#include <webkit2/webkit2.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* fopen, fseek, ... */

#include "gui/webview.h"
#include "options.h"

// GtkBox *grid;
// GtkEntry *url;

void webview_add(GtkGrid *grid, options *option) {
    GtkButton *search_btn;
    // WebKitWebView *web_view;
    // url = malloc(sizeof(GtkEntry));
    option->m_display_settings->webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    search_btn = GTK_BUTTON(gtk_button_new());
    // web_view = option->m_display_settings->webview;
    // load_scripts(option);
    // web_view = malloc(sizeof(WebKitWebView));
    printf("Webview setup\n");

    option->m_display_settings->webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    webkit_web_view_load_uri(option->m_display_settings->webview, "http://www.w3schools.com/html/html5_video.asp");

    // grid = GTK_GRID(gtk_grid_new());
    option->m_display_settings->url = GTK_ENTRY(gtk_entry_new());
    search_btn = GTK_BUTTON(gtk_button_new_with_label("Connect"));

    gtk_widget_set_size_request(GTK_WIDGET(option->m_display_settings->webview), 1500, 550);
    gtk_widget_set_size_request(GTK_WIDGET(option->m_display_settings->url), 1600, 30);

    gtk_entry_set_placeholder_text(option->m_display_settings->url, webkit_web_view_get_uri(option->m_display_settings->webview));

    //In order: left, top, width, height

    gtk_grid_attach(grid, GTK_WIDGET(option->m_display_settings->webview), 0, 0, 100, 1);
    gtk_grid_attach(grid, GTK_WIDGET(option->m_display_settings->url), 0, 1, 70, 1);
    gtk_grid_attach(grid, GTK_WIDGET(search_btn), 70, 1, 30, 1);

    gtk_entry_set_text(option->m_display_settings->url, webkit_web_view_get_uri(option->m_display_settings->webview));

    // gtk_container_add(GTK_CONTAINER(window), GTK_GRID(grid));

    g_signal_connect(search_btn, "clicked", G_CALLBACK(url_entry_query), option->m_display_settings);
    g_signal_connect(option->m_display_settings->url, "activate", G_CALLBACK(url_entry_query), option->m_display_settings);

    WebKitWebInspector *inspector = webkit_web_view_get_inspector(WEBKIT_WEB_VIEW(option->m_display_settings->webview));
    webkit_web_inspector_show(WEBKIT_WEB_INSPECTOR(inspector));

    // g_signal_connect(window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    // g_signal_connect(web_view, "close", G_CALLBACK(closeWebViewCb), window);

    // Will get input from mouse and keyboard.
    // gtk_widget_grab_focus(GTK_WIDGET(web_view));
}

// void load_scripts(options *option) {
    // int size = 0;

    // FILE *fp = fopen("js/pause_video.js", "r");

    // fseek(fp, 0, SEEK_END); /* Go to end of file */
    // size = ftell(fp);      /* How many bytes did we pass ? */

    // /* Set position of stream to the beginning */
    // rewind(fp);

    // /* Allocate the buffer (no need to initialize it with calloc) */
    // option->m_display_settings->webview_pause_script = malloc((size) * sizeof(option->m_display_settings->webview_pause_script)); /* size + 1 byte for the \0 */

    // /* Read the file into the buffer */
    // fread(option->m_display_settings->webview_pause_script, size, 1, fp); /* Read 1 chunk of size bytes from fp into buffer */

    // /* NULL-terminate the buffer */
    // option->m_display_settings->webview_pause_script[size] = '\0';
    // option->m_display_settings->size = size;
    // printf("Script loaded\n");

    // FILE *file = fopen("js/pause_video.js", "r");
    // fseek(file, 0, 1);
    // gchar *content = ' ';
    // gssize length;
    // g_file_get_contents("js/pause_video.js", content, &length, NULL);
    // option->m_display_settings->webview_pause_script = content;
    // option->m_display_settings->size = length;

    // long len = ftell(file);
    // char *ret = malloc(len);

    // fseek(file, 0, SEEK_SET);
    // fread(ret, 1, len, file);

    // fclose(file);
    // option->m_display_settings->webview_pause_script = ret;
//     printf("Script loaded\n");
// }

gboolean webview_close_cb(WebKitWebView *web_view, GtkWidget *window) {
    UNUSED(web_view);
    gtk_widget_destroy(window);
    return TRUE;
}

void url_entry_query(GtkWidget *widget, display_settings *settings) {
    UNUSED(widget);
    char buf[512];
    snprintf(buf, sizeof(buf), "%s%s", "http://", gtk_entry_get_text(settings->url));
    printf("%s\n", buf);
    webkit_web_view_load_uri(settings->webview, buf);
    gtk_entry_set_placeholder_text(settings->url, webkit_web_view_get_uri(settings->webview));
}

// static void destroyWindowCb(GtkWidget *widget, GtkWidget *window) {
//     gtk_main_quit();
// }
