#ifndef __HTMLOVERLAY_H
#define __HTMLOVERLAY_H

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <webkit2/webkit2.h>


typedef struct {
  gboolean valid;
  int width;
  int height;
  cairo_t *surface;
  GtkWidget *webview;
} CairoOverlayState;

void add_html_overlay(GstElement *cairo_overlay);

void draw_overlay(GstElement * overlay, cairo_t * cr, guint64 timestamp, 
  guint64 duration, CairoOverlayState *s);

  void prepare_overlay(GstElement *overlay, GstCaps *caps, gpointer user_data);

#endif