#include <gtk/gtk.h>

typedef struct {
    int genero_id;
    int anio_desde;
    int anio_hasta;
    int plataforma_id;
    } FiltrosBusqueda;

void option_genre(GtkButton *button, gpointer data, FiltrosBusqueda *filtros);

void option_year(GtkButton *button, gpointer data, FiltrosBusqueda *filtros);

void option_platform(GtkButton *button, gpointer data, FiltrosBusqueda *filtros);