
#include "gui/control_window.h"
#include "auxiliary.h"

GtkEntry *entry_pos_x, *entry_pos_y;

void control_window_init(GtkWidget *window, options *option, GtkNotebook *tab) {
    gtk_window_set_title(GTK_WINDOW(window), MAIN_WINDOW);

    option->display_window = GTK_WINDOW(gtk_widget_get_window(GTK_WIDGET(tab)));
    option->m_controls->locked = FALSE;

    GtkBox *vbox;
    GtkGrid *decklink_options, *projector_options;
    GtkBox *webview_options;
    GtkBox *controls_box;

    GtkGrid *preview_grid;

    GtkLabel *decklink_label, *webview_label, *controls_label;
    GtkLabel *decklink_label_desc, *decklink_label_current_input;
    GtkLabel *projector_label_desc;
    GtkLabel *projector_label_showing ,*projector_label_showing_var;

    GtkButton *btn_pos_apply;// btn_switch_pause_toggle;//, *btn_upper_corner;

    GtkButton *btn_tab_switch, *btn_display_open, *btn_webview, *btn_decklink, *btn_lock, *btn_hdmi, *btn_sdi;

    vbox = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 10));
    decklink_options = GTK_GRID(gtk_grid_new());
    projector_options = GTK_GRID(gtk_grid_new());
    webview_options = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10));
    controls_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30));

    preview_grid = GTK_GRID(gtk_grid_new());

    decklink_label = GTK_LABEL(gtk_label_new("- Video stream -"));
    webview_label = GTK_LABEL(gtk_label_new("- Projector -"));
    controls_label = GTK_LABEL(gtk_label_new("- Controls -"));

    decklink_label_desc = GTK_LABEL(gtk_label_new("Choose Decklink card input:"));
    decklink_label_current_input = GTK_LABEL(gtk_label_new("Current input: SDI"));
    gtk_label_set_xalign(decklink_label_current_input, 0.0);

    btn_hdmi = GTK_BUTTON(gtk_button_new_with_label("HDMI Input"));
    btn_sdi = GTK_BUTTON(gtk_button_new_with_label("SDI Input"));

    btn_display_open = GTK_BUTTON(gtk_button_new_with_label("Open player"));
    btn_decklink = GTK_BUTTON(gtk_button_new_with_label(S_PROJECTOR_VIDEO_STREAM));
    btn_tab_switch = GTK_BUTTON(gtk_button_new_with_label("Switch"));
    btn_webview = GTK_BUTTON(gtk_button_new_with_label(S_PROJECTOR_WEB_VIEW));
    btn_lock = GTK_BUTTON(gtk_button_new_with_label("LOCK"));

    btn_pos_apply = GTK_BUTTON(gtk_button_new_with_label("Apply"));
    // btn_upper_corner = gtk_button_new_with_label("Bind");
    entry_pos_x = GTK_ENTRY(gtk_entry_new());
    entry_pos_y = GTK_ENTRY(gtk_entry_new());
    projector_label_desc = GTK_LABEL(gtk_label_new("Position:"));
    projector_label_showing = GTK_LABEL(gtk_label_new("Currently showing:"));
    projector_label_showing_var = GTK_LABEL(gtk_label_new(S_PROJECTOR_VIDEO_STREAM));

    option->m_display_settings->entry_pos_x = entry_pos_x;
    option->m_display_settings->entry_pos_y = entry_pos_y;
    option->m_display_settings->btn_pos_apply = btn_pos_apply;
    option->m_display_settings->currently_showing = projector_label_showing_var;

    option->m_controls->btn_open_display = btn_display_open;
    option->m_controls->btn_decklink = btn_decklink;
    option->m_controls->btn_tab_switch = btn_tab_switch;
    option->m_controls->btn_webview = btn_webview;

    option->m_decklink_options->m_input = sdi;
    option->m_decklink_options->btn_other = btn_sdi;
    option->m_decklink_options->label_current_input = decklink_label_current_input;
    option->m_decklink_options->btn_hdmi = btn_hdmi;
    option->m_decklink_options->btn_sdi = btn_sdi;
    gtk_widget_set_sensitive(GTK_WIDGET(btn_sdi), FALSE);

    gtk_box_pack_start(vbox, GTK_WIDGET(preview_grid), FALSE, FALSE, 0);

    gtk_box_pack_start(vbox, GTK_WIDGET(decklink_label), FALSE, FALSE, 5);
    gtk_box_pack_start(vbox, GTK_WIDGET(decklink_options), TRUE, TRUE, 10);

    gtk_box_pack_start(vbox, GTK_WIDGET(webview_label), FALSE, FALSE, 0);
    gtk_box_pack_start(vbox, GTK_WIDGET(webview_options), TRUE, TRUE, 0);
    gtk_box_pack_start(webview_options, GTK_WIDGET(projector_options), TRUE, TRUE, 0);

    gtk_box_pack_start(vbox, GTK_WIDGET(controls_label), FALSE, FALSE, 0);
    gtk_box_pack_start(vbox, GTK_WIDGET(controls_box), TRUE, TRUE, 0);

    gtk_box_pack_end(controls_box, GTK_WIDGET(btn_lock), TRUE, TRUE, 10); // Set all buttons to insensitive.
    gtk_box_pack_end(controls_box, GTK_WIDGET(btn_display_open), TRUE, TRUE, 10);
    gtk_box_pack_end(controls_box, GTK_WIDGET(btn_tab_switch), TRUE, TRUE, 10);
    gtk_box_pack_end(controls_box, GTK_WIDGET(btn_webview), TRUE, TRUE, 10);
    gtk_box_pack_end(controls_box, GTK_WIDGET(btn_decklink), TRUE, TRUE, 10);

    gtk_grid_attach(decklink_options, GTK_WIDGET(btn_hdmi), 1, 0, 2, 2);
    gtk_grid_attach(decklink_options, GTK_WIDGET(btn_sdi), 3, 0, 2, 2);
    gtk_grid_attach(decklink_options, GTK_WIDGET(decklink_label_desc), 0, 0, 1, 1);
    gtk_grid_attach(decklink_options, GTK_WIDGET(decklink_label_current_input), 0, 1, 1, 1);

    gtk_grid_attach(projector_options, GTK_WIDGET(projector_label_desc), 0, 0, 1, 2);
    gtk_grid_attach(projector_options, GTK_WIDGET(entry_pos_x), 1, 0, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(entry_pos_y), 2, 0, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(btn_pos_apply), 3, 0, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(projector_label_showing), 0, 2, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(projector_label_showing_var), 1, 2, 2, 1);    

    decklink_stream_gst(option);
    setup_stream_ui(preview_grid, GTK_WINDOW(window), option->m_decklink_options->m_stream);

    g_object_set(decklink_label_desc, "margin", 12, NULL);
    g_object_set(btn_hdmi, "margin", 6, NULL);
    g_object_set(btn_sdi, "margin", 6, NULL);
    g_object_set(decklink_label_current_input, "margin", 12, NULL);

    g_object_set(controls_box, "margin-bottom", 12, NULL);

    g_object_set(projector_label_desc, "margin", 12, NULL);
    g_object_set(entry_pos_x, "margin", 6, NULL);
    g_object_set(entry_pos_y, "margin", 6, NULL);
    g_object_set(projector_label_showing, "margin", 12, NULL);
    gtk_label_set_xalign(projector_label_showing, 0.0);
    gtk_label_set_xalign(projector_label_desc, 0.0);
    gtk_entry_set_width_chars(entry_pos_x, 5);
    gtk_entry_set_width_chars(entry_pos_y, 5);
    gtk_entry_set_placeholder_text(entry_pos_x, "X");
    gtk_entry_set_placeholder_text(entry_pos_y, "Y");
    gtk_entry_set_input_purpose(entry_pos_x, GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_input_purpose(entry_pos_y, GTK_INPUT_PURPOSE_NUMBER);

    g_signal_connect(G_OBJECT(btn_pos_apply), "clicked", G_CALLBACK(set_display_window_pos_cb), option);

    if (option->is_display_open == TRUE) {
        gtk_widget_set_sensitive(GTK_WIDGET(btn_display_open), FALSE);
    }

    g_signal_connect(G_OBJECT(btn_decklink), "clicked", G_CALLBACK(tab_decklink_cb), tab);
    g_signal_connect(G_OBJECT(btn_webview), "clicked", G_CALLBACK(tab_webview_cb), tab);
    g_signal_connect(G_OBJECT(btn_tab_switch), "clicked", G_CALLBACK(tab_nextpage_cb), tab);
    g_signal_connect(G_OBJECT(btn_display_open), "clicked", G_CALLBACK(open_display_window_cb), option);
    g_signal_connect(G_OBJECT(btn_lock), "clicked", G_CALLBACK(gui_lock_cb), option);

    g_signal_connect(G_OBJECT(btn_hdmi), "clicked", G_CALLBACK(decklink_input_hdmi), option->m_decklink_options);
    g_signal_connect(G_OBJECT(btn_sdi), "clicked", G_CALLBACK(decklink_input_sdi), option->m_decklink_options);
    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event_cb), option);

    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vbox));

    gtk_widget_show_all(window);
}

void tab_decklink_cb(GtkButton *button, GtkNotebook *tab) {
    UNUSED(button);
    gtk_notebook_set_current_page(tab, 0);
}

void tab_webview_cb(GtkButton *button, GtkNotebook *tab) {
    UNUSED(button);
    gtk_notebook_set_current_page(tab, 1);
}

void tab_nextpage_cb(GtkButton *button, GtkNotebook *tab) {
    UNUSED(button);
    if (gtk_notebook_get_current_page(tab) == gtk_notebook_get_n_pages(tab) - 1) {
        gtk_notebook_set_current_page(tab, 0);
    } else {
        gtk_notebook_next_page(tab);
    }
}
	
void window_decoration_toggle_cb(GtkButton *button, display_settings *tab) {
    UNUSED(button);
	GdkWindow *window;
	window = gtk_widget_get_window(GTK_WIDGET(tab));

	if(gtk_window_get_decorated(GTK_WINDOW(window))) {
		gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	} else {
		gtk_window_set_decorated(GTK_WINDOW(window), TRUE);
	}
}

void decklink_input_hdmi(GtkButton *button, decklink_options *option) {
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(option->btn_other), TRUE);
    option->btn_other = button;
    option->m_input = sdi;
	gint* intval;
	GstElement *cap;
	cap = gst_bin_get_by_name (GST_BIN (option->m_stream->pipeline), "source");
    gtk_label_set_text(option->label_current_input, "Current input: HDMI");
    stop_cb(option->m_stream);
	g_object_set(option->m_stream->source, "connection",2, NULL);
	// gst_caps_set_value(cap, "connection","2");
	g_object_get(cap,"connection", &intval, NULL);
    play_cb(option->m_stream);
	g_print("%i\n",GPOINTER_TO_INT(intval));
}

void decklink_input_sdi(GtkButton *button, decklink_options *option) {
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(option->btn_other), TRUE);
    option->btn_other = button;
    option->m_input = hdmi;
	gint* intval;
	GstElement *cap;
	cap = gst_bin_get_by_name (GST_BIN (option->m_stream->pipeline), "source");
    gtk_label_set_text(option->label_current_input, "Current input: SDI");
	// gst_caps_set_value(cap, "connection","1");
    stop_cb(option->m_stream);
	g_object_set(cap, "connection", 1, NULL);
	g_object_get(cap, "connection", &intval, NULL);

    play_cb(option->m_stream);
	g_print("%i\n",GPOINTER_TO_INT(intval));
}

void open_display_window_cb(GtkButton *button, options *option) {
    GtkWindow *display_window;

    display_window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    option->display_window = display_window;
    option->m_display_settings->tab = GTK_NOTEBOOK(gtk_notebook_new());

    g_signal_connect(G_OBJECT(option->m_controls->btn_decklink), "clicked", G_CALLBACK(tab_decklink_cb), option->m_display_settings->tab);
    g_signal_connect(G_OBJECT(option->m_controls->btn_webview), "clicked", G_CALLBACK(tab_webview_cb), option->m_display_settings->tab);
    g_signal_connect(G_OBJECT(option->m_controls->btn_tab_switch), "clicked", G_CALLBACK(tab_nextpage_cb), option->m_display_settings->tab);

    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
    display_window_init(GTK_WIDGET(option->display_window), option);
}

void set_display_window_pos_cb(GtkButton *button, options *option) {
    UNUSED(button);
    option->m_display_settings->pos_x = atoi(gtk_entry_get_text(entry_pos_x));
    option->m_display_settings->pos_y = atoi(gtk_entry_get_text(entry_pos_y));

    gtk_window_move(option->display_window, option->m_display_settings->pos_x, option->m_display_settings->pos_y);
    printf("moved window to %i,%i\n", option->m_display_settings->pos_x, option->m_display_settings->pos_y);
}

void gui_lock_cb(GtkButton *button, options *option) {
	UNUSED(button);
    if (option->m_controls->locked == TRUE) {
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->btn_pos_apply), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->entry_pos_x), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->entry_pos_y), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_decklink_options->btn_hdmi), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_decklink_options->btn_sdi), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_decklink_options->btn_other), FALSE);
        option->m_controls->locked = FALSE;
        printf("State: Unlocked\n");
    } else {
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->btn_pos_apply), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->entry_pos_x), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->entry_pos_y), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_decklink_options->btn_hdmi), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_decklink_options->btn_sdi), FALSE);
        option->m_controls->locked = TRUE;
        printf("State: Locked\n");
    }
}