#include <gtk/gtk.h>

#include "gui/window.h"
// #include "gui/webview.h"
// #include "gui/stream_playback.h"
#include "streamer/decklink.h"

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("led.server.conductor", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    gst_init(&argc, &argv);

    // decklink();

    return status;
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;

    window = gtk_application_window_new(app);
    // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);
    // add_webview(window);
    tab(window);
    // decklink_stream_gst(window);
    // webview(window);
}

void tab(GtkWidget **window) {
    GtkWidget *tab;
    GtkGrid *webview_grid;
    GtkLabel *webview_label;
    
    GtkGrid *stream_grid;
    GtkLabel *stream_label;

    webview_grid = gtk_grid_new();
    webview_label = gtk_label_new("Webview");
    
    stream_grid = gtk_grid_new();
    stream_label = gtk_label_new("Decklink");

    webview(webview_grid);
    decklink_stream_gst(stream_grid, window);

    tab = gtk_notebook_new();

    
    gtk_notebook_append_page(tab, webview_grid, webview_label);
    gtk_notebook_append_page(tab, stream_grid, stream_label);
    // gtk_notebook_append_page()

    gtk_container_add(window, tab);

    gtk_widget_show_all(window);
}