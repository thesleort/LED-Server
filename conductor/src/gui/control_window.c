
#include "gui/control_window.h"

void control_window_init(GtkWidget *window, stream_data *data) {
    gtk_window_set_title(GTK_WINDOW(window), "LED Server - Control window");

    GtkWidget *vbox;
    GtkWidget *decklink_options;
    GtkWidget *webview_options;
    GtkWidget *controls;

    GtkLabel *decklink_label, *webview_label, *controls_label;

    GtkButton *btn_tab_switch, *btn_decklink, *btn_webview, *btn_display_open;

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    decklink_options = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    webview_options = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    controls = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);

    decklink_label = gtk_label_new("- Video stream -");
    webview_label = gtk_label_new("- Projector -");
    controls_label = gtk_label_new("- Controls -");

    btn_tab_switch = gtk_button_new_with_label("Switch");
    btn_display_open = gtk_button_new_with_label("Open player");
    btn_webview = gtk_button_new_with_label("Projector");
    btn_decklink = gtk_button_new_with_label("Video stream");

    gtk_box_pack_start(vbox, decklink_label, TRUE, TRUE, 5);
    gtk_box_pack_start(vbox, decklink_options, TRUE, TRUE, 5);

    gtk_box_pack_start(vbox, webview_label, TRUE, TRUE, 5);
    gtk_box_pack_start(vbox, webview_options, TRUE, TRUE, 5);

    gtk_box_pack_start(vbox, controls_label, TRUE, TRUE, 5);
    gtk_box_pack_start(vbox, controls, TRUE, TRUE, 0);

    gtk_box_pack_end(controls, btn_display_open, TRUE, TRUE, 10);
    gtk_box_pack_end(controls, btn_tab_switch, TRUE, TRUE, 10);
    gtk_box_pack_end(controls, btn_webview, TRUE, TRUE, 10);
    gtk_box_pack_end(controls, btn_decklink, TRUE, TRUE, 10);



    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);

    gtk_container_add(window, vbox);

    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event_cb), &data);

    gtk_widget_show_all(window);

}