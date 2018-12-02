#include "rest/webservice.h"
#include "rest/api.h"

#include <jansson.h>
#include <libconfig.h>
#include <pthread.h>

void webservice_init(options *option) {
    printf("TEST\n");
	
    g_mutex_init((GMutex *)&option->webservice_lock);
    g_cond_init((GCond *)&option->webservice_cond);

    option->thread_webservice = g_thread_new("webservice",  init_rest_api, option);
}

// void webservice_destroy(pthread_t webservice) {
// }

void init_rest_api(options *option) {
    struct _u_instance instance;

    option->m_webservice = (webservice *)malloc(sizeof(webservice));

    init_json(&option->cfg, option);

    // Initialize instance with the port number
    if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
        fprintf(stderr, "Error ulfius_init_instance, abort\n");
        return;
    }
    // Endpoint list declaration
    ulfius_add_endpoint_by_val(&instance, "POST", "/control", "?:foo", 0, &option_post_cb, option);

    // Start the framework
    if (ulfius_start_framework(&instance) == U_OK) {
        printf("::Start framework on port %d\n", instance.port);

        g_mutex_lock((GMutex *)&option->webservice_lock);
        // Wait for a signal to shut down.
        g_cond_wait((GCond *)&option->webservice_cond, (GMutex *)&option->webservice_lock);

    } else {
        fprintf(stderr, "Error starting framework\n");
    }

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);
    printf("::End framework\n");
	return;
}

void init_json(config_t *cfg, options *option) {
    option->m_webservice->root = json_object();

    int tab;
    printf("test\n");
    config_lookup_int(cfg, "tab", &tab);
    if (tab == 0) {
        json_object_set_new(option->m_webservice->root, "show", json_string("video"));
    } else if (tab == 1) {
        json_object_set_new(option->m_webservice->root, "show", json_string("web"));
    }

    json_object_set_new(option->m_webservice->root, "input", json_string("sdi"));
}