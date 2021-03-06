#ifndef __STREAM_PLAYBACK_GTK_H
#define __STREAM_PLAYBACK_GTK_H

#include <string.h>

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gst/video/videooverlay.h>

#include "options.h"

typedef struct _custom_data {
    GstElement *playbin; /* Our one and only pipeline */

    GtkWidget *slider;              /* Slider widget to keep track of current position */
    GtkWidget *streams_list;        /* Text widget to display info about the streams */
    gulong slider_update_signal_id; /* Signal ID for the slider update signal */

    GstState state; /* Current state of the pipeline */
    gint64 duration;
} custom_data;

// static GtkWidget *video_area;

void decklink_stream_gst(options *option);

void setup_stream_ui(GtkGrid *grid, GtkWindow *window, stream_data *data);

void tags_cb(GstElement *playbin);

gboolean refresh_ui(stream_data *data);

void stop_cb (stream_data *data);

void pause_cb(stream_data *data);

void play_cb(stream_data *data);

void pause_sink_cb(GstElement *sink);

void play_sink_cb(GstElement *sink);

void realize_cb(GtkWidget *widget, GstElement *sink);

gboolean draw_cb(GtkWidget *widget, cairo_t *cr, stream_data *data);

void cb_message(GstBus *bus, GstMessage *msg, stream_data *data);

#endif