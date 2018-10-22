#include <webkit2/webkit2.h>

#include "gui/webview.h"

// GtkBox *grid;
GtkEntry *url;
GtkButton *search_btn;
WebKitWebView *web_view;

void webview(GtkGrid **grid) {
    // url = malloc(sizeof(GtkEntry));
    url = gtk_entry_new();
    search_btn = gtk_button_new();
    web_view = webkit_web_view_new();
    // web_view = malloc(sizeof(WebKitWebView));
    printf("Webview setup\n");

    web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    webkit_web_view_load_uri(web_view, "http://localhost/");

    // grid = GTK_GRID(gtk_grid_new());
    url = GTK_ENTRY(gtk_entry_new());
    search_btn = GTK_BUTTON(gtk_button_new_with_label("Connect"));

    gtk_widget_set_size_request(web_view, 1500, 550);
    gtk_widget_set_size_request(url, 1600, 30);

    gtk_entry_set_placeholder_text(url, webkit_web_view_get_uri(web_view));

    //In order: left, top, width, height

    gtk_grid_attach(grid, web_view, 0, 0, 100, 1);
    gtk_grid_attach(grid, url, 0, 1, 70, 1);
    gtk_grid_attach(grid, search_btn, 70, 1, 30, 1);

    gtk_entry_set_text(url, webkit_web_view_get_uri(web_view));

    // gtk_container_add(GTK_CONTAINER(window), GTK_GRID(grid));

    g_signal_connect(search_btn, "clicked", G_CALLBACK(url_entry_query), NULL);
    g_signal_connect(url, "activate", G_CALLBACK(url_entry_query), NULL);

    // g_signal_connect(window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    // g_signal_connect(web_view, "close", G_CALLBACK(closeWebViewCb), window);



    // Will get input from mouse and keyboard.
    // gtk_widget_grab_focus(GTK_WIDGET(web_view));
}

static void url_entry_query(GtkWidget *widget, gpointer data) {
    char buf[512];
    snprintf(buf, sizeof(buf), "%s%s", "http://", gtk_entry_get_text(url));
    printf("%s\n", buf);
    webkit_web_view_load_uri(web_view, buf);
    gtk_entry_set_placeholder_text(url, webkit_web_view_get_uri(web_view));
}

// static void destroyWindowCb(GtkWidget *widget, GtkWidget *window) {
//     gtk_main_quit();
// }

static gboolean closeWebViewCb(WebKitWebView *web_view, GtkWidget *window) {
    gtk_widget_destroy(window);
    return TRUE;
}