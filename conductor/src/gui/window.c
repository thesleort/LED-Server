#include <gtk/gtk.h>

#include "gui/window.h"

#include "gui/stream_playback.h"
#include "options.h"


int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("led.server.conductor", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    gst_init(&argc, &argv);

    return status;
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *display_window;
    GtkWidget *control_window;
    GtkWidget *tab;
    stream_data stream;

    options *option = (options*)malloc(sizeof(options)); 
    decklink_options *d_option = (decklink_options *)malloc(sizeof(decklink_options));
    option->m_decklink_options = d_option;
    option->m_decklink_options->m_stream = &stream;

    tab = gtk_notebook_new();

    control_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    display_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    control_window_init(control_window, option, tab);
    display_window_init(display_window, option, tab);


    gtk_widget_show_all(display_window);
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