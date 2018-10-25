#ifndef __OPTIONS_H
#define __OPTIONS_H

#include <gtk/gtk.h>
#include "gui/stream_playback.h"

enum input { hdmi, sdi };

typedef struct _stream_data {
    gboolean is_live;
    GstElement *pipeline;
    GMainLoop *loop;
    GstState state; /* Current state of the pipeline */
    gint64 duration;

} stream_data;

typedef struct _decklink_options {
    enum input m_input;
    GtkButton *btn_other;
    GtkLabel *label_current_input;
    stream_data *m_stream;
} decklink_options;

typedef struct _options {
    decklink_options *m_decklink_options;
    GtkWindow *display_window;
    gboolean is_display_open;
} options;

#endif