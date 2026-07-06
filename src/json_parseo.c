#include <stdio.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>
#include "json_parseo.h"

int parsear_datos(char *string, struct pelicula *salida, int cantidad)
{
    /* Inicializar */
    for (int k = 0; k < cantidad; k++) {
        
        (salida + k)->titulo       = NULL;
        (salida + k)->descripcion  = NULL;
        (salida + k)->calificacion = NULL;
        (salida + k)->poster_path  = NULL;
    }

    cJSON *json = cJSON_Parse(string);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
            printf("Error JSON: %s\n", error_ptr);
        return 1;
        }
    }

    cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    if (!cJSON_IsArray(results)) {
        printf("No hay resultados\n");
        cJSON_Delete(json);
        return 1;
    }

    cJSON *dato = NULL;
    int i = 0;

    cJSON_ArrayForEach(dato, results)
    {
        if (i >= cantidad) break;

        /* title */
        cJSON *t = cJSON_GetObjectItemCaseSensitive(dato, "title");
        (salida + i)->titulo = (t && t->valuestring) ? strdup(t->valuestring) : NULL;

        /* overview */
        cJSON *o = cJSON_GetObjectItemCaseSensitive(dato, "overview");
        (salida + i)->descripcion = (o && o->valuestring) ? strdup(o->valuestring) : NULL;

        /* poster */
        cJSON *p = cJSON_GetObjectItemCaseSensitive(dato, "poster_path");
        (salida + i)->poster_path = (p && p->valuestring) ? strdup(p->valuestring) : NULL;

        /* vote_average */
        cJSON *vote = cJSON_GetObjectItemCaseSensitive(dato, "vote_average");

        double val = 0.0;
        if (cJSON_IsNumber(vote)) {
            val = vote->valuedouble;
        }

        char buf[16];
        snprintf(buf, sizeof(buf), "%.1f", val);
        (salida + i)->calificacion = strdup(buf);

        i++;
    }

    cJSON_Delete(json);
    return 0;
}


// libera la memoria
void free_memory(struct pelicula *salida, int cantidad){

    for (int i = 0; i < cantidad; i++) {
        free(salida[i].titulo);
        free(salida[i].descripcion);
        free(salida[i].calificacion);
        free(salida[i].poster_path);
    }

    free(salida);

}