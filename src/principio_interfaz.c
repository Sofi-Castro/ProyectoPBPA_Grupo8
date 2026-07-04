#include <gtk/gtk.h>

static void
activate (GtkApplication *app, gpointer user_data){
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *label;
    Gtk

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Recomendador de películas");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    label = gtk_label_new("¿Qué tipo de películas quieres ver? Elige una opción de las tres categorías");
    gtk_window_set_child(GTK_WINDOW(window), label);

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

    gtk_window_set_child (GTK_WINDOW (window), box);

    gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char **argv){

    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}