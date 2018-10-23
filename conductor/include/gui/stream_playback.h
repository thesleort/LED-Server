#ifndef __STREAM_PLAYBACK_GTK_H
#define __STREAM_PLAYBACK_GTK_H

#include <string.h>

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gst/video/videooverlay.h>

typedef struct _streamData {
    gboolean is_live;
    GstElement *pipeline;
    GMainLoop *loop;
    GstState state; /* Current state of the pipeline */
    gint64 duration;

} stream_data;

typedef struct _custom_data {
    GstElement *playbin; /* Our one and only pipeline */

    GtkWidget *slider;              /* Slider widget to keep track of current position */
    GtkWidget *streams_list;        /* Text widget to display info about the streams */
    gulong slider_update_signal_id; /* Signal ID for the slider update signal */

    GstState state; /* Current state of the pipeline */
    gint64 duration;
} custom_data;

void decklink_stream_gst(GtkGrid **grid, GtkWindow **window);

static void setup_stream_ui(GtkGrid **grid, GtkWindow **window, stream_data *data);

static void tags_cb(GstElement *playbin, gint stream, stream_data *data);

static gboolean refresh_ui(stream_data *data);

static void realize_cb(GtkWidget *widget, stream_data *data);

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, stream_data *data);

static void cb_message(GstBus *bus, GstMessage *msg, stream_data *data);

#endif