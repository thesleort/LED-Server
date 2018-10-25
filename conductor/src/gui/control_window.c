
#include "gui/control_window.h"

GtkEntry *entry_pos_x, *entry_pos_y;

void control_window_init(GtkWidget *window, options *option, GtkNotebook **tab) {
    gtk_window_set_title(GTK_WINDOW(window), "LED Server - Control window");

    option->display_window = gtk_widget_get_window(tab);
    option->m_controls->locked = FALSE;

    GtkWidget *vbox;
    GtkGrid *decklink_options, *projector_options;
    GtkWidget *webview_options;
    GtkWidget *controls;

    GtkLabel *decklink_label, *webview_label, *controls_label;
    GtkLabel *decklink_label_desc, *decklink_label_current_input;
    GtkLabel *projector_label_desc;

    GtkButton *btn_pos_apply, *btn_upper_corner;

    GtkButton *btn_tab_switch, *btn_display_open, *btn_webview, *btn_decklink, *btn_lock, *btn_hdmi, *btn_sdi;

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    decklink_options = gtk_grid_new();
    projector_options = gtk_grid_new();
    webview_options = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    controls = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);

    decklink_label = gtk_label_new("- Video stream -");
    webview_label = gtk_label_new("- Projector -");
    controls_label = gtk_label_new("- Controls -");

    decklink_label_desc = gtk_label_new("Choose Decklink card input:");
    decklink_label_current_input = gtk_label_new("Current input: SDI");
    gtk_label_set_xalign(decklink_label_current_input, 0.0);

    btn_hdmi = gtk_button_new_with_label("HDMI Input");
    btn_sdi = gtk_button_new_with_label("SDI Input");

    btn_display_open = gtk_button_new_with_label("Open player");
    btn_decklink = gtk_button_new_with_label("Video stream");
    btn_tab_switch = gtk_button_new_with_label("Switch");
    btn_webview = gtk_button_new_with_label("Projector");
    btn_lock = gtk_button_new_with_label("LOCK");

    btn_pos_apply = gtk_button_new_with_label("Apply");
    btn_upper_corner = gtk_button_new_with_label("Bind");
    entry_pos_x = gtk_entry_new();
    entry_pos_y = gtk_entry_new();
    projector_label_desc = gtk_label_new("Position:");
    option->m_display_settings->entry_pos_x = entry_pos_x;
    option->m_display_settings->entry_pos_y = entry_pos_y;
    option->m_display_settings->btn_pos_apply = btn_pos_apply;

    option->m_controls->btn_open_display = btn_display_open;
    option->m_controls->btn_decklink = btn_decklink;
    option->m_controls->btn_tab_switch = btn_tab_switch;
    option->m_controls->btn_webview = btn_webview;

    option->m_decklink_options->m_input = sdi;
    option->m_decklink_options->btn_other = btn_sdi;
    option->m_decklink_options->label_current_input = decklink_label_current_input;
    option->m_decklink_options->btn_hdmi = btn_hdmi;
    option->m_decklink_options->btn_sdi = btn_sdi;
    gtk_widget_set_sensitive(btn_sdi, FALSE);

    gtk_box_pack_start(vbox, decklink_label, FALSE, FALSE, 5);
    gtk_box_pack_start(vbox, decklink_options, TRUE, TRUE, 10);

    gtk_box_pack_start(vbox, webview_label, FALSE, FALSE, 0);
    gtk_box_pack_start(vbox, webview_options, TRUE, TRUE, 0);
    gtk_box_pack_start(webview_options, projector_options, TRUE, TRUE, 0);

    gtk_box_pack_start(vbox, controls_label, FALSE, FALSE, 0);
    gtk_box_pack_start(vbox, controls, TRUE, TRUE, 0);

    gtk_box_pack_end(controls, btn_lock, TRUE, TRUE, 10); // Set all buttons to insensitive.
    gtk_box_pack_end(controls, btn_display_open, TRUE, TRUE, 10);
    gtk_box_pack_end(controls, btn_tab_switch, TRUE, TRUE, 10);
    gtk_box_pack_end(controls, btn_webview, TRUE, TRUE, 10);
    gtk_box_pack_end(controls, btn_decklink, TRUE, TRUE, 10);

    gtk_grid_attach(decklink_options, btn_hdmi, 1, 0, 2, 2);
    gtk_grid_attach(decklink_options, btn_sdi, 3, 0, 2, 2);
    gtk_grid_attach(decklink_options, decklink_label_desc, 0, 0, 1, 1);
    gtk_grid_attach(decklink_options, decklink_label_current_input, 0, 1, 1, 1);

    gtk_grid_attach(projector_options, projector_label_desc, 0, 0, 1, 2);
    gtk_grid_attach(projector_options, entry_pos_x, 1, 0, 1, 1);
    gtk_grid_attach(projector_options, entry_pos_y, 2, 0, 1, 1);
    gtk_grid_attach(projector_options, btn_pos_apply, 3, 0, 1, 1);

    g_object_set(decklink_label_desc, "margin", 12, NULL);
    g_object_set(btn_hdmi, "margin", 6, NULL);
    g_object_set(btn_sdi, "margin", 6, NULL);
    g_object_set(decklink_label_current_input, "margin", 12, NULL);

    g_object_set(projector_label_desc, "margin", 12, NULL);
    g_object_set(entry_pos_x, "margin", 6, NULL);
    g_object_set(entry_pos_y, "margin", 6, NULL);
    gtk_entry_set_width_chars(entry_pos_x, 5);
    gtk_entry_set_width_chars(entry_pos_y, 5);
    gtk_entry_set_placeholder_text(entry_pos_x, "X");
    gtk_entry_set_placeholder_text(entry_pos_y, "Y");
    gtk_entry_set_input_purpose(entry_pos_x, GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_input_purpose(entry_pos_y, GTK_INPUT_PURPOSE_NUMBER);

    g_signal_connect(G_OBJECT(btn_pos_apply), "clicked", G_CALLBACK(set_display_window_pos_cb), option);

    if (option->is_display_open == TRUE) {
        gtk_widget_set_sensitive(btn_display_open, FALSE);
    }

    g_signal_connect(G_OBJECT(btn_decklink), "clicked", G_CALLBACK(tab_decklink_cb), tab);
    g_signal_connect(G_OBJECT(btn_webview), "clicked", G_CALLBACK(tab_webview_cb), tab);
    g_signal_connect(G_OBJECT(btn_tab_switch), "clicked", G_CALLBACK(tab_nextpage_cb), tab);
    g_signal_connect(G_OBJECT(btn_display_open), "clicked", G_CALLBACK(open_display_window_cb), option);
    g_signal_connect(G_OBJECT(btn_lock), "clicked", G_CALLBACK(gui_lock_cb), option);

    g_signal_connect(G_OBJECT(btn_hdmi), "clicked", G_CALLBACK(decklink_input_hdmi), option->m_decklink_options);
    g_signal_connect(G_OBJECT(btn_sdi), "clicked", G_CALLBACK(decklink_input_sdi), option->m_decklink_options);
    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event_cb), option->m_decklink_options->m_stream);

    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);

    gtk_container_add(window, vbox);

    gtk_widget_show_all(window);
}

void tab_decklink_cb(GtkButton *button, GtkNotebook *tab) {
    gtk_notebook_set_current_page(tab, 0);
}

void tab_webview_cb(GtkButton *button, GtkNotebook *tab) {
    gtk_notebook_set_current_page(tab, 1);
}

void tab_nextpage_cb(GtkButton *button, GtkNotebook *tab) {
    if (gtk_notebook_get_current_page(tab) == gtk_notebook_get_n_pages(tab) - 1) {
        gtk_notebook_set_current_page(tab, 0);
    } else {
        gtk_notebook_next_page(tab);
    }
}

void decklink_input_hdmi(GtkButton *button, decklink_options *option) {
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(option->btn_other), TRUE);
    option->btn_other = button;
    option->m_input = sdi;
    gtk_label_set_text(option->label_current_input, "Current input: HDMI");
}

void decklink_input_sdi(GtkButton *button, decklink_options *option) {
    gtk_widget_set_sensitive(button, FALSE);
    gtk_widget_set_sensitive(option->btn_other, TRUE);
    option->btn_other = button;
    option->m_input = hdmi;
    gtk_label_set_text(option->label_current_input, "Current input: SDI");
}

void open_display_window_cb(GtkButton *button, options *option) {
    GtkWidget *display_window;

    display_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    option->display_window = display_window;
    option->m_display_settings->tab = gtk_notebook_new();

    g_signal_connect(G_OBJECT(option->m_controls->btn_decklink), "clicked", G_CALLBACK(tab_decklink_cb), option->m_display_settings->tab);
    g_signal_connect(G_OBJECT(option->m_controls->btn_webview), "clicked", G_CALLBACK(tab_webview_cb), option->m_display_settings->tab);
    g_signal_connect(G_OBJECT(option->m_controls->btn_tab_switch), "clicked", G_CALLBACK(tab_nextpage_cb), option->m_display_settings->tab);

    gtk_widget_set_sensitive(button, FALSE);
    display_window_init(option->display_window, option);
}

void set_display_window_pos_cb(GtkButton *button, options *option) {

    option->m_display_settings->pos_x = atoi(gtk_entry_get_text(entry_pos_x));
    option->m_display_settings->pos_y = atoi(gtk_entry_get_text(entry_pos_y));

    gtk_window_move(option->display_window, option->m_display_settings->pos_x, option->m_display_settings->pos_y);
    printf("moved window to %i,%i\n", option->m_display_settings->pos_x, option->m_display_settings->pos_y);
}

void gui_lock_cb(GtkButton *button, options *option) {
    if (option->m_controls->locked == TRUE) {
        gtk_widget_set_sensitive(option->m_display_settings->btn_pos_apply, TRUE);
        gtk_widget_set_sensitive(option->m_display_settings->entry_pos_x, TRUE);
        gtk_widget_set_sensitive(option->m_display_settings->entry_pos_y, TRUE);
        gtk_widget_set_sensitive(option->m_decklink_options->btn_hdmi, TRUE);
        gtk_widget_set_sensitive(option->m_decklink_options->btn_sdi, TRUE);
        gtk_widget_set_sensitive(option->m_decklink_options->btn_other, FALSE);
        option->m_controls->locked = FALSE;
        printf("State: Unlocked\n");
    } else {
        gtk_widget_set_sensitive(option->m_display_settings->btn_pos_apply, FALSE);
        gtk_widget_set_sensitive(option->m_display_settings->entry_pos_x, FALSE);
        gtk_widget_set_sensitive(option->m_display_settings->entry_pos_y, FALSE);
        gtk_widget_set_sensitive(option->m_decklink_options->btn_hdmi, FALSE);
        gtk_widget_set_sensitive(option->m_decklink_options->btn_sdi, FALSE);
        option->m_controls->locked = TRUE;
        printf("State: Locked\n");
    }
}