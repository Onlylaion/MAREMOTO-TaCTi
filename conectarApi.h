#ifndef CONECTARAPI_H_INCLUDED
#define CONECTARAPI_H_INCLUDED
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

typedef struct {
    char nombre[50];
    unsigned puntaje;
    char fyh[50];
} tJugadorAPI;

typedef struct {
    char *info;
    size_t tamInfo;
} tRespuesta;

#endif // CONECTARAPI_H_INCLUDED
