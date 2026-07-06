#include <gtk/gtk.h>
#include "interfaz.h"
#include "api.h"
#include "json_parseo.h"

void option_genre(GtkButton *button, gpointer data){

    Opcionradio *radio1 = (Opcionradio *)data;

    /*Acción*/
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[0]))){
        radio1->filtros->genero_id = 28; 
    /*Romance*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[1]))){
        radio1->filtros->genero_id = 10746;
    /*Comedia*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[2]))){
        radio1->filtros->genero_id = 35;
    /*Thriller*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[3]))){
        radio1->filtros->genero_id = 53;
    /*Terror*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[4]))){
        radio1->filtros->genero_id = 27;
    /*Drama*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[5]))){
        radio1->filtros->genero_id = 18;
    }
}

void option_year(GtkButton *button, gpointer data){

    Opcionradio *radio1 = (Opcionradio *)data;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[0]))){
        radio1->filtros->anio_desde = 1920;
        radio1->filtros->anio_hasta = 1939;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[1]))){
        radio1->filtros->anio_desde = 1940;
        radio1->filtros->anio_hasta = 1959;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[2]))){
        radio1->filtros->anio_desde = 1960;
        radio1->filtros->anio_hasta = 1979;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[3]))){
        radio1->filtros->anio_desde = 1980;
        radio1->filtros->anio_hasta = 1999;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[4]))){
        radio1->filtros->anio_desde = 2000;
        radio1->filtros->anio_hasta = 2019;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[5]))){
        radio1->filtros->anio_desde = 2020;
        radio1->filtros->anio_hasta = 2026;
    }

}

void option_platform(GtkButton *button, gpointer data){

    Opcionradio *radio1 = (Opcionradio *)data;

    /*Netflix*/
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[0]))){
        radio1->filtros->plataforma_id = 8;
    /*Max*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[1]))){
        radio1->filtros->plataforma_id = 384;
    /*Disney+*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[2]))){
        radio1->filtros->plataforma_id = 337;
    /*Youtube*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[3]))){
        radio1->filtros->plataforma_id = 192;
    /*Prime Video*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[4]))){
        radio1->filtros->plataforma_id = 119;
    /*Apple TV*/
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[5]))){
        radio1->filtros->plataforma_id = 2;
    }

}

void interfaz_resultado(GtkButton *button, gpointer data){

    punteros *entrada = (punteros *)data;

    RespuestaHTTP respuesta;

    /*Después de elegir las opciones en la interfaz, hay que hacer la petición a la API y parsear la respuesta*/
    api_buscar_peliculas(entrada->filtros, &respuesta);
    parsear_datos(&respuesta, entrada->peliculas);

    /*Crear cuadriculas para cada película*/
    GtkWidget *grid4 = gtk_grid_new();
    GtkWidget *grid5 = gtk_grid_new();
    GtkWidget *grid6 = gtk_grid_new();
    
    /*Crear punteros para imagenes de las tres peliculas*/
    GtkWidget *imagen1, *imagen2, *imagen3;

    /*Crear las etiquetas a los títulos*/
    GtkWidget *titulo1, *descripcion1, *calificacion1;
    GtkWidget *titulo2, *descripcion2, *calificacion2;
    GtkWidget *titulo3, *descripcion3, *calificacion3;

    /*Descargar las imágenes*/
    int valor1 = api_descargar_poster(entrada->peliculas[0].poster_path, "imagenes/imagen1.jpg");
    if (valor1 != 0){
        fprintf(stderr, "No se pudo descargar la imagen.");
    }
    int valor2 = api_descargar_poster(entrada->peliculas[1].poster_path, "imagenes/imagen2.jpg");
    if (valor2 != 0){
        fprintf(stderr, "No se pudo descargar la imagen.");
    }
    int valor3 = api_descargar_poster(entrada->peliculas[2].poster_path, "imagenes/imagen3.jpg");
    if (valor3 != 0){
        fprintf(stderr, "No se pudo descargar la imagen.");
    }

    /*Etiquetas con los titulos, descripciones y calificaciones*/
    titulo1 = gtk_label_new(entrada->peliculas[0].titulo);
    gtk_label_set_xalign(GTK_LABEL(titulo1), 0.5);
    descripcion1 = gtk_label_new(entrada->peliculas[0].descripcion);
    gtk_label_set_line_wrap(GTK_LABEL(descripcion1), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(descripcion1), 50);
    calificacion1 = gtk_label_new(entrada->peliculas[0].calificacion);
    imagen1 = gtk_image_new_from_file("imagenes/imagen1.jpg");

    titulo2 = gtk_label_new(entrada->peliculas[1].titulo);
    gtk_label_set_xalign(GTK_LABEL(titulo2), 0.5);
    descripcion2 = gtk_label_new(entrada->peliculas[1].descripcion);
    gtk_label_set_line_wrap(GTK_LABEL(descripcion2), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(descripcion2), 50);
    calificacion2 = gtk_label_new(entrada->peliculas[1].calificacion);
    imagen2 = gtk_image_new_from_file("imagenes/imagen2.jpg");

    titulo3 = gtk_label_new(entrada->peliculas[2].titulo);
    gtk_label_set_xalign(GTK_LABEL(titulo3), 0.5);
    descripcion3 = gtk_label_new(entrada->peliculas[2].descripcion);
    gtk_label_set_line_wrap(GTK_LABEL(descripcion3), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(descripcion3), 50);
    calificacion3 = gtk_label_new(entrada->peliculas[2].calificacion);
    imagen3 = gtk_image_new_from_file("imagenes/imagen3.jpg");

    /*Cuadrícula para la primera película*/
    gtk_grid_set_row_spacing(GTK_GRID(grid4), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid4), 10);
    gtk_grid_attach(GTK_GRID(grid4), titulo1, 0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid4), imagen1, 0,1,1,3);
    gtk_grid_attach(GTK_GRID(grid4), calificacion1, 1,1,1,1);
    gtk_grid_attach(GTK_GRID(grid4), descripcion1, 1,2,1,2);

    /*Cuadrícula para la segunda película*/
    gtk_grid_set_row_spacing(GTK_GRID(grid5), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid5), 10);
    gtk_grid_attach(GTK_GRID(grid5), titulo2, 0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid5), imagen2, 0,1,1,3);
    gtk_grid_attach(GTK_GRID(grid5), calificacion2, 1,1,1,1);
    gtk_grid_attach(GTK_GRID(grid5), descripcion2, 1,2,1,2);
    

    /*Cuadrícula para la segunda película*/
    gtk_grid_set_row_spacing(GTK_GRID(grid6), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid6), 10);
    gtk_grid_attach(GTK_GRID(grid6), titulo3, 0,0,2,1);
    gtk_grid_attach(GTK_GRID(grid6), imagen3, 0,1,1,3);
    gtk_grid_attach(GTK_GRID(grid6), calificacion3, 1,1,1,1);
    gtk_grid_attach(GTK_GRID(grid6), descripcion3, 1,2,1,2);
    

    gtk_box_pack_start(GTK_BOX(entrada->caja), grid4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), grid5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), grid6, FALSE, FALSE, 0);

    gtk_widget_show_all(entrada->ventana);
}
