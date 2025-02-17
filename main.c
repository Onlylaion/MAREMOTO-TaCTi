#include "Juego.h"
#include "TDALista.h"
#include "conectarApi.h"


int main(int arg,char** arg2)
{
    srand(time(NULL));
    char tablero[TAM_TABLERO][TAM_TABLERO];
    tLista listaJugadores;
    tLista listaPartidas;
    tLista listaRanking;
    tConfiguracion configuracion;

    if(arg!=2)
        return ERROR;

    listaCrear(&listaJugadores);
    listaCrear(&listaPartidas);
    listaCrear(&listaRanking);
    inicializarTablero(tablero);

    obtenerDatosArchConfiguracion(arg2[ARCHIVO_CONFIG],&configuracion);
    menu(&listaJugadores,&listaPartidas,&listaRanking,&configuracion, tablero);


    listaVaciar(&listaJugadores);
    listaVaciar(&listaPartidas);
    listaVaciar(&listaRanking);

}






