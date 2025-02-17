#ifndef INFORME_H_INCLUDED
#define INFORME_H_INCLUDED

#include "TDALista.h"
#include <stdio.h>

int generarInformeDeGrupo(tLista* listaJugadores, tLista* partidasJugadas,int cantidadPartidas,int (*cmp)(const void*, const void*));
void registrarEnInformeMayoresPuntajes(FILE* arch,tLista* listaJugadores,int (*cmp)(const void*, const void*));
int registrarEnInformeJugadorPartidasPuntaje(FILE* arch,tLista* partidasJugadas,int numeroDePartida);
void registrarEnInformePuntosTotalesXJugador(FILE* arch,int PuntosTotales);



#endif // INFORME_H_INCLUDED
