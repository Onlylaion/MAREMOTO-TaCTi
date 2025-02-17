#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "TDALista.h"
#include "conectarApi.h"
#include <stdio.h>
#define TAM_TABLERO 3
#define TAM_URL 100
#define TAM_CADENA_ARCH 100
#define TAM_CADENA 100
#define ARCHIVO_CONFIG 1
#define TAM_MAX_JSON 200
#define LIMITE_RANKING 10

typedef struct
{
    char urlApi[TAM_CADENA_ARCH];
    char codIdenGrupo[TAM_CADENA];
    int CantPartidas;

}tConfiguracion;


typedef struct
{
    char nombre[TAM_CADENA];
    char letra;
    int puntaje;

}tJugador;

typedef struct
{
    char jugador[TAM_CADENA];
    int puntajeObtenido;
    char tablero[TAM_TABLERO][TAM_TABLERO];

}tPartida;



void prepararDatoJSON(tLista* listaJugadores, tConfiguracion* configuracion, char* json_data,unsigned tamJSON);
void inicializarTablero(char tablero[][TAM_TABLERO]);
void mostrarTablero(char tablero[][TAM_TABLERO]);
char verificarGanador(char tablero[][TAM_TABLERO]);
void movimientoIA(char tablero[][TAM_TABLERO], char, int);
int puedeGanar(char tablero[][TAM_TABLERO], char jugador, int *fila, int *columna);
void actualizarPantalla(char tablero[][TAM_TABLERO], char turno, char jugador, char ia);
char quienEmpieza();
char obtenerOpcionDeMenu();
void detectarMovDelJugador(char tablero[][TAM_TABLERO], char letra);
int registrarMovEnTablero(char tablaTaTeTi[][TAM_TABLERO], char letra, int x, int y);
void quienGana(tNodo* listaJugadores,tLista* partidas,char tablero[][TAM_TABLERO],char ganador,char turnoJugador, void(*accion)(tLista*, void*, char[][TAM_TABLERO],int));
int preparadoSiONo(void* jugador );
int obtenerRanking(tLista *lista, tConfiguracion* configuracion);
void registrarPartida(tLista* partidas, void* jugador, char tablero[][TAM_TABLERO],int puntajeObtenido);
void cargarDificultad(int* num);
void menu(tLista* listaJugadores,tLista* listaPartidas,tLista* listaRanking,tConfiguracion* configuracion, char tablero[][TAM_TABLERO]);
void Jugar(char tablero[][TAM_TABLERO], tLista* listaJugadores, int dif, tLista* ListaPartidas, tConfiguracion* configuracion);
void ingresarJugadores(tLista* pl);
int obtenerDatosArchConfiguracion(char* ruta, tConfiguracion* configuracion);

#endif // JUEGO_H_INCLUDED
