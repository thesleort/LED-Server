#ifndef __API_H
#define __API_H

#include "gui/control_window.h"

gboolean idle_tab_decklink_cb(options *option);

gboolean idle_tab_webview_cb(options *option);

gboolean idle_tab_nextpage_cb(options *option);

gboolean idle_set_input_source_hdmi(options *option);

gboolean idle_set_input_source_sdi(options *option);

#endif