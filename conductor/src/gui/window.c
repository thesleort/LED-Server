#include <gtk/gtk.h>

#include "gui/window.h"

// #include "gui/webview.h"
#include "gui/stream_playback.h"
// #include "streamer/decklink.h"


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

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    stream_data stream;
    GtkWidget *tab;
    GtkGrid *webview_grid;
    GtkLabel *webview_label;

    GtkGrid *stream_grid;
    GtkLabel *stream_label;
    // window = gtk_application_window_new(app);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event_cb), &stream);
    gtk_window_set_title(GTK_WINDOW(window), "LED Server");
    gtk_window_set_decorated(window, FALSE);

    webview_grid = gtk_grid_new();
    webview_label = gtk_label_new("Webview");

    stream_grid = gtk_grid_new();
    stream_label = gtk_label_new("Decklink");

    webview(webview_grid);
    decklink_stream_gst(stream_grid, window, &stream);

    tab = gtk_notebook_new();
    gtk_notebook_set_show_border(tab, FALSE);
    gtk_notebook_append_page(tab, stream_grid, stream_label);
    gtk_notebook_append_page(tab, webview_grid, webview_label);

    g_signal_connect(G_OBJECT(tab), "switch-page", G_CALLBACK(switch_tab_cb), &stream);


    gtk_container_add(GTK_CONTAINER(window), tab);
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);

    gtk_widget_show_all(window);
    gtk_main();
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

/* This function is called when the main window is closed */
void delete_event_cb(GtkWidget *widget, GdkEvent *event, stream_data *data) {
    stop_cb(NULL, data);
    gtk_main_quit();
}