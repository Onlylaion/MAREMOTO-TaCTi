#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include "Juego.h"

void mostrarJugador(const void* a,const void* b);
int compararPuntajeTotal(const void* a, const void* b);
int compararPuntajeTotalIgual(const void* a, const void* b);
int cmpNombres(const void* a, const void* b);
void actualizarJugador(void *a, void *b);
void mostrarJugadorAPI(const void *a, const void *b);
int compararJugAPI(const void *a, const void *b);
int compararFechaHora(const char *fyh1, const char *fyh2);
int parsearJugadores(tRespuesta *res, tJugadorAPI *jugador);
void imprimirEncabezadoRanking();
void mostrarEnOrdenJugadores(tLista* jugadores,void (*accion)(const void*,const void*));
#endif // UTILIDADES_H_INCLUDED
