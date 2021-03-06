#ifndef __WINDOW_GTK_H
#define __WINDOW_GTK_H

#include <gtk/gtk.h>
#include "streamer/stream_playback.h"
#include "gui/display_window.h"
#include "gui/control_window.h"


void activate(GtkApplication *app,
                     gpointer user_data);


int main(int argc, char **argv);


/**
 * @brief Callbacks
 * 
 */

void delete_event_cb (GtkWidget *widget, GdkEvent *event, options *option);

#endif