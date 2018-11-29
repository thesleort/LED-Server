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
    struct _u_instance instance;

    // Initialize instance with the port number
    if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
        fprintf(stderr, "Error ulfius_init_instance, abort\n");
        return (1);
    }
    printf("TEST\n");
    // Endpoint list declaration
    ulfius_add_endpoint_by_val(&instance, "GET", "/helloworld", NULL, 0, &callback_hello_world, NULL);

    ulfius_add_endpoint_by_val(&instance, "POST", "/control", "?:foo", 0, &switch_input_cb, option);

    // g_signal_connect(G_OBJECT(&instance), "switch-page", G_CALLBACK(switch_input_cb), option);
    // Start the framework
    if (ulfius_start_framework(&instance) == U_OK) {
        printf("Start framework on port %d\n", instance.port);

        // Wait for the user to press <enter> on the console to quit the application
        getchar();
    } else {
        fprintf(stderr, "Error starting framework\n");
    }
    printf("End framework\n");

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);

    return 0;
}