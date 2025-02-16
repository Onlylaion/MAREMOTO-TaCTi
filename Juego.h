#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "TDALista.h"
#include "conectarApi.h"
#include <stdio.h>
#define TAM 3
#define TAM_URL 100
#define TAM_CADENA_ARCH 100
#define TAM_CADENA 100
#define ARCHIVO_CONFIG 1
#define TAM_MAX_JSON 200

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
    char tablero[TAM][TAM];

}tPartida;

typedef struct
{
    char urlApi[TAM_CADENA_ARCH];
    char codIdenGrupo[TAM_CADENA];
    int CantPartidas;

}tConfiguracion;

void normalizar_minusculas(char* str);
void prepararDatoJSON(tLista* listaJugadores,tConfiguracion* configuracion, char json_data[TAM_MAX_JSON]);
void mostrarJugador(const void* a,const void* b);
int compararPuntajeTotal(const void* a, const void* b);
int compararPuntajeTotalIgual(const void* a, const void* b);
int cmpNombres(const void* a, const void* b);

void inicializarTablero(char tablero[TAM][TAM]);
void mostrarTablero(char tablero[TAM][TAM]);
char verificarGanador(char tablero[TAM][TAM]);
void movimientoIA(char tablero[TAM][TAM], char, int);
int puedeGanar(char tablero[TAM][TAM], char jugador, int *fila, int *columna);
void actualizarPantalla(char tablero[TAM][TAM], char turno, char jugador, char ia);
char quienEmpieza();
char obtenerOpcionDeMenu();
void detectarMovDelJugador(char tablero[TAM][TAM], char letra);
int registrarMovEnTablero(char tablaTaTeTi[TAM][TAM], char letra, int x, int y);
void mostrarEnOrdenJugadores(tLista* jugadores,void (*accion)(const void*,const void*));
void quienGana(tNodo* listaJugadores,tLista* partidas,char tablero[][TAM],char ganador,char turnoJugador, void(*accion)(tLista*, void*, char[][TAM],int));
int preparadoSiONo(void* jugador );
int obtenerRanking(tLista *lista, tConfiguracion* configuracion);
void registrarPartida(tLista* partidas, void* jugador, char tablero[][TAM],int puntajeObtenido);

void cargarDificultad(int* num);

///FUNCIONES PARA GENERAR EL INFORME:
int generarInformeDeGrupo(tLista* listaJugadores, tLista* partidasJugadas,int cantidadPartidas,int (*cmp)(const void*, const void*));
void registrarEnInformeMayoresPuntajes(FILE* arch,tLista* listaJugadores,int (*cmp)(const void*, const void*));
int registrarEnInformeJugadorPartidasPuntaje(FILE* arch,tLista* partidasJugadas,int numeroDePartida);
void registrarEnInformePuntosTotalesXJugador(FILE* arch,int PuntosTotales);


///ESTO ES DE PRUEBA:
void menu(tLista* listaJugadores,tLista* listaPartidas,tConfiguracion* configuracion, char tablero[TAM][TAM]);
int Jugar(char tablero[][TAM], tLista* listaJugadores, int dif, tLista* ListaPartidas, tConfiguracion* configuracion);
void ingresarJugadores(tLista* pl);
int obtenerDatosArchConfiguracion(char* ruta, tConfiguracion* configuracion);
#endif // JUEGO_H_INCLUDED
