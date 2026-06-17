#include <stdio.h>
#include <cjson/cJSON.h>
#include <stdlib.h>


struct pelicula {
    char *titulo;
    char *descripcion;
    char *calificacion;
    char *poster_path;
};

int parsear_datos(char *string, struct pelicula *salida, int cantidad){


    // parsea los datos

    cJSON *json = cJSON_Parse(string);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return 1;
    }

    // acceder a los datos

    cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    
    if(cJSON_GetArraySize(results) == 0) {
        printf("No hay resultado");
        return 1;
    }

    cJSON *dato = NULL;

    int i = 0;

    // recorre cada pelicula guerda datos en salida
    
    cJSON_ArrayForEach(dato, results){
        if (i == cantidad) break;

        (salida+i)->titulo = cJSON_Print( cJSON_GetObjectItemCaseSensitive(dato, "title") );
        (salida+i)->descripcion = cJSON_Print( cJSON_GetObjectItemCaseSensitive(dato, "overview") );
        (salida+i)->calificacion = cJSON_Print( cJSON_GetObjectItemCaseSensitive(dato, "vote_average") );
        (salida+i)->poster_path = cJSON_Print( cJSON_GetObjectItemCaseSensitive(dato, "poster_path") );

        i++;
    }



    // limpiar

    cJSON_Delete(json);
    return 0;
}


// libera la memoria
void free_memory(struct pelicula *salida, int cantidad){
        for (int i = 0; i < cantidad; i++) {
        free((salida+i)->titulo);
        free((salida+i)->descripcion);
        free((salida+i)->calificacion);
        free((salida+i)->poster_path);
    }
}
