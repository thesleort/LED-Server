#include "rest/api.h"
#include "options.h"
#include "gui/api.h"

#include <ulfius.h>
#include <gtk/gtk.h>
#include <string.h>

int callback_hello_world(const struct _u_request *request, struct _u_response *response, void *user_data) {
    ulfius_set_string_body_response(response, 200, "Hello World!");
    return U_CALLBACK_CONTINUE;
}

int switch_input_cb(const struct _u_request *request, struct _u_response *response, options *option) {

    printf("Lengths: %i, POS: %i\n", request->map_url->nb_values, option->m_display_settings->pos_x);
    for (unsigned key = 0; key < request->map_url->nb_values; ++key) {
        if (strcmp(request->map_url->keys[key], "show") == 0) {
            printf("SHOW\n");

            if (strcmp(request->map_url->values[key], "next") == 0) {
                printf("NEXT\n");
                g_idle_add((GSourceFunc) tab_nextpage_idle_cb, option);
                ulfius_set_string_body_response(response, 200, "showing: next\n");
                printf("NEXT\n");
            } else if (strcmp(request->map_url->values[key], "web") == 0) {
                printf("WEB\n");
                g_idle_add((GSourceFunc) tab_webview_idle_cb, option);
                ulfius_set_string_body_response(response, 200, "showing: web\n");
            } else if (strcmp(request->map_url->values[key], "video") == 0) {
                
                g_idle_add((GSourceFunc) tab_decklink_idle_cb, option);
            }
        }
    }
    return U_CALLBACK_CONTINUE;
}

int example_cb(const struct _u_request *request, struct _u_response *response, options *option) {
    // char *url_params = print_map(request->map_url), *headers = print_map(request->map_header), *cookies = print_map(request->map_cookie),
    //      *post_params = print_map(request->map_post_body);

    // char *response_body = sprintf("Hello World!\n\n  method is %s\n  url is %s\n\n  parameters from the url are \n%s\n\n  cookies are \n%s\n\n  headers are \n%s\n\n  post parameters are \n%s\n\n  user data is %s\n\n",
    //
    // char *user_data;

    char *url_params = print_map(request->map_url);
    char *headers = print_map(request->map_header);
    char *cookies = print_map(request->map_cookie);
    char *post_params = print_map(request->map_post_body);

    char buffer[512];
    char *response_body = sprintf(buffer, "Hello World!\n\n  method is %s\n  url is %s\n\n  parameters from the url are \n%s\n\n  cookies are \n%s\n\n  headers are \n%s\n\n  post parameters are \n%s\n\n",
                                  request->http_verb, request->http_url, url_params, cookies, headers, post_params);
    // char *response_body = sprintf("Page switched\n", user_data);

    printf("%s\n", buffer);

    ulfius_set_string_body_response(response, 200, "response_body\n");
    free(url_params);
    // free(response_body);
    return U_CALLBACK_CONTINUE;
}

char *print_map(const struct _u_map *map) {
    char *line, *to_return = NULL;
    const char **keys, *value;
    int len, i;
    if (map != NULL) {
        keys = u_map_enum_keys(map);
        for (i = 0; keys[i] != NULL; i++) {
            value = u_map_get(map, keys[i]);
            len = snprintf(NULL, 0, "key is %s, value is %s", keys[i], value);
            line = malloc((len + 1) * sizeof(char));
            snprintf(line, (len + 1), "key is %s, value is %s", keys[i], value);
            if (to_return != NULL) {
                len = strlen(to_return) + strlen(line) + 1;
                to_return = realloc(to_return, (len + 1) * sizeof(char));
                if (strlen(to_return) > 0) {
                    strcat(to_return, "\n");
                }
            } else {
                to_return = malloc((strlen(line) + 1) * sizeof(char));
                to_return[0] = 0;
            }
            strcat(to_return, line);
            free(line);
        }
        return to_return;
    } else {
        return NULL;
    }
}