#include "gui/api.h"


void tab_decklink_idle_cb(options *option) {
    tab_decklink_cb(NULL, option);
}

void tab_webview_idle_cb(options *option) {
    tab_webview_cb(NULL, option);
}

void tab_nextpage_idle_cb(options *option) {
    tab_nextpage_cb(NULL, option);
}