#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "json_parseo.h"

/* Copia el valor de texto de un item JSON (sin comillas). Si es null/ausente
 * devuelve cadena vacia. Siempre retorna memoria liberable con free(). */
static char *dup_texto(const cJSON *item) {
    const char *s = cJSON_GetStringValue(item);   /* NULL si no es string */
    return strdup(s ? s : "");
}

int parsear_datos(char *string, struct pelicula *salida, int cantidad){

    cJSON *json = cJSON_Parse(string);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) printf("Error: %s\n", error_ptr);
        return 1;
    }

    cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    if (!cJSON_IsArray(results) || cJSON_GetArraySize(results) == 0) {
        printf("No hay resultado\n");
        cJSON_Delete(json);
        return 1;
    }

    cJSON *dato = NULL;
    int i = 0;

    cJSON_ArrayForEach(dato, results){
        if (i == cantidad) break;

        (salida+i)->titulo      = dup_texto(cJSON_GetObjectItemCaseSensitive(dato, "title"));
        (salida+i)->descripcion = dup_texto(cJSON_GetObjectItemCaseSensitive(dato, "overview"));
        (salida+i)->poster_path = dup_texto(cJSON_GetObjectItemCaseSensitive(dato, "poster_path"));

        /* vote_average es numero: lo formateamos a texto. */
        cJSON *vote = cJSON_GetObjectItemCaseSensitive(dato, "vote_average");
        char buf[16];
        snprintf(buf, sizeof(buf), "%.1f", cJSON_IsNumber(vote) ? vote->valuedouble : 0.0);
        (salida+i)->calificacion = strdup(buf);

        i++;
    }

    cJSON_Delete(json);
    return 0;
}

void free_memory(struct pelicula *salida, int cantidad){
    for (int i = 0; i < cantidad; i++) {
        free((salida+i)->titulo);
        free((salida+i)->descripcion);
        free((salida+i)->calificacion);
        free((salida+i)->poster_path);
    }
}
