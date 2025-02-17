#include "informe.h"
#include "Juego.h"
#include <string.h>

void registrarEnInformeMayoresPuntajes(FILE* arch,tLista* listaJugadores,int (*cmp)(const void*, const void*))
{
    //Realizamos la escritura de una archivo de txt
    tLista* aux = listaJugadores;
    fprintf(arch,"Puntaje/Puntajes mas altos:\n\n");
    while( *listaJugadores && cmp((*listaJugadores)->info,(*aux)->info))
    {
        fprintf(arch,"Jugador: %s ---> Puntos: %d\n",((tJugador*)(*listaJugadores)->info)->nombre,((tJugador*)(*listaJugadores)->info)->puntaje);
        listaJugadores=&(*listaJugadores)->sig;
    }
}

int registrarEnInformeJugadorPartidasPuntaje(FILE* arch,tLista* partidasJugadas,int numeroDePartida)
{
    unsigned j;
    //en caso de ser la primer partida, escribimos el nombre del jugador en un archivo
    tPartida* auxPartida = (tPartida*) (*partidasJugadas)->info;

    if(numeroDePartida==1)
        fprintf(arch,"Jugador: %s\n\n", auxPartida ->jugador);

    fprintf(arch,"Partida numero %d: \n\n",numeroDePartida);
    //mostramos el tablero al final del tablero
    for(j=0; j<TAM_TABLERO; j++)
        fprintf(arch,"\t%c | %c | %c\n",auxPartida ->tablero[j][0],auxPartida ->tablero[j][1],auxPartida ->tablero[j][2]);
    //guardamos los puntos obtenidos en la partida
    fprintf(arch,"\nPuntos Obtenidos: %d \n\n",auxPartida ->puntajeObtenido);
    //Fuerza la escritura en el archivo, asegurando que los datos no queden en el buffer
    fflush(arch);
    //Devolvemos los puntos obtenidos
    return auxPartida->puntajeObtenido;
}

void registrarEnInformePuntosTotalesXJugador(FILE* arch,int PuntosTotales)
{
    fprintf(arch,"TOTAL DE PUNTOS: %d \n----------------------------------\n\n", PuntosTotales);
    fflush(arch);
}

int generarInformeDeGrupo(tLista* listaJugadores, tLista* partidasJugadas,int cantidadPartidas,int (*cmp)(const void*, const void*))
{
    //cadena para almacenar el nombre del archivo del informe
    char nombreArch[TAM_CADENA_ARCH];
    FILE *arch;
    int i=1, totalPuntaje=0;
    time_t t = time(NULL);
    struct tm tiempoAct = *localtime(&t);

    //Personalizo el nombre del informe de juego de acuerdo a fecha y hora:

    snprintf(nombreArch, sizeof(nombreArch), "informe-juego_%d-%02d-%02d-%02d-%02d.txt",tiempoAct.tm_year + 1900, tiempoAct.tm_mon + 1, tiempoAct.tm_mday, tiempoAct.tm_hour, tiempoAct.tm_min);

    arch = fopen(nombreArch, "wt");
    if (!arch)
        return ERROR;

    //mientras tengamos nodos de la lista que registraron la partida
    while(*partidasJugadas)
    {
        // Procesa hasta "cantidadPartidas" registros o hasta que se acaben las partidas.
        while(i<=cantidadPartidas && *partidasJugadas)
        {

            totalPuntaje += registrarEnInformeJugadorPartidasPuntaje(arch,partidasJugadas,i);
            partidasJugadas=&(*partidasJugadas)->sig;
            i++;
        }
        //registra el informe los jugadores con los mayores puntajes
        registrarEnInformePuntosTotalesXJugador(arch,totalPuntaje);
        totalPuntaje=0;
        i=1;

    }
    registrarEnInformeMayoresPuntajes(arch,listaJugadores,cmp);

    fclose(arch);

    return TODO_OK;
}
