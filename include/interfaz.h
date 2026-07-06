#include <gtk/gtk.h>
#include "api.h"
#include "json_parseo.h"
#ifndef INTERFAZ_H
#define INTERFAZ_H

typedef struct {
    FiltrosBusqueda *filtros;
    struct pelicula *peliculas;
    GtkWidget *radio1[6];
    GtkWidget *radio2[6];
    GtkWidget *radio3[6];
    GtkWidget *caja;
    GtkWidget *ventana;
} punteros;

void option_genre(GtkButton *button, gpointer data);

void option_year(GtkButton *button, gpointer data);

void option_platform(GtkButton *button, gpointer data);

void interfaz_resultado(GtkButton *button, gpointer data);

#endif