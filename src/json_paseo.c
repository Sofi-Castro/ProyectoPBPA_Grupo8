#include <stdio.h>
#include <cjson/cJSON.h>


// creo que hay que incluir esto al archivo .h
struct pelicula {
    char *titulo;
    char *descripcion;
    char *calificacion;
    char *poster_path;
};

int parsear_datos(char *string, struct pelicula *salida){

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

    cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    
    if(cJSON_GetArraySize(results) == 0) {
        printf("No hay resultado");
        return 1;
    }


}
