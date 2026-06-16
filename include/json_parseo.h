#ifndef JSON_PARSEO_H
#define JSON_PARSEO_H

struct pelicula {
    char *titulo;
    char *descripcion;
    char *calificacion;
    char *poster_path;
};

int parsear_datos(char *string, struct pelicula *salida);

#endif