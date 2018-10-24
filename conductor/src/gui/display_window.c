
#include "gui/display_window.h"

void display_window_init(GtkWidget *window, stream_data *data, GtkNotebook **tab) {

    GtkGrid *webview_grid;
    GtkLabel *webview_label;

    GtkGrid *stream_grid;
    GtkLabel *stream_label;

    gtk_window_set_title(GTK_WINDOW(window), "LED Server - Display window");
    gtk_window_set_decorated(window, TRUE);

    webview_grid = gtk_grid_new();
    webview_label = gtk_label_new("Webview");

    stream_grid = gtk_grid_new();
    stream_label = gtk_label_new("Decklink");

    // Setup tab: Start

    webview(webview_grid);
    decklink_stream_gst(stream_grid, window, data);


    gtk_notebook_set_show_tabs(tab, FALSE);
    gtk_notebook_set_show_border(tab, FALSE);
    gtk_notebook_append_page(tab, stream_grid, stream_label);
    gtk_notebook_append_page(tab, webview_grid, webview_label);

    g_signal_connect(G_OBJECT(tab), "switch-page", G_CALLBACK(switch_tab_cb), data);
    // Setup tab: End

    gtk_container_add(GTK_CONTAINER(window), tab);
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);

    gtk_widget_show_all(window);
}