#include <gtk/gtk.h>
#include "api.h"
#include "json_parseo.h"
#ifndef INTERFAZ_H
#define INTERFAZ_H

typedef struct {
    GtkWidget *radio[6];
    FiltrosBusqueda *filtros;
} Opcionradio;

typedef struct {
    FiltrosBusqueda *filtros;
    pelicula *peliculas;
    Opcionradio *radio1;
    Opcionradio *radio2;
    Opcionradio *radio3;
} punteros;

void option_genre(GtkButton *button, gpointer data);

void option_year(GtkButton *button, gpointer data);

void option_platform(GtkButton *button, gpointer data);

#endif