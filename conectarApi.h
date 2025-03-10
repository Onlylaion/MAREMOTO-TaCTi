#ifndef CONECTARAPI_H_INCLUDED
#define CONECTARAPI_H_INCLUDED
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include "TDALista.h"
#include "Juego.h"
#define TAM_CAD 50

typedef struct {
    char nombre[TAM_CAD];
    int puntaje;
    char fyh[TAM_CAD];
} tJugadorAPI;

typedef struct {
    char *info;
    size_t tamInfo;
} tRespuesta;

typedef struct {
    int dia;
    int mes;
    int anio;
    int hora;
    int minutos;
    int segundos;
} tFechaHora;

void enviarDatosJSON(const void* elem1,const void* elem2);
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
CURLcode peticionGET(tRespuesta *respuesta,const char *path);
CURLcode peticionPOST(tRespuesta *respuesta,const char* pathUrl,const char* jsonData);





#endif // CONECTARAPI_H_INCLUDED
