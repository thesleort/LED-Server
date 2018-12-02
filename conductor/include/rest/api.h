#ifndef __REST_API_H
#define __REST_API_H

#include "options.h"

#include <ulfius.h>

#define PORT 8080

int callback_hello_world(const struct _u_request *request, struct _u_response *response, void * user_data);

int option_post_cb(const struct _u_request *request, struct _u_response *response, options *option);

int switch_input_cb(const struct _u_request *request, struct _u_response *response, options *option);

char * print_map(const struct _u_map * map);

#endif