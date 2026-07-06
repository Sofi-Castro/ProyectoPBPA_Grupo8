#include <gtk/gtk.h>
#include "interfaz.h"
#include "api.h"
#include "json_parseo.h"

void option_genre(GtkButton *button, gpointer data){

    Opcionradio *radio1 = (Opcionradio *)data;

    int lista_id[6] = {28, 10764, 35, 53, 27, 18};

    for (int i = 0; i < 6; i++) {
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[i]))) {
            radio1->filtros->genero_id = lista_id[i];
            break;
        }
    }
}

void option_year(GtkButton *button, gpointer data){

    Opcionradio *radio1 = (Opcionradio *)data;

    int lista_desde[6] = {1920,1940,1960,1980,2000,2020};
    int lista_hasta[6] = {1939, 1959, 1979, 1999, 2019, 2026};

    for (int i = 0; i < 6; i++) {
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[i]))) {
            radio1->filtros->anio_desde = lista_desde[i];
            radio1->filtros->anio_hasta = lista_hasta[i];
            break;
        }
    }
}

void option_platform(GtkButton *button, gpointer data){

    Opcionradio *radio1 = (Opcionradio *)data;

    g_print("radio1 = %p\n", (void *)radio1);

    int lista_id[6] = {8, 384, 337, 192, 119, 2};

    for (int i = 0; i < 6; i++) {
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio1->radio[i]))) {
            radio1->filtros->plataforma_id = lista_id[i];
            break;
        }
    }

}

void interfaz_resultado(GtkButton *button, gpointer data){

    punteros *entrada = (punteros *)data;

    RespuestaHTTP respuesta;

    int cantidad = 3;

    int consulta = api_buscar_peliculas(entrada->filtros, &respuesta);

    if (consulta != 0){
        fprintf(stderr, "fallo en la peticion\n");
        return;    
    }
    
    parsear_datos(respuesta.datos, entrada->peliculas, cantidad);

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
    int valor2 = api_descargar_poster(entrada->peliculas[1].poster_path, "imagenes/imagen2.jpg");
    int valor3 = api_descargar_poster(entrada->peliculas[2].poster_path, "imagenes/imagen3.jpg");

    /*Etiquetas con los titulos, descripciones y calificaciones e imagen*/
    titulo1 = gtk_label_new(entrada->peliculas[0].titulo);
    gtk_label_set_xalign(GTK_LABEL(titulo1), 0.5);
    descripcion1 = gtk_label_new(entrada->peliculas[0].descripcion);
    gtk_label_set_line_wrap(GTK_LABEL(descripcion1), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(descripcion1), 50);
    calificacion1 = gtk_label_new(entrada->peliculas[0].calificacion);

    if (valor1 == 0) {
        imagen1 = gtk_image_new_from_file("imagenes/imagen1.jpg");
    } else {
        imagen1 = gtk_image_new_from_icon_name("image-missing", GTK_ICON_SIZE_DIALOG);
        fprintf(stderr, "No se pudo descargar la imagen.");
    }

    titulo2 = gtk_label_new(entrada->peliculas[1].titulo);
    gtk_label_set_xalign(GTK_LABEL(titulo2), 0.5);
    descripcion2 = gtk_label_new(entrada->peliculas[1].descripcion);
    gtk_label_set_line_wrap(GTK_LABEL(descripcion2), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(descripcion2), 50);
    calificacion2 = gtk_label_new(entrada->peliculas[1].calificacion);
    
    if (valor2 == 0) {
        imagen2 = gtk_image_new_from_file("imagenes/imagen2.jpg");
    } else {
        imagen2 = gtk_image_new_from_icon_name("image-missing", GTK_ICON_SIZE_DIALOG);
        fprintf(stderr, "No se pudo descargar la imagen.");
    }

    titulo3 = gtk_label_new(entrada->peliculas[2].titulo);
    gtk_label_set_xalign(GTK_LABEL(titulo3), 0.5);
    descripcion3 = gtk_label_new(entrada->peliculas[2].descripcion);
    gtk_label_set_line_wrap(GTK_LABEL(descripcion3), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(descripcion3), 50);
    calificacion3 = gtk_label_new(entrada->peliculas[2].calificacion);

    if (valor3 == 0) {
        imagen3 = gtk_image_new_from_file("imagenes/imagen3.jpg");
    } else {
        imagen3 = gtk_image_new_from_icon_name("image-missing", GTK_ICON_SIZE_DIALOG);
        fprintf(stderr, "No se pudo descargar la imagen.");
    }

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
