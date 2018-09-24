#ifndef __WEBVIEW_GTK_H
#define __WEBVIEW_GTK_H

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

void add_webview(GtkWidget *window);

static void url_entry_reset(GtkWidget *widget, gpointer data);
static void url_entry_query(GtkWidget *widget, gpointer data);
static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);

#endif