#ifndef __CONTROL_WINDOW_H
#define __CONTROL_WINDOW_H

#include <gtk/gtk.h>

#include "gui/window.h"
#include "options.h"

void control_window_init(GtkWidget *window, options *option);

void projector_settings_add(GtkGrid *decklink_options, options *option);

void video_stream_control_add(GtkGrid *projector_options, options *option);

void controls_add(GtkBox *controls_box, options *option);

void about_info_add(GtkGrid *grid);

void tab_decklink_cb(GtkButton *button, options *option);

void tab_webview_cb(GtkButton *button, options *option);

void tab_nextpage_cb(GtkButton *button, options *option);

void save_current_tab(int tab, options *option);

void decklink_input_hdmi(GtkButton *button, decklink_options *option);

void decklink_input_sdi(GtkButton *button, decklink_options *option);

void open_display_window_cb(GtkButton *button, options *option);

void set_display_window_pos_cb(GtkButton *button, options *option);

void gui_lock_cb(GtkButton *button, options *option);


#endif