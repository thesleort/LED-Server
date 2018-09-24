#include <webkit2/webkit2.h>

#include "gui/webview.h"

GtkBox *grid;
GtkEntry *url;
GtkButton *search_btn;
WebKitWebView *webView;

void add_webview(GtkWidget *window) {

    webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
    webkit_web_view_load_uri(webView, "http://localhost/");

    grid = GTK_GRID(gtk_grid_new());
    url = GTK_ENTRY(gtk_entry_new());
    search_btn = GTK_BUTTON(gtk_button_new_with_label("Connect"));

    gtk_widget_set_size_request(webView, 1500, 550);
    gtk_widget_set_size_request(url, 1600, 30);

    gtk_entry_set_placeholder_text(url, webkit_web_view_get_uri(webView));

    //In order: left, top, width, height

    gtk_grid_attach(grid, webView, 0, 0, 100, 1);
    gtk_grid_attach(grid, url, 0, 1, 70, 1);
    gtk_grid_attach(grid, search_btn, 70, 1, 30, 1);

    gtk_entry_set_text(url, webkit_web_view_get_uri(webView));

    gtk_container_add(GTK_CONTAINER(window), GTK_GRID(grid));

    g_signal_connect(search_btn, "clicked", G_CALLBACK(url_entry_query), NULL);
    g_signal_connect(url, "activate", G_CALLBACK(url_entry_query), NULL);

    g_signal_connect(window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), window);




    // Will get input from mouse and keyboard.
    // gtk_widget_grab_focus(GTK_WIDGET(webView));
}

static void url_entry_query(GtkWidget *widget, gpointer data) {
    char buf[512];
    snprintf(buf, sizeof(buf), "%s%s", "http://", gtk_entry_get_text(url));
    printf("%s\n", buf);
    webkit_web_view_load_uri(webView, buf);
    gtk_entry_set_placeholder_text(url, webkit_web_view_get_uri(webView));
}

static void destroyWindowCb(GtkWidget *widget, GtkWidget *window) {
    gtk_main_quit();
}

static gboolean closeWebViewCb(WebKitWebView *webView, GtkWidget *window) {
    gtk_widget_destroy(window);
    return TRUE;
}