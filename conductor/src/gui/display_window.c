
#include "gui/display_window.h"
#include "gui/webview.h"
#include "auxiliary.h"

#include <libconfig.h>
#include <glib.h>
typedef void (*FPtr)(void);
void display_window_init(GtkWidget *window, options *option) {
    GtkNotebook *tab = option->m_display_settings->tab;

    option->display_window = GTK_WINDOW(window);
    option->is_display_open = TRUE;

    GtkGrid *webview_grid;
    GtkLabel *webview_label;

    GtkGrid *stream_grid;
    GtkLabel *stream_label;

    gtk_window_set_title(GTK_WINDOW(window), DISPLAY_WINDOW);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

    webview_grid = GTK_GRID(gtk_grid_new());
    webview_label = GTK_LABEL(gtk_label_new(S_PROJECTOR_WEB_VIEW));

    stream_grid = GTK_GRID(gtk_grid_new());
    stream_label = GTK_LABEL(gtk_label_new(S_PROJECTOR_VIDEO_STREAM));

    // Setup tab: Start

    webview_add(webview_grid, option);

    setup_stream_ui(stream_grid, GTK_WINDOW(window), option->m_decklink_options->m_stream);

    gtk_notebook_set_show_tabs(tab, FALSE);
    gtk_notebook_set_show_border(tab, FALSE);
    gtk_notebook_append_page(tab, GTK_WIDGET(stream_grid), GTK_WIDGET(stream_label));
    gtk_notebook_append_page(tab, GTK_WIDGET(webview_grid), GTK_WIDGET(webview_label));

    g_signal_connect(G_OBJECT(tab), "switch-page", G_CALLBACK(switch_tab_cb), option);
    // Setup tab: End

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(tab));
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 550);

    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(display_close_cb), option);

    gtk_widget_show_all(window);

    gtk_notebook_set_current_page(tab, load_current_page_setting(option));

    gtk_window_move(GTK_WINDOW(window), option->m_display_settings->pos_x, option->m_display_settings->pos_y);
}

void display_close_cb(GtkWidget *widget, GdkEvent *event, options *option) {
    UNUSED(event);
    stop_cb(option->m_decklink_options->m_stream);
    option->is_display_open = FALSE;
    gtk_widget_destroy(widget);
    webview_close_cb(option->m_display_settings->webview, widget);
    gtk_widget_set_sensitive(GTK_WIDGET(option->m_controls->btn_open_display), TRUE);

    // TODO: Remove compiler warning.
    g_signal_handlers_disconnect_by_func(option->m_controls->btn_tab_switch, tab_nextpage_cb, option);
    printf("Closed: Display Window\n");
}

void switch_tab_cb(GtkNotebook *notebook, GtkWidget *page, guint page_num, options *option) {
    printf("Calling: switch_tab_cb\n");

    gtk_label_set_text(option->m_display_settings->currently_showing, gtk_notebook_get_tab_label_text(notebook, page));
    switch (page_num) {
    case 0:
        printf("page: 0\n");
        play_cb(option->m_decklink_options->m_stream);
        webkit_web_view_run_javascript(option->m_display_settings->webview, option->m_display_settings->webview_pause_script, NULL, finish, NULL);
        break;
    case 1:
        printf("page: 1\n");
        // pause_cb(option->m_decklink_options->m_stream);
        webkit_web_view_run_javascript(option->m_display_settings->webview, option->m_display_settings->webview_play_script, NULL, finish, NULL);
        break;
    }
}

void finish() {
    printf("Script done\n");
}

int load_current_page_setting(options *option) {
    config_setting_t *root, *setting;
    int tab;
    root = config_root_setting(&option->cfg);

    setting = config_lookup(&option->cfg, "tab");
    if (!setting) {
        setting = config_setting_add(root, "tab", CONFIG_TYPE_INT);
        config_setting_set_int(setting, 0);
        FILE *file = fopen(option->file_cfg, "w+");
        config_write(&option->cfg, file);
        fclose(file);
    }
    config_lookup_int(&option->cfg, "tab", &tab);

    return tab;
}
