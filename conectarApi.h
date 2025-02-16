#ifndef CONECTARAPI_H_INCLUDED
#define CONECTARAPI_H_INCLUDED
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include "TDALista.h"
#include "Juego.h"


typedef struct {
    char nombre[50];
    int puntaje;
    char fyh[50];
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


size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
CURLcode peticionGET(tRespuesta *respuesta, char *path);
CURLcode peticionPOST(tRespuesta *respuesta,tLista* listaJugadores,char* pathUrl, char* jsonData);
int parsearJugadores(tRespuesta *res, tJugadorAPI *jugador);

int compararJugAPI(const void *a, const void *b);
void actualizarJugador(void *a, void *b);
void mostrarJugadorAPI(const void *a, const void *b);

#endif // CONECTARAPI_H_INCLUDED
