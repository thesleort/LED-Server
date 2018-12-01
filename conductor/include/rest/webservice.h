#ifndef __REST_WEBSERVICE_H
#define __REST_WEBSERVICE_H

#include "options.h"

#include <ulfius.h>
#include <jansson.h>
#include <libconfig.h>

void webservice_init(options *option);

void webservice_destroy(pthread_t webservice);

void init_rest_api(options *option);

void init_json(config_t *cfg, options *option);

#endif