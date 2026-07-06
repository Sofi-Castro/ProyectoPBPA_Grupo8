#include <stdio.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>
#include "json_parseo.h"

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
        if (i >= cantidad) break;

        cJSON *title = cJSON_GetObjectItemCaseSensitive(dato, "title");
        cJSON *overview = cJSON_GetObjectItemCaseSensitive(dato, "overview");
        cJSON *vote = cJSON_GetObjectItemCaseSensitive(dato, "vote_average");
        cJSON *poster = cJSON_GetObjectItemCaseSensitive(dato, "poster_path");

        /* TITULO */
        if (title && cJSON_IsString(title) && title->valuestring) {
            salida[i].titulo = strdup(title->valuestring);
        } else {
            salida[i].titulo = strdup("");
        }

        /* DESCRIPCION */
        if (overview && cJSON_IsString(overview) && overview->valuestring) {
            salida[i].descripcion = strdup(overview->valuestring);
        } else {
            salida[i].descripcion = strdup("");
        }

        /* CALIFICACION (double → string) */
        char buffer[32];

        if (vote && cJSON_IsNumber(vote)) {
            snprintf(buffer, sizeof(buffer), "%.1f", vote->valuedouble);
        } else {
            snprintf(buffer, sizeof(buffer), "0.0");
        }

        salida[i].calificacion = strdup(buffer);

        /* POSTER */
        if (poster && cJSON_IsString(poster) && poster->valuestring) {
            salida[i].poster_path = strdup(poster->valuestring);
        } else {
            salida[i].poster_path = strdup("");
        }

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