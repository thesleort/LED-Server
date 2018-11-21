#include <webkit2/webkit2.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* fopen, fseek, ... */
#include <libconfig.h>

#include "gui/webview.h"
#include "options.h"

void webview_add(GtkGrid *grid, options *option) {
    option->m_display_settings->webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    load_scripts(option);
    printf("Webview setup\n");

    option->m_display_settings->webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    option->m_display_settings->web_settings = webkit_web_view_get_settings(option->m_display_settings->webview);

    config_lookup_string(&option->cfg, "url", (const char **)&option->m_display_settings->website_url);
    printf("WEBSITE: %s\n", option->m_display_settings->website_url);

    url_entry_query(NULL, option);

    gtk_widget_set_size_request(GTK_WIDGET(option->m_display_settings->webview), 1500, 550);

    gtk_entry_set_text(option->m_display_settings->entry_url, option->m_display_settings->website_url);

    //In order: left, top, width, height

    gtk_grid_attach(grid, GTK_WIDGET(option->m_display_settings->webview), 0, 0, 100, 1);

    WebKitWebInspector *inspector = webkit_web_view_get_inspector(WEBKIT_WEB_VIEW(option->m_display_settings->webview));
    webkit_web_inspector_show(WEBKIT_WEB_INSPECTOR(inspector));

    webkit_settings_set_enable_javascript(option->m_display_settings->web_settings, TRUE);
    webkit_settings_set_enable_mediasource(option->m_display_settings->web_settings, TRUE);

    config_setting_t *root, *setting;
    const char *decoder[8];

    root = config_root_setting(&option->cfg);

    setting = config_lookup(&option->cfg, "decoder");
    if (!setting) {
        setting = config_setting_add(root, "decoder", CONFIG_TYPE_STRING);
        config_setting_set_string(setting, "software");
        FILE *file = fopen(option->file_cfg, "w+");
        config_write(&option->cfg, file);
        fclose(file);
    }
    config_lookup_string(&option->cfg, "decoder", decoder);
    if(strcmp(*decoder, "software")) {
        webkit_settings_set_hardware_acceleration_policy(option->m_display_settings->web_settings, WEBKIT_HARDWARE_ACCELERATION_POLICY_NEVER);
    } else if(strcmp(*decoder, "hardware")) {
        webkit_settings_set_hardware_acceleration_policy(option->m_display_settings->web_settings, WEBKIT_HARDWARE_ACCELERATION_POLICY_ALWAYS);
    }
}

void load_scripts(options *option) {
    gchar *pause_video;
    gchar *play_video;
    gsize pause_length;
    gsize play_length;

    g_file_get_contents("js/pause_video.js", &pause_video, &pause_length, NULL);
    option->m_display_settings->webview_pause_script = pause_video;
    option->m_display_settings->pause_size = pause_length;

    g_file_get_contents("js/play_video.js", &play_video, &play_length, NULL);
    option->m_display_settings->webview_play_script = play_video;
    option->m_display_settings->play_size = play_length;
}

gboolean webview_close_cb(WebKitWebView *web_view, GtkWidget *window) {
    UNUSED(web_view);
    gtk_widget_destroy(window);
    return TRUE;
}

void webview_refresh_cb(GtkWidget *widget, options *option) {
    UNUSED(widget);
    webkit_web_view_reload(option->m_display_settings->webview);
    printf("Page refreshed\n");
}

void url_entry_query(GtkWidget *widget, options *option) {
    UNUSED(widget);
    char buf[512];
    if (webkit_web_view_get_uri(option->m_display_settings->webview) == NULL) {
        snprintf(buf, sizeof(buf), "%s%s", "http://", option->m_display_settings->website_url);
    } else {
        snprintf(buf, sizeof(buf), "%s%s", "http://", gtk_entry_get_text(option->m_display_settings->entry_url));
    }

    printf("%s\n", buf);
    webkit_web_view_load_uri(option->m_display_settings->webview, buf);
    gtk_entry_set_placeholder_text(option->m_display_settings->entry_url, option->m_display_settings->website_url);
}

void url_entry_save(GtkWidget *widget, options *option) {
    UNUSED(widget);
    char buf[512];
    snprintf(buf, sizeof(buf), "%s", gtk_entry_get_text(option->m_display_settings->entry_url));
    config_setting_t *setting = config_lookup(&option->cfg, "url");
    if (!setting) {
        config_setting_t *root = config_root_setting(&option->cfg);
        setting = config_setting_add(root, "url", CONFIG_TYPE_STRING);
    }
    printf("SETTING: %i\n", config_setting_set_string(setting, buf));
    FILE *file = fopen(option->file_cfg, "w+");
    config_write(&option->cfg, file);
    fclose(file);
    gtk_entry_set_placeholder_text(option->m_display_settings->entry_url, webkit_web_view_get_uri(option->m_display_settings->webview));
}