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
    GtkNotebook *tab;
    stream_data stream;

    options *option = (options*)malloc(sizeof(options)); 
    decklink_options *d_option = (decklink_options *)malloc(sizeof(decklink_options));
    display_settings *display = (display_settings*)malloc(sizeof(display_settings));
    controls *control = (controls*)malloc(sizeof(controls));
    option->m_controls = control;
    option->m_decklink_options = d_option;
    option->m_display_settings = display;
    option->m_decklink_options->m_stream = &stream;

    option->m_display_settings->tab = gtk_notebook_new();
    tab = option->m_display_settings->tab;

    control_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    display_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    option->is_display_open = TRUE;
    control_window_init(control_window, option, tab);
    display_window_init(display_window, option, tab);


    gtk_widget_show_all(display_window);
    gtk_main();
}


/* This function is called when the main window is closed */
void delete_event_cb(GtkWidget *widget, GdkEvent *event, stream_data *data) {
    stop_cb(NULL, data);
    gtk_main_quit();
}