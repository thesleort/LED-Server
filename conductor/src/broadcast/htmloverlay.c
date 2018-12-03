#include "broadcast/htmloverlay.h"

#include <gst/gst.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

void add_html_overlay(GstElement *cairo_overlay) {

    CairoOverlayState *s = (CairoOverlayState *)malloc(sizeof(CairoOverlayState));
    WebKitWebView *webview;
    cairo_t *graphics_surface;

    s->height = 896;
    s->width = 512;
    // cairo_create(graphics_surface);
g_assert (cairo_overlay);
    s->webview = webkit_web_view_new();

    webkit_web_view_load_html(s->webview, ""
                                       "<html>"
                                       "  <head>"
                                       "    <style>"
                                       "      @keyframes slidein {"
                                       "        from { transform: scaleX(0); }"
                                       "        to   { transform: scaleX(1); }"
                                       "      }"
                                       "      body { background-color: rgba(0,0,0,0.3) }"
                                       "      h1 { background-color: rgba(0,0,0,0.3); animation: slidein 3s ease-in 1s infinite reverse both running; }"
                                       "    </style>"
                                       "  </head>"
                                       "  <body><h1 style='color:red'>Test</h1></body>"
                                       "</html>"
                                       "",
                              "/");

    // gtk_widget_draw(webview, s->surface);

	// s->webview = webview;

    printf("TEEEEEEST\n");
    // s->surface = graphics_surface;

    // cairo_overlay = gst_element_factory_make("cairooverlay", "graphics");
    // g_signal_connect(cairo_overlay, "caps-changed", G_CALLBACK(draw_overlay), s);
    g_signal_connect(cairo_overlay, "draw", G_CALLBACK(draw_overlay), s);

    printf("%p\n", cairo_overlay);
}

void draw_overlay(GstElement *overlay, cairo_t *cr, guint64 timestamp,
                  guint64 duration, CairoOverlayState *s) {
    //   cairo_set_source(cr, s->surface);

    // printf("--------------DRAW:   %p\n", cr);
    double scale;
    int width, height;

    // if (!s->valid)
    //     return;

    width = 200;
    height = 200;

    scale = 2 * (((timestamp / (int)1e7) % 70) + 30) / 100.0;
    cairo_translate(cr, width / 2, (height / 2) - 30);

    // /* FIXME: this assumes a pixel-aspect-ratio of 1/1 */
    cairo_scale(cr, scale, scale);

    // cairo_move_to(cr, 0, 0);
    // cairo_curve_to(cr, 0, -30, -50, -30, -50, 0);
    // cairo_curve_to(cr, -50, 30, 0, 35, 0, 60);
    // cairo_curve_to(cr, 0, 35, 50, 30, 50, 0);
    // cairo_curve_to(cr, 50, -30, 0, -30, 0, 0);
    // cairo_set_source_rgba(cr, 0.9, 0.0, 0.1, 0.7);
	// cairo_set_source(cr, s->surface);
	// cairo_set_source_surface(cr, )
	gtk_widget_draw(s->webview, cr);
    cairo_fill(cr);
}

void prepare_overlay(GstElement *overlay, GstCaps *caps, gpointer user_data) {
    CairoOverlayState *state = (CairoOverlayState *)user_data;

      state->valid = TRUE;
}