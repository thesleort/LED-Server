#ifndef __REST_WEBSERVICE_H
#define __REST_WEBSERVICE_H

#include "options.h"

#include <ulfius.h>

void webservice_init(options *option);

void webservice_destroy(pthread_t webservice);

void init_rest_api(options *option);

#endif