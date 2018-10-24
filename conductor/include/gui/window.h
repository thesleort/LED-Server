#ifndef __WINDOW_GTK_H
#define __WINDOW_GTK_H

#include <gtk/gtk.h>
#include "gui/stream_playback.h"


void activate(GtkApplication *app,
                     gpointer user_data);


main(int argc, char **argv);


/**
 * @brief Callbacks
 * 
 */

void delete_event_cb (GtkWidget *widget, GdkEvent *event, stream_data *data);

void switch_tab_cb(GtkNotebook *notebook, GtkWidget *page, guint page_num, stream_data *data);

#endif