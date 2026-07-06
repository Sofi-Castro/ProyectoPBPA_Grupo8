#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "api.h"

// Acumula los datos que libcurl va recibiendo
static size_t callback_escritura(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    RespuestaHTTP *resp  = (RespuestaHTTP *)userdata;
    size_t         bytes = size * nmemb;

    if (resp->longitud + bytes >= API_BUFFER_MAX - 1) {
        fprintf(stderr, "[api] buffer lleno, respuesta truncada\n");
        bytes = API_BUFFER_MAX - 1 - resp->longitud;
    }

    memcpy(resp->datos + resp->longitud, ptr, bytes);
    resp->longitud += bytes;
    resp->datos[resp->longitud] = '\0';

    return bytes;
}

int api_buscar_peliculas(const FiltrosBusqueda *filtros, RespuestaHTTP *respuesta)
{
    // Leer API key del entorno
    const char *api_key = getenv("TMDB_API_KEY");
    if (!api_key || api_key[0] == '\0') {
        fprintf(stderr, "[api] error: TMDB_API_KEY no definida\n");
        return -1;
    }

    // Construir URL
    char url[1024];
    snprintf(url, sizeof(url),
             "https://api.themoviedb.org/3/discover/movie"
             "?api_key=%s"
             "&language=es-MX"
             "&sort_by=popularity.desc"
             "&with_genres=%d"
             "&primary_release_date.gte=%d-01-01"
             "&primary_release_date.lte=%d-12-31"
             "&watch_region=MX"
             "&with_watch_providers=%d"
             "&page=1",
             api_key,
             filtros->genero_id,
             filtros->anio_desde,
             filtros->anio_hasta,
             filtros->plataforma_id);

    printf("[api] URL: %s\n\n", url);

    // Inicializar libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "[api] error: no se pudo inicializar libcurl\n");
        curl_global_cleanup();
        return -1;
    }

    // Configurar peticion
    memset(respuesta, 0, sizeof(RespuestaHTTP));
    curl_easy_setopt(curl, CURLOPT_URL,            url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  callback_escritura);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,      respuesta);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,        10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Ejecutar peticion
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "[api] error de red: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return -1;
    }

    // Verificar codigo HTTP
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code != 200) {
        fprintf(stderr, "[api] error HTTP %ld\n", http_code);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return -1;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;
}

// Descarga el poster entregado por la API (poster_path de TMDB) a un archivo local.
// Escribe primero a un temporal .part y solo lo deja como definitivo si todo salio bien.
int api_descargar_poster(const char *poster_path, const char *ruta_destino)
{
    if (!poster_path || poster_path[0] == '\0' || !ruta_destino) {
        fprintf(stderr, "[api] poster_path o ruta_destino invalidos\n");
        return -1;
    }

    // TMDB entrega poster_path como "/abc.jpg"; toleramos con o sin '/' inicial.
    const char *sep = (poster_path[0] == '/') ? "" : "/";
    char url[512];
    snprintf(url, sizeof(url), "https://image.tmdb.org/t/p/w500%s%s", sep, poster_path);

    // Descargamos a un temporal para no dejar una imagen a medias.
    char tmp_path[600];
    snprintf(tmp_path, sizeof(tmp_path), "%s.part", ruta_destino);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "[api] error: no se pudo inicializar libcurl\n");
        curl_global_cleanup();
        return -1;
    }

    FILE *fp = fopen(tmp_path, "wb");
    if (!fp) {
        fprintf(stderr, "[api] error: no se pudo crear %s\n", tmp_path);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL,            url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  NULL);   // fwrite por defecto -> FILE
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,      fp);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,        20L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR,    1L);     // HTTP >= 400 -> error

    CURLcode res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    fclose(fp);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (res != CURLE_OK) {
        fprintf(stderr, "[api] error al descargar poster: %s [HTTP %ld]\n",
                curl_easy_strerror(res), http_code);
        remove(tmp_path);
        return -1;
    }

    if (rename(tmp_path, ruta_destino) != 0) {
        fprintf(stderr, "[api] error: no se pudo renombrar %s -> %s\n", tmp_path, ruta_destino);
        remove(tmp_path);
        return -1;
    }

    return 0;
}