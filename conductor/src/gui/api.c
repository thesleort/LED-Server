#include "gui/api.h"


void idle_tab_decklink_cb(options *option) {
    tab_decklink_cb(NULL, option);
}

void idle_tab_webview_cb(options *option) {
    tab_webview_cb(NULL, option);
}

void idle_tab_nextpage_cb(options *option) {
    tab_nextpage_cb(NULL, option);
}

void idle_set_input_source_hdmi(options *option) {
    decklink_input_hdmi(option->m_decklink_options->btn_hdmi, option->m_decklink_options);
}

void idle_set_input_source_sdi(options *option) {
    decklink_input_sdi(option->m_decklink_options->btn_sdi, option->m_decklink_options);
}