
#include "gui/display_window.h"

void display_window_init(GtkWidget *window, options *option, GtkNotebook **tab) {
    stream_data *data = option->m_decklink_options->m_stream;
    option->display_window = window;
    option->is_display_open = TRUE;

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
    decklink_stream_gst(stream_grid, window, option);

    gtk_notebook_set_show_tabs(tab, FALSE);
    gtk_notebook_set_show_border(tab, FALSE);
    gtk_notebook_append_page(tab, stream_grid, stream_label);
    gtk_notebook_append_page(tab, webview_grid, webview_label);

    g_signal_connect(G_OBJECT(tab), "switch-page", G_CALLBACK(switch_tab_cb), data);
    // Setup tab: End

    gtk_container_add(GTK_CONTAINER(window), tab);
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);

    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(display_close_cb), option);

    gtk_widget_show_all(window);
}

void display_close_cb(GtkWidget *widget, GdkEvent *event, options *option) {
    stop_cb(NULL, option->m_decklink_options->m_stream);
    option->is_display_open = FALSE;
    gtk_widget_destroy(option->display_window);
    gtk_widget_set_sensitive(option->m_controls->open_display, TRUE);
    printf("Closed: Display Window\n");
}

void switch_tab_cb(GtkNotebook *notebook, GtkWidget *page, guint page_num, stream_data *data) {
    printf("Calling: switch_tab_cb\n");

    switch (page_num) {
    case 0:
        printf("page: 0\n");
        play_cb(data);
        break;
    case 1:
        printf("page: 1\n");
        pause_cb(data);
        break;
    }
}
