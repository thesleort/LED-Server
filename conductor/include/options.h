#ifndef __OPTIONS_H
#define __OPTIONS_H

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <gst/gst.h>
#include <libconfig.h>

#define MAIN_WINDOW "LED Server - Control window"
#define DISPLAY_WINDOW "LED Server - Display window"
#define S_PROJECTOR_VIDEO_STREAM "Video stream"
#define S_PROJECTOR_WEB_VIEW "Webview"

#define CONFIG_FILE "conductor.cfg"

#define UNUSED(x) (void)(x);

enum input { hdmi, sdi };

typedef struct _stream_data {
    gboolean is_live;
    GstBin *pipeline;
	GstElement *source;
	GstElement *tee;
	GstElement *convert;
	GstElement *sink;
	GstElement *preview_sink;
    GMainLoop *loop;
    GstState state; /* Current state of the pipeline */
    gint64 duration;

} stream_data;

typedef struct _controls {
    GtkButton *btn_open_display;
    GtkButton *btn_tab_switch;
    GtkButton *btn_decklink;
    GtkButton *btn_webview;
    gboolean locked;
} controls;

typedef struct _display_settings {
    GtkNotebook *tab;
    unsigned pos_x;
    unsigned pos_y;
    GtkEntry *entry_pos_x;
    GtkEntry *entry_pos_y;
    GtkButton *btn_pos_apply;
    GtkLabel *currently_showing;

    gchar *website_url;
	WebKitWebView *webview;
	gchar *webview_pause_script;
	int pause_size;
	gchar *webview_play_script;
    int play_size;
    GtkEntry *entry_url;
    GtkButton *btn_url_search;
    GtkButton *btn_url_save;
} display_settings;

typedef struct _decklink_options {
    enum input m_input;
    GtkButton *btn_other;
    GtkLabel *label_current_input;
    stream_data *m_stream;
    GtkButton *btn_hdmi;
    GtkButton *btn_sdi;
} decklink_options;

typedef struct _options {
    decklink_options *m_decklink_options;
    controls *m_controls;
    display_settings *m_display_settings;
    GtkWindow *display_window;
    gboolean is_display_open;
    config_t cfg;
} options;

#endif