#include "auxiliary.h"

const gchar* conductor_notebook_get_current_tab_label(GtkNotebook *tab) {
    return gtk_notebook_get_tab_label_text(tab, gtk_notebook_get_nth_page(tab, gtk_notebook_get_current_page(tab)));
}