#include "conectarApi.h"


void prepararDatoJSON(tLista* listaJugadores, tConfiguracion* configuracion, char* jsonData,unsigned tamJSON)
{
    char cadena[TAM_CADENA];
    int pos = 0;

    // Iniciar el JSON
    pos += snprintf(jsonData + pos, tamJSON, "{ \"CodigoGrupo\": \"%s\", \"Jugadores\": [", configuracion->codIdenGrupo);

    // Recorrer la lista de jugadores y agregarlos al JSON cadena
    while(*listaJugadores)
    {
        snprintf(cadena, sizeof(cadena), "{\"nombre\": \"%s\", \"puntos\": %d}",
                 ((tJugador*)(*listaJugadores)->info)->nombre,
                 ((tJugador*)(*listaJugadores)->info)->puntaje);

        // Agregar coma entre elementos, excepto
        listaJugadores=&(*listaJugadores)->sig;
        pos += snprintf(jsonData + pos, tamJSON - pos, "%s%s", cadena, (*listaJugadores) ? ", " : "" );
    }
    // Cerrar el JSON
    snprintf(jsonData + pos, tamJSON - pos, "]}");
}

// Funci�n que maneja la respuesta de la solicitud HTTP
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

CURLcode peticionGET(tRespuesta *respuesta,const char *path){
    CURLcode res;
    CURL* curl;
    // Inicializar el manejo de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    // Establecer la URL de la solicitud GET
    curl_easy_setopt(curl, CURLOPT_URL, path);

    // Establecer la funci�n de retorno de llamada para manejar la respuesta
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, respuesta);

    // Realizar la solicitud HTTP GET
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return res;
}

CURLcode peticionPOST(tRespuesta *respuesta,const char* pathUrl,const char* jsonData){
    CURLcode res;
    CURL* curl;
    struct curl_slist *headers = NULL;

    // Inicializar el manejo de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    // Agregar encabezados para indicar que se env�a JSON
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Configurar la URL
    curl_easy_setopt(curl, CURLOPT_URL, pathUrl);

    // Indicar que es una solicitud POST
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // Enviar los datos JSON
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData);

    // Configurar los encabezados
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Establecer la funci�n de retorno de llamada para manejar la respuesta
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, respuesta);


    // Realizar la solicitud HTTP GET
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return res;
}





