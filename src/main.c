#include <gtk/gtk.h>
#include <options.h>

static void
activate (GtkApplication *app, gpointer user_data){
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *radio11, *radio21, *radio31, *radio41, *radio51, *radio61;
    GtkWidget *radio12, *radio22, *radio32, *radio42, *radio52, *radio62;
    GtkWidget *radio13, *radio23, *radio33, *radio43, *radio53, *radio63;

    /*Configuración principal de la interfaz*/
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Recomendador de películas");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    /*Configuración de la cuadrícula donde van los botones*/
    grid = gtk_grid_new ();

    /*Botones para elegir género*/
    radio11 = gtk_radio_button_new_with_label(NULL, "Acción");
    radio21 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Romance");
    radio31 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Comedia");
    radio41 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Thriller");
    radio51 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Terror");
    radio61 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio11), "Drama");
    GtkWidget *radios1[] = {radio11, radio21, radio31, radio41, radio51, radio61};
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio11), TRUE);

    gtk_grid_attach(GTK_GRID(grid), radio11, 0,0,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio21, 2,0,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio31, 0,3,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio41, 2,3,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio51, 0,6,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio61, 2,6,2,2);

    /*Botones para elegir años*/
    radio12 = gtk_radio_button_new_with_label(NULL, "1920-1939");
    radio22 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "1940-1959");
    radio32 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "1960-1979");
    radio42 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "1980-1999");
    radio52 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "2000-2019");
    radio62 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio12), "2020-2026");
    GtkWidget *radios2[] = {radio12, radio22, radio32, radio42, radio52, radio62};
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio12), TRUE);

    gtk_grid_attach(GTK_GRID(grid), radio12, 5,0,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio22, 7,0,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio32, 5,3,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio42, 7,3,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio52, 5,6,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio62, 7,6,2,2);

    /*Botones para elegir plataforma*/
    radio13 = gtk_radio_button_new_with_label(NULL, "Netflix");
    radio23 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Max");
    radio33 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Disney+");
    radio43 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Youtube");
    radio53 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Prime Video");
    radio63 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio13), "Apple TV");
    GtkWidget *radios3[] = {radio13, radio23, radio33, radio43, radio53, radio63};
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio13), TRUE);

    gtk_grid_attach(GTK_GRID(grid), radio13, 10,0,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio23, 12,0,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio33, 10,3,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio43, 12,3,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio53, 10,6,2,2);
    gtk_grid_attach(GTK_GRID(grid), radio63, 12,6,2,2);

    /*definir lo que contiene los widgets como grid*/
    gtk_container_add (GTK_CONTAINER (window), grid);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv){

    GtkApplication *app;
    int status;

    app = gtk_application_new ("com.proyecto", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}