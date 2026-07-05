#include <gtk/gtk.h>
#include <api.h>
#ifndef OPTIONS_H
#define OPTIONS_H

void option_genre(GtkButton *button, gpointer data, FiltrosBusqueda *filtros);

void option_year(GtkButton *button, gpointer data, FiltrosBusqueda *filtros);

void option_platform(GtkButton *button, gpointer data, FiltrosBusqueda *filtros);

#endif