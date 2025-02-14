#include "Juego.h"
#include "TDALista.h"
#include "conectarApi.h"


int main(int arg,char** arg2)
{
    srand(time(NULL));
    char tablero[TAM][TAM];
    tLista listaJugadores;
    tLista listaPartidas;
    tConfiguracion configuracion;

    if(arg!=2)
        return ERROR;

    listaCrear(&listaJugadores);
    listaCrear(&listaPartidas);
    inicializarTablero(tablero);
    obtenerDatosArchConfiguracion(arg2[ARCHIVO_CONFIG],&configuracion);

    menu(&listaJugadores,&listaPartidas,&configuracion, tablero);
}






