#ifndef __WEBVIEW_GTK_H
#define __WEBVIEW_GTK_H

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include "options.h"

void add_webview(GtkWidget *window, GtkWidget *area);

void webview(GtkGrid **grid, options *option);

void load_scripts(options *option);

static void url_entry_reset(GtkWidget *widget, gpointer data);
static void url_entry_query(GtkWidget *widget, gpointer data);
static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);

#endif