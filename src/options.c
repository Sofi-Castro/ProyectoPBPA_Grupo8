#include <gtk/gtk.h>
#include "options.h"

void option_genre(GtkButton *button, gpointer data, FiltrosBusqueda *filtros){

    GtkWidget **radio = (GtkWidget **)data;

    /*Acción*/
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[0]))){
        filtros->genero_id = 28;
    /*Romance*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[1]))){
        filtros->genero_id = 10746;
    /*Comedia*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[2]))){
        filtros->genero_id = 35;
    /*Thriller*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[3]))){
        filtros->genero_id = 53;
    /*Terror*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[4]))){
        filtros->genero_id = 27;
    /*Drama*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[5]))){
        filtros->genero_id = 18;
    }

}

void option_year(GtkButton *button, gpointer data, FiltrosBusqueda *filtros){

    GtkWidget **radio = (GtkWidget **)data;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[0]))){
        filtros->anio_desde = 1920;
        filtros->anio_hasta = 1939;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[1]))){
        filtros->anio_desde = 1940;
        filtros->anio_hasta = 1959;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[2]))){
        filtros->anio_desde = 1960;
        filtros->anio_hasta = 1979;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[3]))){
        filtros->anio_desde = 1980;
        filtros->anio_hasta = 1999;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[4]))){
        filtros->anio_desde = 2000;
        filtros->anio_hasta = 2019;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[5]))){
        filtros->anio_desde = 2020;
        filtros->anio_hasta = 2026;
    }

}

void option_platform(GtkButton *button, gpointer data, FiltrosBusqueda *filtros){

    GtkWidget **radio = (GtkWidget **)data;

    /*Netflix*/
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[0]))){
        filtros->plataforma_id = 8;
    /*Max*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[1]))){
        filtros->plataforma_id = 384;
    /*Disney+*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[2]))){
        filtros->plataforma_id = 337;
    /*Youtube*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[3]))){
        filtros->plataforma_id = 192;
    /*Prime Video*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[4]))){
        filtros->plataforma_id = 119;
    /*Apple TV*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[5]))){
        filtros->plataforma_id = 2;
    }

}




