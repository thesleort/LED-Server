#ifndef __STREAM_PLAYBACK_GTK_H
#define __STREAM_PLAYBACK_GTK_H

#include <gtk/gtk.h>
#include <gst/gst.h>

typedef struct _custom_data {
    GstElement *pipeline;
    GstElement *source;
    GstElement *convert;
    GstElement *sink;
} custom_data;

static void pad_added_handler(GstElement *src, GstPad *pad, custom_data *data);

void decklink_stream_gst();

#endif