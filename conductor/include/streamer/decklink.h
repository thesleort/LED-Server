#ifndef __DECKLINK_H
#define __DECKLINK_H

#include <gst/gst.h>
#include <string.h>

typedef struct _streamData {
  gboolean is_live;
  GstElement *pipeline;
  GMainLoop *loop;
} streamData;

int decklink();

// static void dcb_message(GstBus *bus, GstMessage *msg, streamData *data);

#endif