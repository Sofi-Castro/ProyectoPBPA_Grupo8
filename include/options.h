#include <gtk/gtk.h>
#include <api.h>
#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
    GtkWidget *radios[6];
    FiltrosBusqueda *filtros;
} Opcionradio;

void option_genre(GtkButton *button, gpointer data);

void option_year(GtkButton *button, gpointer data);

void option_platform(GtkButton *button, gpointer data);

#endif