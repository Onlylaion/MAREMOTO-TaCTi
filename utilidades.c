#include "utilidades.h"
#include "Juego.h"
#include <string.h>

int cmpNombres(const void* a, const void* b)
{
    return strcmp((((tJugador*)a)->nombre), (((tJugador*)b)->nombre));
}

int compararPuntajeTotal(const void* a, const void* b)
{
    return ((tJugador*)a)->puntaje < ((tJugador*)b)->puntaje ? 1 : -1;
}

int compararPuntajeTotalIgual(const void* a, const void* b)
{
    return ((tJugador*)a)->puntaje == ((tJugador*)b)->puntaje ? 1 : 0;
}

void mostrarJugador(const void* a,const void* b)
{
    int* posicion= (int*)b;
    tJugador* jugador=(tJugador*)a;
    printf("%d-%s\n",*posicion,jugador->nombre);
}

void actualizarJugador(void *a, void *b)
{
    tJugadorAPI *aa = (tJugadorAPI *) a;
    tJugadorAPI *bb = (tJugadorAPI *) b;

    aa->puntaje += bb->puntaje;
    strcpy(aa->fyh, bb->fyh);
}

int compararJugAPI(const void *a, const void *b)
{
    tJugadorAPI *aa = (tJugadorAPI *) a;
    tJugadorAPI *bb = (tJugadorAPI *) b;
    //Esta funci�n se encarga de ordenar jugadores seg�n:
    //Nombre (orden alfab�tico).
    //Puntaje (mayor puntaje primero).
    //Fecha y hora de la �ltima partida (m�s reciente primero en caso de empate).
    int resultado = strcmp(aa->nombre, bb->nombre);
    if( resultado != 0)
    {
        resultado = aa->puntaje - bb->puntaje;
        if ( resultado == 0)
        {
            resultado = compararFechaHora(aa->fyh, bb->fyh);
        }
    }

    return resultado;
}

int compararFechaHora(const char *fyh1, const char *fyh2)
{

    int resultado;
    tFechaHora fecha1, fecha2;

    sscanf(fyh1, "%2d/%2d/%4d %2d:%2d:%2d",
           &fecha1.dia, &fecha1.mes, &fecha1.anio,
           &fecha1.hora, &fecha1.minutos, &fecha1.segundos);

    sscanf(fyh2, "%2d/%2d/%4d %2d:%2d:%2d",
           &fecha2.dia, &fecha2.mes, &fecha2.anio,
           &fecha2.hora, &fecha2.minutos, &fecha2.segundos);

    resultado = fecha1.anio - fecha2.anio;
    if(resultado == 0)
    {
        resultado = fecha1.mes - fecha2.mes;
        if(resultado == 0)
        {
            resultado = fecha1.dia - fecha2.dia;
            if(resultado == 0)
            {
                resultado = fecha1.hora - fecha2.hora;

                if(resultado == 0)
                {
                    resultado = fecha1.minutos - fecha2.minutos;

                    if(resultado == 0)
                    {
                        resultado = fecha1.segundos - fecha2.segundos;
                    }
                }
            }
        }
    }

    return resultado;
}


void imprimirEncabezadoRanking()
{

    printf("| Pos | Nombre          | Puntaje Total | Ultima Partida       |\n");

}

void mostrarJugadorAPI(const void *a, const void *b)
{

    tJugadorAPI *aa = (tJugadorAPI *) a;

    int posicion = *(int *) b;

    printf("| %-3d | %-15s | %-13d | %-20s |\n",

           posicion, aa->nombre, aa->puntaje, aa->fyh);

}

int parsearJugadores(tRespuesta *res, tJugadorAPI *jugador)
{
    char *p = strrchr(res->info, '}');

    if(!p)
    {
        return 0;
    }

    p--;
    *p = '\0';

    p = strrchr(res->info, ',');
    p = strchr(p, ':');
    strcpy(jugador->fyh, p + 2);
    p = strrchr(res->info, ',');

    *p = '\0';
    p = strrchr(res->info, ',');
    p = strchr(p, ':');
    sscanf(p + 1, "%u", &jugador->puntaje);
    p = strrchr(res->info, ',');

    p--;
    *p = '\0';
    p = strrchr(res->info, '{');
    p = strchr(p, ':');
    strcpy(jugador->nombre, p + 2);
    p = strrchr(res->info, '{');

    *p = '\0';
    return 1;
}

void mostrarEnOrdenJugadores(tLista* jugadores,void (*accion)(const void*,const void*))
{
    printf("Orden de Juego:\n\n");
    listaFuncionMap(jugadores,accion);
    printf("\nPresione enter para comenzar el juego...");
    fflush(stdin);
    getchar();
}

int cadenaVacia(const char*p)
{
   return(p ==NULL || *p == '\0');
}
