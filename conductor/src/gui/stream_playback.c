#include <gtk/gtk.h>
#include <gst/gst.h>
#include <webkit2/webkit2.h>

#include "gui/stream_playback.h"

void decklink_stream_gst(GtkGrid *grid, GtkWindow *window, stream_data *data) {
    GstBus *bus;
    GstStateChangeReturn ret;

    printf("Init stream\n");

    gst_init(0, ' ');

    memset(data, 0, sizeof(*data));
    data->duration = GST_CLOCK_TIME_NONE;


    // data.pipeline = gst_parse_launch("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);
    data->pipeline = gst_element_factory_make ("playbin", "playbin");

    if (!data->pipeline) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    g_object_set(data->pipeline, "uri", "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);

    g_signal_connect(G_OBJECT(data->pipeline), "video-tags-changed", (GCallback)tags_cb, &data);
    g_signal_connect(G_OBJECT(data->pipeline), "audio-tags-changed", (GCallback)tags_cb, &data);
    g_signal_connect(G_OBJECT(data->pipeline), "text-tags-changed", (GCallback)tags_cb, &data);

    setup_stream_ui(grid, window, data);

    bus = gst_element_get_bus(data->pipeline);

    gst_bus_add_signal_watch (bus);

    ret = gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        gst_object_unref (data->pipeline);
        return -1;
    }

    /* Register a function that GLib will call every second */
    g_timeout_add_seconds (1, (GSourceFunc)refresh_ui, &data);

    printf("streaming\n");

    // gtk_widget_show_all(window);
}

void setup_stream_ui(GtkGrid *grid, GtkWindow *window, stream_data *data) {
    GtkWidget *video_area;
    GtkWidget *main_hbox;
    GtkWidget *main_box;

    // video_area = gtk_drawing_area_new();
    video_area = GTK_DRAWING_AREA(gtk_drawing_area_new());
    main_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_double_buffered(video_area, FALSE);
    gtk_widget_set_size_request(video_area, 896, 512);

    gtk_box_pack_start(GTK_BOX(main_box), video_area, TRUE, TRUE, 0);


    // grid = GTK_GRID(gtk_grid_new());
    gtk_grid_attach(grid, main_box, 0, 0, 100, 1);


    g_signal_connect(video_area, "realize", G_CALLBACK(realize_cb), data);
    g_signal_connect (video_area, "draw", G_CALLBACK (draw_cb), data);

    // gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(data->pipeline), video_area);
    // gtk_container_add(window, video_area);


    // gtk_container_add(GTK_CONTAINER(grid), GTK_GRID(grid));

    // gtk_widget_show_all(grid);

    // main_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // gtk_box_pack_start(GTK_BOX(main_hbox), video_area, TRUE, TRUE, 0);

    // main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_box_pack_start(GTK_BOX(main_box), main_hbox, TRUE, TRUE, 0);

    // gtk_container_add(GTK_CONTAINER(window), main_box);
}

/*
 *
 * Helper functions
 * 
 */

/* This function is called when new metadata is discovered in the stream */
void tags_cb(GstElement *playbin, gint stream, stream_data *data) {
    printf("Calling: tags_cb\n");
    /* We are possibly in a GStreamer working thread, so we notify the main
   * thread of this event through a message in the bus */
    gst_element_post_message(playbin,
                             gst_message_new_application(GST_OBJECT(playbin),
                                                         gst_structure_new_empty("tags-changed")));
}

gboolean refresh_ui(stream_data *data) {
    gint64 current = -1;

    /* We do not want to update anything unless we are in the PAUSED or PLAYING states */
    if (data->state < GST_STATE_PAUSED)
        return TRUE;

    /* If we didn't know it yet, query the stream duration */
    // if (!GST_CLOCK_TIME_IS_VALID(data->duration)) {
    //     if (!gst_element_query_duration(data->pipeline, GST_FORMAT_TIME, &data->duration)) {
    //         g_printerr("Could not query current duration.\n");
    //     } else {
    //         /* Set the range of the slider to the clip duration, in SECONDS */
    //         gtk_range_set_range(GTK_RANGE(data->slider), 0, (gdouble)data->duration / GST_SECOND);
    //     }
    // }

    // if (gst_element_query_position(data->playbin, GST_FORMAT_TIME, &current)) {
    //     /* Block the "value-changed" signal, so the slider_cb function is not called
    //  * (which would trigger a seek the user has not requested) */
    //     g_signal_handler_block(data->slider, data->slider_update_signal_id);
    //     /* Set the position of the slider to the current pipeline positoin, in SECONDS */
    //     gtk_range_set_value(GTK_RANGE(data->slider), (gdouble)current / GST_SECOND);
    //     /* Re-enable the signal */
    //     g_signal_handler_unblock(data->slider, data->slider_update_signal_id);
    // }
    return TRUE;
}

void realize_cb(GtkWidget *widget, stream_data *data) {
    printf("Calling: realize_cb\n");
    GdkWindow *window = gtk_widget_get_window(widget);
    guintptr window_handle;

    if (!gdk_window_ensure_native(window))
        g_error("Couldn't create native window needed for GstVideoOverlay!");

    printf("err\n");
    /* Pass it to playbin, which implements VideoOverlay and will forward it to the video sink */
    window_handle = GDK_WINDOW_XID(window);
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(data->pipeline), window_handle);
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
void stop_cb (GtkButton *button, stream_data *data) {
  gst_element_set_state (data->pipeline, GST_STATE_READY);
}