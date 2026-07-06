#include <gtk/gtk.h>
#include "interfaz.h"
#include "api.h"
#include "json_parseo.h"

void activate (GtkApplication *app, gpointer user_data){
    GtkWidget *grid1, *grid2, *grid3;
    GtkWidget *titulo, *genero, *años, *plataforma;
    GtkWidget *boton, *boton_mostrar;
    GtkWidget *radio11, *radio21, *radio31, *radio41, *radio51, *radio61;
    GtkWidget *radio12, *radio22, *radio32, *radio42, *radio52, *radio62;
    GtkWidget *radio13, *radio23, *radio33, *radio43, *radio53, *radio63;

    /*Nombrar como entrada el struct tipo punteros que recibe activate*/
    punteros *entrada = (punteros *)user_data;
    
    /*Configuración principal de la interfaz*/
    entrada->ventana = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (entrada->ventana), "Recomendador de películas");
    gtk_window_set_default_size (GTK_WINDOW (entrada->ventana), 200, 200);
 
    /*Configuración de la caja donde van los elementos*/
    entrada->caja = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    /*Mensajes*/
    titulo = gtk_label_new("¿Qué tipo de película quiere ver? Selccione una opción de cada una de las tres categorías:");
    genero = gtk_label_new("Seleccione un género: ");
    gtk_label_set_xalign(GTK_LABEL(genero), 0.0);
    años = gtk_label_new("Seleccione el intervalo de años: ");
    gtk_label_set_xalign(GTK_LABEL(años), 0.0);
    plataforma = gtk_label_new("Seleccione una plataforma: ");
    gtk_label_set_xalign(GTK_LABEL(plataforma), 0.0);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);

    /*Botón para seleccionar los campos*/
    boton = gtk_button_new_with_label("Seleccionar");

    /*Botón para mostrar los resultados*/
    boton_mostrar = gtk_button_new_with_label("Mostrar resultados");

    /*Botones para elegir género*/
    radio11 = gtk_radio_button_new_with_label(NULL, "Acción");
    radio21 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Romance");
    radio31 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Comedia");
    radio41 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Thriller");
    radio51 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Terror");
    radio61 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Drama");
    GtkWidget *radios1[6] = {radio11, radio21, radio31, radio41, radio51, radio61};
    for (int i=0; i < 6; i++){
        entrada->radio1[i] = radios1[i];
    }
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio11), TRUE);

    grid1 = gtk_grid_new ();
    gtk_grid_set_row_spacing(GTK_GRID(grid1), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid1), 10);
    gtk_grid_attach(GTK_GRID(grid1), radio11, 0,0,2,2);
    gtk_grid_attach(GTK_GRID(grid1), radio21, 0,3,2,2);
    gtk_grid_attach(GTK_GRID(grid1), radio31, 3,0,2,2);
    gtk_grid_attach(GTK_GRID(grid1), radio41, 3,3,2,2);
    gtk_grid_attach(GTK_GRID(grid1), radio51, 6,0,2,2);
    gtk_grid_attach(GTK_GRID(grid1), radio61, 6,3,2,2);

    /*Botones para elegir años*/
    radio12 = gtk_radio_button_new_with_label(NULL, "1920-1939");
    radio22 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "1940-1959");
    radio32 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "1960-1979");
    radio42 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "1980-1999");
    radio52 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "2000-2019");
    radio62 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "2020-2026");
    GtkWidget *radios2[6] = {radio12, radio22, radio32, radio42, radio52, radio62};
    for (int i=0; i < 6; i++){
        entrada->radio2[i] = radios2[i];
    }
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio12), TRUE);

    grid2 = gtk_grid_new ();
    gtk_grid_set_row_spacing(GTK_GRID(grid2), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid2), 10);
    gtk_grid_attach(GTK_GRID(grid2), radio12, 0,0,2,2);
    gtk_grid_attach(GTK_GRID(grid2), radio22, 0,3,2,2);
    gtk_grid_attach(GTK_GRID(grid2), radio32, 3,0,2,2);
    gtk_grid_attach(GTK_GRID(grid2), radio42, 3,3,2,2);
    gtk_grid_attach(GTK_GRID(grid2), radio52, 6,0,2,2);
    gtk_grid_attach(GTK_GRID(grid2), radio62, 6,3,2,2);

    /*Botones para elegir plataforma*/
    radio13 = gtk_radio_button_new_with_label(NULL, "Netflix");
    radio23 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Max");
    radio33 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Disney+");
    radio43 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Youtube");
    radio53 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Prime Video");
    radio63 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Apple TV");
    GtkWidget *radios3[6] = {radio13, radio23, radio33, radio43, radio53, radio63};
    for (int i=0; i < 6; i++){
        entrada->radio3[i] = radios3[i];;
    }
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio13), TRUE);

    grid3 = gtk_grid_new ();
    gtk_grid_set_row_spacing(GTK_GRID(grid3), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid3), 10);
    gtk_grid_attach(GTK_GRID(grid3), radio13, 0,0,2,2);
    gtk_grid_attach(GTK_GRID(grid3), radio23, 0,3,2,2);
    gtk_grid_attach(GTK_GRID(grid3), radio33, 3,0,2,2);
    gtk_grid_attach(GTK_GRID(grid3), radio43, 3,3,2,2);
    gtk_grid_attach(GTK_GRID(grid3), radio53, 6,0,2,2);
    gtk_grid_attach(GTK_GRID(grid3), radio63, 6,3,2,2);

    /*Acomodar la box con cada widget*/
    gtk_box_pack_start(GTK_BOX(entrada->caja), titulo, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), genero, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), grid1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), años, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), grid2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), plataforma, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), grid3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), boton, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(entrada->caja), boton_mostrar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(scroll), entrada->caja);
    gtk_container_add(GTK_CONTAINER(entrada->ventana), scroll);

    /*Funcionalidad del boton con los radio buttons*/
    g_signal_connect(boton, "clicked", G_CALLBACK(option_genre), entrada);
    g_signal_connect(boton, "clicked", G_CALLBACK(option_year), entrada);
    g_signal_connect(boton, "clicked", G_CALLBACK(option_platform), entrada);
    g_signal_connect(boton_mostrar, "clicked", G_CALLBACK(interfaz_resultado), entrada);

    gtk_widget_show_all(entrada->ventana);
}

int main(int argc, char **argv){

    GtkApplication *app;
    int status;

    int cantidad = 3; /*la cantidad de peliculas recomendadas*/

    FiltrosBusqueda *filtro = malloc(sizeof(FiltrosBusqueda));
    if (!filtro){
        fprintf(stderr, "fallo en la reserva de memoria\n");
        return 1;
    }

    filtro->genero_id = 0;
    filtro->anio_desde = 0;
    filtro->anio_hasta = 0;
    filtro->plataforma_id = 0;

    /*guardar espacio para las recomendaciones*/
    struct pelicula *recomendacion = calloc(cantidad, sizeof(struct pelicula)); /* calloc: zero-init para liberar sin peligro en la 1a busqueda */
    if (!recomendacion){
        fprintf(stderr, "fallo en la reserva de memoria\n");
        free(filtro);
        return 1;
    }

    punteros *entrada_programa = malloc(sizeof(punteros));
    if (!entrada_programa){
        fprintf(stderr, "fallo en la reserva de memoria\n");
        free(filtro);
        free(recomendacion);
        return 1;
    }

    entrada_programa->filtros = filtro;
    entrada_programa->peliculas = recomendacion;

    app = gtk_application_new ("com.proyecto", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), entrada_programa);
    status = g_application_run (G_APPLICATION (app), argc, argv);

    /*Liberar los espacios de memoria reservados*/
    free(filtro);
    free_memory(recomendacion, cantidad);
    free(entrada_programa);

    g_object_unref (app);
    return status;
}
