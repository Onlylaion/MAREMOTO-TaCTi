#include "conectarApi.h"


void prepararDatoJSON(tLista* listaJugadores, tConfiguracion* configuracion, char json_data[TAM_MAX_JSON])
{
    char cadena[TAM_CADENA];
    int pos = 0;

    // Iniciar el JSON
    pos += snprintf(json_data + pos, TAM_MAX_JSON, "{ \"CodigoGrupo\": \"%s\", \"Jugadores\": [", configuracion->codIdenGrupo);

    // Recorrer la lista de jugadores y agregarlos al JSON cadena
    while(*listaJugadores)
    {
        snprintf(cadena, sizeof(cadena), "{\"nombre\": \"%s\", \"puntos\": %d}",
                 ((tJugador*)(*listaJugadores)->info)->nombre,
                 ((tJugador*)(*listaJugadores)->info)->puntaje);

        // Agregar coma entre elementos, excepto
        listaJugadores=&(*listaJugadores)->sig;
        pos += snprintf(json_data + pos, TAM_MAX_JSON - pos, "%s%s", cadena, (*listaJugadores) ? ", " : "");
    }
    // Cerrar el JSON
    snprintf(json_data + pos, TAM_MAX_JSON - pos, "]}");
}
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

CURLcode peticionGET(CURL *curl, tRespuesta *respuesta, char *path){
    CURLcode res;
    // Inicializar el manejo de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    // Establecer la URL de la solicitud GET
    curl_easy_setopt(curl, CURLOPT_URL, path);

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

CURLcode peticionPOST(tRespuesta *respuesta,tLista* listaJugadores,char* pathUrl, char* json_data){
    CURLcode res;
    CURL* curl;
    struct curl_slist *headers = NULL;

    // Inicializar el manejo de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl)
        return CURLE_FAILED_INIT;

    // Agregar encabezados para indicar que se envía JSON
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Configurar la URL
    curl_easy_setopt(curl, CURLOPT_URL, pathUrl);

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

int compararJugAPI(const void *a, const void *b){
    tJugadorAPI *aa = (tJugadorAPI *) a;
    tJugadorAPI *bb = (tJugadorAPI *) b;
    tFechaHora fecha1, fecha2;


    int resultado = strcmp(aa->nombre, bb->nombre);
    if( resultado != 0){
        resultado = aa->puntaje - bb->puntaje;
        if ( resultado == 0){

            sscanf(aa->fyh, "%2d/%2d/%4d %2d:%2d:%2d",
                   &fecha1.dia,
                   &fecha1.mes,
                   &fecha1.anio,
                   &fecha1.hora,
                   &fecha1.minutos,
                   &fecha1.segundos);


            sscanf(bb->fyh, "%2d/%2d/%4d %2d:%2d:%2d",
                   &fecha1.dia,
                   &fecha1.mes,
                   &fecha1.anio,
                   &fecha1.hora,
                   &fecha1.minutos,
                   &fecha1.segundos);

            resultado = fecha1.anio - fecha2.anio;
            if(resultado == 0){
                resultado = fecha1.mes - fecha2.mes;
                if(resultado == 0){
                    resultado = fecha1.dia - fecha2.dia;
                    if(resultado == 0){
                        resultado = fecha1.hora - fecha2.hora;

                        if(resultado == 0){
                            resultado = fecha1.minutos - fecha2.minutos;

                            if(resultado == 0){
                                resultado = fecha1.segundos - fecha2.segundos;
                            } else {
                                return 1;
                            }
                        }
                    }
                }
            }

        }
    }

    return resultado;

}

void actualizarJugador(void *a, void *b){
    tJugadorAPI *aa = (tJugadorAPI *) a;
    tJugadorAPI *bb = (tJugadorAPI *) b;

    aa->puntaje += bb->puntaje;
    strcpy(aa->fyh, bb->fyh);
}

void mostrarJugadorAPI(const void *a, const void *b){
    tJugadorAPI *aa = (tJugadorAPI *) a;
    int posicion = *(int *) b;
    printf("%02d - Jugador: %s - Puntaje total: %02d - Ultima partida: %s \n", posicion, aa->nombre, aa->puntaje, aa->fyh);
}
