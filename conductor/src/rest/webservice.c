#include "rest/webservice.h"
#include "rest/api.h"

#include <pthread.h>

void webservice_init(options *option) {
    printf("TEST\n");
    if(pthread_create(&option->thread_webservice, NULL, init_rest_api, option)) {
        fprintf(stderr, "Error creating thread\n");
        return;
    }
}

void webservice_destroy(pthread_t webservice) {
}

void init_rest_api(options *option) {

    pthread_mutex_lock(&option->end_lock);
    struct _u_instance instance;

    option->m_webservice = (webservice*)malloc(sizeof(webservice));

    // pthread_mutex_lock(&option->lock);
    // pthread_cond_wait(&option->start_cond, &option->lock);
    // Initialize instance with the port number
    if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
        fprintf(stderr, "Error ulfius_init_instance, abort\n");
        return (1);
    }
    // Endpoint list declaration
    ulfius_add_endpoint_by_val(&instance, "GET", "/helloworld", NULL, 0, &callback_hello_world, NULL);

    ulfius_add_endpoint_by_val(&instance, "POST", "/control", "?:foo", 0, &switch_display_cb, option);

    // ulfius_add_endpoint_by_val(&instance, "POST", "/control", "?:foo", 0, &switch_input_cb, option);


    // g_signal_connect(G_OBJECT(&instance), "switch-page", G_CALLBACK(switch_input_cb), option);
    // Start the framework
    if (ulfius_start_framework(&instance) == U_OK) {
        printf("::Start framework on port %d\n", instance.port);

        // Wait for the user to press <enter> on the console to quit the application
        // getchar();
        pthread_cond_wait(&option->end_cond, &option->end_lock);
    } else {
        fprintf(stderr, "Error starting framework\n");
    }

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);
    printf("::End framework\n");

    pthread_cond_signal(&option->end_cond);

    return;
}