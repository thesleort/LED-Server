#ifndef __WEBVIEW_GTK_H
#define __WEBVIEW_GTK_H

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include "options.h"

void add_webview(GtkWidget *window, GtkWidget *area);

void webview_add(GtkGrid *grid, options *option);

void load_scripts(options *option);

gboolean webview_close_cb(WebKitWebView* webView, GtkWidget* window);

void url_entry_query(GtkWidget *widget, options *option);
void url_entry_save(GtkWidget *widget, options *option);
void url_entry_reset(GtkWidget *widget, gpointer data);

#endif