#ifndef API_H
#define API_H

#define API_BUFFER_MAX 65536
#define API_MAX_RESULTADOS 3

typedef struct {
    char   datos[API_BUFFER_MAX];
    size_t longitud;
} RespuestaHTTP;

typedef struct {
    int genero_id;
    int anio_desde;
    int anio_hasta;
    int plataforma_id;
} FiltrosBusqueda;

int api_buscar_peliculas(const FiltrosBusqueda *filtros, RespuestaHTTP *respuesta);

/* Descarga el poster de TMDB (poster_path) a ruta_destino. 0 = exito, !=0 = error. */
int api_descargar_poster(const char *poster_path, const char *ruta_destino);

#endif
