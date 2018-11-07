
#include "gui/control_window.h"
#include "gui/webview.h"
#include "auxiliary.h"

void control_window_init(GtkWidget *window, options *option, GtkNotebook *tab) {
    gtk_window_set_title(GTK_WINDOW(window), MAIN_WINDOW);

    option->display_window = GTK_WINDOW(gtk_widget_get_window(GTK_WIDGET(tab)));
    option->m_controls->locked = FALSE;

    GtkBox *vbox, *webview_options, *controls_box;
    GtkGrid *decklink_options, *projector_options;

    GtkGrid *preview_grid;

    GtkLabel *decklink_label, *webview_label, *controls_label;

    vbox = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 10));
    decklink_options = GTK_GRID(gtk_grid_new());
    projector_options = GTK_GRID(gtk_grid_new());
    webview_options = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10));
    controls_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30));

    preview_grid = GTK_GRID(gtk_grid_new());

    decklink_label = GTK_LABEL(gtk_label_new("- Video stream -"));
    webview_label = GTK_LABEL(gtk_label_new("- Projector -"));
    controls_label = GTK_LABEL(gtk_label_new("- Controls -"));


    decklink_stream_gst(option);
    setup_stream_ui(preview_grid, GTK_WINDOW(window), option->m_decklink_options->m_stream);
    gtk_box_pack_start(vbox, GTK_WIDGET(preview_grid), FALSE, FALSE, 0);


    projector_settings_add(decklink_options, option);
    gtk_box_pack_start(vbox, GTK_WIDGET(decklink_label), FALSE, FALSE, 5);
    gtk_box_pack_start(vbox, GTK_WIDGET(decklink_options), TRUE, TRUE, 10);


    video_stream_control_add(projector_options, option);
    gtk_box_pack_start(vbox, GTK_WIDGET(webview_label), FALSE, FALSE, 0);
    gtk_box_pack_start(vbox, GTK_WIDGET(webview_options), TRUE, TRUE, 0);
    gtk_box_pack_start(webview_options, GTK_WIDGET(projector_options), TRUE, TRUE, 0);


    controls_add(controls_box, option, tab);
    gtk_box_pack_start(vbox, GTK_WIDGET(controls_label), FALSE, FALSE, 0);
    gtk_box_pack_start(vbox, GTK_WIDGET(controls_box), TRUE, TRUE, 0);


    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event_cb), option);

    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vbox));

    gtk_widget_show_all(window);
}

void projector_settings_add(GtkGrid *decklink_options, options *option) {
    GtkButton *btn_hdmi, *btn_sdi;
    GtkLabel *decklink_label_desc, *decklink_label_current_input;

    btn_hdmi = GTK_BUTTON(gtk_button_new_with_label("HDMI Input"));
    btn_sdi = GTK_BUTTON(gtk_button_new_with_label("SDI Input"));

    decklink_label_desc = GTK_LABEL(gtk_label_new("Choose Decklink card input:"));
    decklink_label_current_input = GTK_LABEL(gtk_label_new("Current input: SDI"));

    option->m_decklink_options->m_input = sdi;
    option->m_decklink_options->btn_other = btn_sdi;
    option->m_decklink_options->label_current_input = decklink_label_current_input;
    option->m_decklink_options->btn_hdmi = btn_hdmi;
    option->m_decklink_options->btn_sdi = btn_sdi;

    gtk_widget_set_sensitive(GTK_WIDGET(btn_sdi), FALSE);
    gtk_label_set_xalign(decklink_label_current_input, 0.0);

    gtk_grid_attach(decklink_options, GTK_WIDGET(btn_hdmi), 1, 0, 2, 2);
    gtk_grid_attach(decklink_options, GTK_WIDGET(btn_sdi), 3, 0, 2, 2);
    gtk_grid_attach(decklink_options, GTK_WIDGET(decklink_label_desc), 0, 0, 1, 1);
    gtk_grid_attach(decklink_options, GTK_WIDGET(decklink_label_current_input), 0, 1, 1, 1);

    g_object_set(decklink_label_desc, "margin", 12, NULL);
    g_object_set(btn_hdmi, "margin", 6, NULL);
    g_object_set(btn_sdi, "margin", 6, NULL);
    g_object_set(decklink_label_current_input, "margin", 12, NULL);

    g_signal_connect(G_OBJECT(btn_hdmi), "clicked", G_CALLBACK(decklink_input_hdmi), option->m_decklink_options);
    g_signal_connect(G_OBJECT(btn_sdi), "clicked", G_CALLBACK(decklink_input_sdi), option->m_decklink_options);
}

void video_stream_control_add(GtkGrid *projector_options, options *option) {
    GtkLabel *projector_label_desc, *projector_label_showing_var;

    option->m_display_settings->btn_pos_apply = GTK_BUTTON(gtk_button_new_with_label("Apply"));
    option->m_display_settings->entry_pos_x = GTK_ENTRY(gtk_entry_new());
    option->m_display_settings->entry_pos_y = GTK_ENTRY(gtk_entry_new());
    projector_label_desc = GTK_LABEL(gtk_label_new("Position:"));
    option->m_display_settings->currently_showing = GTK_LABEL(gtk_label_new("Currently showing:"));
    projector_label_showing_var = GTK_LABEL(gtk_label_new(S_PROJECTOR_VIDEO_STREAM));
    option->m_display_settings->entry_url = GTK_ENTRY(gtk_entry_new());
    option->m_display_settings->btn_url_search = GTK_BUTTON(gtk_button_new_with_label("Search"));
    option->m_display_settings->btn_url_save = GTK_BUTTON(gtk_button_new_with_label("Save URL"));

    gtk_grid_attach(projector_options, GTK_WIDGET(projector_label_desc), 0, 0, 1, 2);
    gtk_grid_attach(projector_options, GTK_WIDGET(option->m_display_settings->entry_pos_x), 1, 0, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(option->m_display_settings->entry_pos_y), 2, 0, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(option->m_display_settings->btn_pos_apply), 3, 0, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(option->m_display_settings->currently_showing), 0, 2, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(projector_label_showing_var), 1, 2, 2, 1);    
    gtk_grid_attach(projector_options, GTK_WIDGET(option->m_display_settings->entry_url), 0, 3, 2, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(option->m_display_settings->btn_url_search), 2, 3, 1, 1);
    gtk_grid_attach(projector_options, GTK_WIDGET(option->m_display_settings->btn_url_save), 3, 3, 1, 1);

    g_object_set(projector_label_desc, "margin", 12, NULL);
    g_object_set(option->m_display_settings->entry_pos_x, "margin", 6, NULL);
    g_object_set(option->m_display_settings->entry_pos_y, "margin", 6, NULL);
    g_object_set(option->m_display_settings->currently_showing, "margin", 12, NULL);
    gtk_label_set_xalign(option->m_display_settings->currently_showing, 0.0);
    gtk_label_set_xalign(projector_label_desc, 0.0);
    gtk_entry_set_width_chars(option->m_display_settings->entry_pos_x, 5);
    gtk_entry_set_width_chars(option->m_display_settings->entry_pos_y, 5);
    gtk_entry_set_placeholder_text(option->m_display_settings->entry_pos_x, "X");
    gtk_entry_set_placeholder_text(option->m_display_settings->entry_pos_y, "Y");
    gtk_entry_set_text(option->m_display_settings->entry_pos_x, g_strdup_printf("%i", option->m_display_settings->pos_x));
    gtk_entry_set_text(option->m_display_settings->entry_pos_y, g_strdup_printf("%i", option->m_display_settings->pos_y));
    gtk_entry_set_input_purpose(option->m_display_settings->entry_pos_x, GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_input_purpose(option->m_display_settings->entry_pos_y, GTK_INPUT_PURPOSE_NUMBER);
    gtk_widget_set_size_request(GTK_WIDGET(option->m_display_settings->entry_url), 500, 30);
    g_object_set(option->m_display_settings->entry_url, "margin", 6, NULL);

    g_signal_connect(G_OBJECT(option->m_display_settings->btn_pos_apply), "clicked", G_CALLBACK(set_display_window_pos_cb), option);
    g_signal_connect(option->m_display_settings->btn_url_search, "clicked", G_CALLBACK(url_entry_query), option);
    g_signal_connect(option->m_display_settings->btn_url_save, "clicked", G_CALLBACK(url_entry_save), option);
    g_signal_connect(option->m_display_settings->entry_url, "activate", G_CALLBACK(url_entry_query), option);
}

void controls_add(GtkBox *controls_box, options *option, GtkNotebook *tab) {
    GtkButton *btn_lock;

    option->m_controls->btn_open_display = GTK_BUTTON(gtk_button_new_with_label("Open player"));
    option->m_controls->btn_decklink = GTK_BUTTON(gtk_button_new_with_label(S_PROJECTOR_VIDEO_STREAM));
    option->m_controls->btn_tab_switch = GTK_BUTTON(gtk_button_new_with_label("Switch"));
    option->m_controls->btn_webview  = GTK_BUTTON(gtk_button_new_with_label(S_PROJECTOR_WEB_VIEW));
    btn_lock = GTK_BUTTON(gtk_button_new_with_label("LOCK"));

    gtk_box_pack_end(controls_box, GTK_WIDGET(btn_lock), TRUE, TRUE, 10); // Set all buttons to insensitive.
    gtk_box_pack_end(controls_box, GTK_WIDGET(option->m_controls->btn_open_display), TRUE, TRUE, 10);
    gtk_box_pack_end(controls_box, GTK_WIDGET(option->m_controls->btn_tab_switch), TRUE, TRUE, 10);
    gtk_box_pack_end(controls_box, GTK_WIDGET(option->m_controls->btn_webview), TRUE, TRUE, 10);
    gtk_box_pack_end(controls_box, GTK_WIDGET(option->m_controls->btn_decklink), TRUE, TRUE, 10);

    if (option->is_display_open == TRUE) {
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_controls->btn_open_display), FALSE);
    }

    g_object_set(controls_box, "margin-bottom", 12, NULL);

    g_signal_connect(G_OBJECT(option->m_controls->btn_decklink), "clicked", G_CALLBACK(tab_decklink_cb), tab);
    g_signal_connect(G_OBJECT(option->m_controls->btn_webview), "clicked", G_CALLBACK(tab_webview_cb), tab);
    g_signal_connect(G_OBJECT(option->m_controls->btn_tab_switch), "clicked", G_CALLBACK(tab_nextpage_cb), tab);
    g_signal_connect(G_OBJECT(option->m_controls->btn_open_display), "clicked", G_CALLBACK(open_display_window_cb), option);
    g_signal_connect(G_OBJECT(btn_lock), "clicked", G_CALLBACK(gui_lock_cb), option);
}


//
// Callbacks
//
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
    int pos_x = atoi(gtk_entry_get_text(option->m_display_settings->entry_pos_x));
    int pos_y = atoi(gtk_entry_get_text(option->m_display_settings->entry_pos_y));

    option->m_display_settings->pos_x = pos_x;
    option->m_display_settings->pos_y = pos_y;
    config_setting_t *setting, *root;

    root = config_root_setting(&option->cfg);

    setting = config_lookup(&option->cfg, "display_x");
    if(!setting) {
        setting = config_setting_add(root, "display_x", CONFIG_TYPE_INT);
    }
    config_setting_set_int(setting, pos_x);
    
    setting = config_lookup(&option->cfg, "display_y");
    if(!setting) {
        setting = config_setting_add(root, "display_y", CONFIG_TYPE_INT);
    }
    config_setting_set_int(setting, pos_y);
	FILE *file = fopen(option->file_cfg, "w+");
    config_write(&option->cfg, file);
	fclose(file);
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
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->entry_url), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->btn_url_search), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->btn_url_save), TRUE);

        option->m_controls->locked = FALSE;
        printf("State: Unlocked\n");
    } else {
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->btn_pos_apply), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->entry_pos_x), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->entry_pos_y), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_decklink_options->btn_hdmi), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_decklink_options->btn_sdi), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->entry_url), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->btn_url_search), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(option->m_display_settings->btn_url_save), FALSE);
        option->m_controls->locked = TRUE;
        printf("State: Locked\n");
    }
}