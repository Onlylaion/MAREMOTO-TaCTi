#include "conectarApi.h"

// Función que maneja la respuesta de la solicitud HTTP
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    tRespuesta *res = (tRespuesta*) userp;
    char *info = malloc(realsize + 1);

    if(!info){
        printf("No hay memoria suficiente");
        return 0;
    }

    memcpy(info, (char *)contents, (int)realsize);
    *(info + realsize) = '\0';
    res->info = info;
    res->tamInfo = realsize;
    return realsize;
}

CURLcode peticionGET(CURL *curl, tRespuesta *respuesta){
    CURLcode res;
    // Inicializar el manejo de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    // Establecer la URL de la solicitud GET
    curl_easy_setopt(curl, CURLOPT_URL, "https://algoritmos-api.azurewebsites.net/api/TaCTi/MARFIL");

    // Establecer la función de retorno de llamada para manejar la respuesta
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, respuesta);

    // Realizar la solicitud HTTP GET
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return res;
}

CURLcode peticionPOST(CURL *curl, tRespuesta *respuesta){
    CURLcode res;
    struct curl_slist *headers = NULL;

    const char *json_data = "{"
            "\"CodigoGrupo\": \"MARFIL\","
            "\"Jugadores\": [{"
                "\"nombre\": \"ejemplo5\","
                "\"puntos\": 30"
            "}]"
        "}";


    // Inicializar el manejo de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    // Agregar encabezados para indicar que se envía JSON
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Configurar la URL
    curl_easy_setopt(curl, CURLOPT_URL, "https://algoritmos-api.azurewebsites.net/api/TaCTi");

    // Indicar que es una solicitud POST
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // Enviar los datos JSON
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

    // Configurar los encabezados
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Establecer la función de retorno de llamada para manejar la respuesta
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, respuesta);


    // Realizar la solicitud HTTP GET
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return res;
}

int parsearJugadores(tRespuesta *res, tJugadorAPI *jugador){
    char *p = strrchr(res->info, '}');

    if(!p){
        return 0;
    }

    p--;
    *p = '\0';

    p = strrchr(res->info, ',');
    p = strchr(p, ':');
    strcpy(jugador->fyh, p + 2);
    p = strrchr(res->info, ',');

    *p = '\0';
    p = strrchr(res->info, ',');
    p = strchr(p, ':');
    sscanf(p + 1, "%u", &jugador->puntaje);
    p = strrchr(res->info, ',');

    p--;
    *p = '\0';
    p = strrchr(res->info, '{');
    p = strchr(p, ':');
    strcpy(jugador->nombre, p + 2);
    p = strrchr(res->info, '{');

    *p = '\0';
    return 1;
}
