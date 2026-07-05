#include <gtk/gtk.h>
#include <options.h>

static void
activate (GtkApplication *app, gpointer user_data){
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *radio1, *radio2, *radio3;
    GtkWidget *button;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Recomendador de películas");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

    radio1 = gtk_radio_button_new_with_label(NULL, "Acción");
    radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio1), "Romance");
    radio3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio1), "Comedia");

    GtkWidget *radios[] = {radio1, radio2, radio3};

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio1), TRUE);

    button = gtk_button_new_with_label("Buscar");

    g_signal_connect(button, "clicked", G_CALLBACK(option_genre), radios);

    gtk_box_pack_start(GTK_BOX(box), radio1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), radio2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), radio3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 10);
    gtk_container_add (GTK_CONTAINER (window), box);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv){

    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}