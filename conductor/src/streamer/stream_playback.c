#include <gtk/gtk.h>
#include <gst/gst.h>
#include <webkit2/webkit2.h>

#include "streamer/stream_playback.h"

void decklink_stream_gst(GtkGrid *grid, GtkWindow *window, options *option) {
    stream_data *data = option->m_decklink_options->m_stream;
    GstBus *bus;
    GstStateChangeReturn ret;

    printf("Init stream\n");

    gst_init(0, NULL);

    memset(data, 0, sizeof(*data));
    data->duration = GST_CLOCK_TIME_NONE;
    printf("Gst element init\n");

    data->source = gst_element_factory_make("decklinkvideosrc", "source");
    data->convert = gst_element_factory_make("videoconvert", "convert");
    data->sink = gst_element_factory_make("xvimagesink", "sink");

    g_object_set(data->source, "connection", 2, NULL);

    g_object_set(data->sink, "sync", FALSE, NULL);

    printf("Gst element init completed\n");

    data->pipeline = GST_BIN(gst_pipeline_new("decklink_stream"));

    printf("Gst pipeline new done\n");

    if (!data->pipeline || !data->source || !data->convert || !data->sink) {
        g_printerr("Not all elements could be created.\n");
        return;
    }

    // g_signal_connect(G_OBJECT(data->pipeline), "video-tags-changed", (GCallback)tags_cb, &data);
    // g_signal_connect(G_OBJECT(data->pipeline), "audio-tags-changed", (GCallback)tags_cb, &data);
    // g_signal_connect(G_OBJECT(data->pipeline), "text-tags-changed", (GCallback)tags_cb, &data);
    printf("Stream ui start\n");

    setup_stream_ui(grid, window, data);

    printf("Stream ui finish\n");

    bus = gst_element_get_bus(GST_ELEMENT(data->pipeline));

    gst_bus_add_signal_watch(bus);

    ret = gst_element_set_state(GST_ELEMENT(data->pipeline), GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Unable to set the pipeline to the playing state.\n");
        gst_object_unref(data->pipeline);
        return;
    }
    gst_bin_add_many(data->pipeline, data->source, data->convert, data->sink, NULL);

    gst_element_link(data->source, data->convert);
    gst_element_link(data->convert, data->sink);

    /* Register a function that GLib will call every second */
    g_timeout_add_seconds(1, (GSourceFunc)refresh_ui, &data);

    printf("streaming\n");
}

void setup_stream_ui(GtkGrid *grid, GtkWindow *window, stream_data *data) {
    GtkWidget *video_area;
    GtkBox *main_box;

    video_area = gtk_drawing_area_new();
    main_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0));
    printf("test1\n");

    // gtk_widget_set_double_buffered(video_area, FALSE);
    gtk_widget_set_size_request(video_area, 896, 512);

    gtk_grid_attach(grid, GTK_WIDGET(main_box), 0, 0, 100, 1);

    gtk_box_pack_start(main_box, video_area, FALSE, FALSE, 0);

    gtk_widget_realize(GTK_WIDGET(window));

    g_signal_connect(video_area, "realize", G_CALLBACK(realize_cb), data);
    g_signal_connect(video_area, "draw", G_CALLBACK(draw_cb), data);

	gtk_widget_show_all(GTK_WIDGET(window));
}

/*
 *
 * Helper functions
 * 
 */

/* This function is called when new metadata is discovered in the stream */
void tags_cb(GstElement *playbin) {
    printf("Calling: tags_cb\n");
    /* We are possibly in a GStreamer working thread, so we notify the main
   * thread of this event through a message in the bus */
    gst_element_post_message(playbin,
                             gst_message_new_application(GST_OBJECT(playbin),
                                                         gst_structure_new_empty("tags-changed")));
}

gboolean refresh_ui(stream_data *data) {
    // gint64 current = -1;

    /* We do not want to update anything unless we are in the PAUSED or PLAYING states */
    if (data->state < GST_STATE_PAUSED)
        return TRUE;
    return TRUE;
}

void realize_cb(GtkWidget *widget, stream_data *data) {
    printf("Calling: realize_cb\n");
    GdkWindow *window = gtk_widget_get_window(widget);
    gulong window_handle;

    if (!gdk_window_ensure_native(window))
        g_error("Couldn't create native window needed for GstVideoOverlay!");

    printf("err\n");
    /* Pass it to playbin, which implements VideoOverlay and will forward it to the video sink */
    window_handle = GDK_WINDOW_XID(window);
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(data->sink), window_handle);
}

gboolean draw_cb(GtkWidget *widget, cairo_t *cr, stream_data *data) {
    printf("Calling: draw_cb\n");
    if (data->state < GST_STATE_PAUSED) {
        GtkAllocation allocation;

        /* Cairo is a 2D graphics library which we use here to clean the video window.
     * It is used by GStreamer for other reasons, so it will always be available to us. */
        gtk_widget_get_allocation(widget, &allocation);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_rectangle(cr, 0, 0, allocation.width, allocation.height);
        cairo_fill(cr);
    }

    return FALSE;
}

/* This function is called when the STOP button is clicked */
void stop_cb(stream_data *data) {
    gst_element_set_state(GST_ELEMENT(data->pipeline), GST_STATE_READY);
}

void pause_cb(stream_data *data) {
    gst_element_set_state(GST_ELEMENT(data->pipeline), GST_STATE_PAUSED);
}

void play_cb(stream_data *data) {
    gst_element_set_state(GST_ELEMENT(data->pipeline), GST_STATE_PLAYING);
}