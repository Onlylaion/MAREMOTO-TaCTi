#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "Juego.h"
#include "TDALista.h"


int compararNombre(void*a, void* b)
{
    return strcmpi((char*)a,(char*)b)==0 ? 1 : 0;
}
int compararPuntajeTotal(const void* a, const void* b)
{
    return ((tJugador*)a)->puntaje < ((tJugador*)b)->puntaje ? 1 : -1;
}
int compararPuntajeTotalIgual(const void* a, const void* b)
{
    return ((tJugador*)a)->puntaje == ((tJugador*)b)->puntaje ? 1 : 0;
}

int obtenerDatosArchConfiguracion(char* ruta, tConfiguracion* configuracion)
{
    char cadena[TAM_CADENA_ARCH];
    FILE* arch = fopen(ruta,"rt");
    if(!arch)
        return ERROR_ARCH;

    fgets(cadena,TAM_CADENA_ARCH,arch);
    sscanf(cadena,"%[^|]|%[^\n]",configuracion->urlApi,configuracion->codIdenGrupo);
    fgets(cadena,TAM,arch);
    sscanf(cadena,"%d",&configuracion->CantPartidas);
    fclose(arch);

    return TODO_OK;
}

int registrarMovEnTablero(char tablaTaTeTi[][3], char letra, int x, int y)
{

    if(x>=12 && x<=17 && y>=3 && y<=7)
        return tablaTaTeTi[0][0]==' ' ? (tablaTaTeTi[0][0]=letra) : 0;
    else if(x>=19 && x<=25 && y>=3 && y<=7)
        return tablaTaTeTi[0][1]==' ' ? (tablaTaTeTi[0][1]=letra) : 0;
    else if(x>=27 && x<=33 && y>=3 && y<=7)
        return tablaTaTeTi[0][2]==' ' ? (tablaTaTeTi[0][2]=letra) : 0;
    else if(x>=12 && x<=17 && y>=8 && y<=12)
        return tablaTaTeTi[1][0]==' ' ? (tablaTaTeTi[1][0]=letra) : 0;
    else if(x>=19 && x<=25 && y>=8 && y<=12)
        return tablaTaTeTi[1][1]==' ' ? (tablaTaTeTi[1][1]=letra) : 0;
    else if(x>=27 && x<=33 && y>=8 && y<=12)
        return tablaTaTeTi[1][2]==' ' ? (tablaTaTeTi[1][2]=letra) : 0;
    else if(x>=12 && x<=17 && y>=14 && y<=17)
        return tablaTaTeTi[2][0]==' ' ? (tablaTaTeTi[2][0]=letra) : 0;
    else if(x>=19 && x<=25 && y>=14 && y<=17)
        return tablaTaTeTi[2][1]==' ' ? (tablaTaTeTi[2][1]=letra) : 0;
    else if(x>=27 && x<=33 && y>=14 && y<=17)
        return tablaTaTeTi[2][2]==' ' ? (tablaTaTeTi[2][2]=letra) : 0;
    return 0;
}

void detectarMovDelJugador(char tablero[][3], char letra)
{

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD eventos;
    INPUT_RECORD ir;
    int x,y;

    // Habilita la captura de eventos de mouse
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    while (1)
    {
        ReadConsoleInput(hIn, &ir, 1, &eventos);
        // Si se detecta un evento de mouse y se presiona el botón izquierdo
        if (ir.EventType == MOUSE_EVENT && ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            x = ir.Event.MouseEvent.dwMousePosition.X;
            y = ir.Event.MouseEvent.dwMousePosition.Y;

            if(registrarMovEnTablero(tablero,letra, x, y))
            {
                system("cls");
                fflush(stdout);
                Sleep(10);
                return;
            }
            else
            {
                printf("Error al realizar el movimiento.\n");
                Sleep(100);
                fflush(stdout);
            }
        }
    }
}

char obtenerOpcionDeMenu()
{
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD eventos;
    INPUT_RECORD ir;
    int x,y;

    // Habilita la captura de eventos de mouse
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    while (1)
    {
        ReadConsoleInput(hIn, &ir, 1, &eventos);
        // Si se detecta un evento de mouse y se presiona el botón izquierdo
        if (ir.EventType == MOUSE_EVENT && ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            x = ir.Event.MouseEvent.dwMousePosition.X;
            y = ir.Event.MouseEvent.dwMousePosition.Y;

            if(x>=2&& x<=9 && y == 0)
            {
                return 'A';
            }
            if(x>=2&& x<=22 && y == 2)
            {
                return 'B';
            }
            if(x>=2&& x<=9 && y == 4)
            {
                return 'C';
            }

        }

    }

}

void menu(tLista* listaJugadores,tLista* listaPartidas,tConfiguracion* configuracion, char tablero[TAM][TAM])
{

    char opcion;

    do
    {
        printf(" [A] Jugar\n\n [B] Ver ranking equipo\n\n [C] Salir\n ");
        opcion = obtenerOpcionDeMenu();
        fflush(stdin);
        system("cls");

        if(opcion!='A'&&opcion!='B'&&opcion!='C')
        {
            printf("\n Opcion ingresada incorrecta...\n\n");
            fflush(stdin);
            getchar();
            system("cls");
        }
        else
        {
            switch(opcion)
            {
                case 'A':
                {
                    ingresarJugadores(listaJugadores);
                    if(*listaJugadores)
                    {
                        mostrarEnOrdenJugadores(listaJugadores);
                        Jugar(tablero,listaJugadores,listaPartidas,configuracion,compararNombre);
                    }
                    else
                    {
                        printf("No se ha ingresado ningun jugador...");
                        fflush(stdin);
                        getchar();
                        system("cls");
                    }

                }
                break;
                case 'B':
                {

                }
                break;
                case 'C':
                    return;
            }
        }

    }
    while(opcion!='A'&&opcion!='B'&&opcion!='C');

    return;
}

void mostrarEnOrdenJugadores(tLista* jugadores)
{
    int i=1;

    printf("Orden de Juego:\n");
    while(*jugadores)
    {
        printf("%d-%s\n",i,((tJugador*)(*jugadores)->info)->nombre);
        i++;
        jugadores=&(*jugadores)->sig;
    }
    printf("\nPresione enter para comenzar el juego...");
    fflush(stdin);
    getchar();
}

void inicializarTablero(char tablero[TAM][TAM])
{

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            tablero[i][j] = ' ';
        }
    }

}

void mostrarTablero(char tablero[TAM][TAM])
{
    printf("\n\n\n");

    for (int i = 0; i < TAM; i++)
    {
        // Imprime las filas del tablero
        for (int fila = 0; fila < 4; fila++)
        {
            printf("           "); // Espaciado para centrar el tablero

            for (int j = 0; j < TAM; j++)
            {
                if (fila == 2)
                    printf("   %c   ", tablero[i][j]);
                else
                    printf("       ");

                if (j < TAM - 1) printf("|");  // Separadores verticales
            }
            printf("\n");
        }

        // linea horizontal
        if (i < TAM - 1)
            printf("           =======|=======|=======\n");
    }
}

char verificarGanador(char tablero[TAM][TAM])
{

    // verifica horizontal y vertical
    for(int i = 0; i < TAM; i++)
    {
        if (tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) return tablero[i][0];
        if (tablero[0][i] != ' ' && tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i]) return tablero[0][i];
    }

    // verifica diagonales
    if (tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) return tablero[0][0];
    if (tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) return tablero[0][2];

    return ' ';
}

void movimientoIA(char tablero[TAM][TAM], char letra)
{

    int fila, columna;

    if (puedeGanar(tablero, 'O', &fila, &columna) || puedeGanar(tablero, 'X', &fila, &columna))
    {
        tablero[fila][columna] = letra;
        return;
    }

    do
    {
        fila = rand() % TAM;
        columna = rand() % TAM;
    }
    while (tablero[fila][columna] != ' ');

    tablero[fila][columna] = letra;

    return;
}

int puedeGanar(char tablero[TAM][TAM], char jugador, int* fila, int* columna)
{

    for (int i = 0; i < TAM; i++)
    {

        for (int j = 0; j < TAM; j++)
        {

            if (tablero[i][j] == ' ')
            {

                tablero[i][j] = jugador;

                if (verificarGanador(tablero) == jugador)
                {
                    *fila = i;
                    *columna = j;
                    tablero[i][j] = ' ';
                    return 1;
                }

                tablero[i][j] = ' ';
            }
        }
    }

    return 0;
}

char quienEmpieza()
{
    if(rand()%2 == 1)
        return 'X';
    else
        return 'O';
}

void actualizarPantalla(char tablero[TAM][TAM], char jugador, char ia)
{

    system("cls");
    printf("Jugador: %c | IA: %c\n", jugador, ia);
    mostrarTablero(tablero);

    return;
}

void ingresarJugadores(tLista* pl)
{
    tJugador jugador;
    int cantidad=0;

    printf("Ingresar Nombres(termina con FIN/fin):\n");
    scanf("%s",jugador.nombre);
    jugador.puntaje=0;

    while(strcmpi(jugador.nombre,"FIN")!=0)
    {
        listaInsertarEnPosAleatoria(pl,cantidad,&jugador,sizeof(jugador));
        cantidad++;
        fflush(stdin);
        scanf("%s",jugador.nombre);
        jugador.puntaje=0;
    }
    system("cls");
}

void registrarPartida(tLista* partidas, void* jugador, char tablero[][TAM],int puntajeObtenido)
{
    tPartida partida;
    tJugador* auxJugador=(tJugador*)jugador;
    int i,j;

    for( i=0; i<TAM; i++)
    {
        for( j=0; j<TAM; j++)
            partida.tablero[i][j]= tablero[i][j];
    }

    partida.puntajeObtenido = puntajeObtenido;
    strcpy(partida.jugador,auxJugador->nombre);
    listaInsertarAlFinal(partidas,&partida,sizeof(partida));

}

void quienGana(tNodo* listaJugadores,tLista* partidas,char tablero[][TAM],char ganador,char turnoJugador, void(*accion)(tLista*, void*, char[][TAM],int))
{
    tJugador* jugador = (tJugador*)listaJugadores->info;

    if (ganador == turnoJugador )
    {
        printf("\nEl jugador %s gana!!\n", jugador->nombre);
        jugador->puntaje +=3;
        accion(partidas,jugador,tablero,3);
    }
    else if(ganador!=' ')
    {
        printf("\nLa IA gana!!\n");
        jugador->puntaje -=1;
        accion(partidas,jugador,tablero,-1);
    }
    else
    {
        printf("\nEs un empate!!\n");
        jugador->puntaje +=2;
        accion(partidas,jugador,tablero,2);
    }
}

int preparadoSiONo(void* jugador )
{
    tJugador* a = (tJugador*)jugador;
    char opcion[3];
    do
    {
        system("cls");
        printf("Jugador %s, estas preparado?(Si/No)\n Ingresa la opcion: ",a->nombre);
        scanf("%s",opcion);
    }
    while( strcmpi(opcion,"SI")!=0);
    return TODO_OK;
}

void registrarEnInformeMayoresPuntajes(FILE* arch,tLista* listaJugadores,int (*cmp)(const void*, const void*))
{
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
    int j;
    tPartida* auxPartida = (tPartida*) (*partidasJugadas)->info;

    if(numeroDePartida==1)
        fprintf(arch,"Jugador: %s\n\n", auxPartida ->jugador);

    fprintf(arch,"Partida numero %d: \n\n",numeroDePartida);
    for(j=0; j<TAM; j++)
    {
        fprintf(arch,"\t%c | %c | %c\n",auxPartida ->tablero[j][0],auxPartida ->tablero[j][1],auxPartida ->tablero[j][2]);
    }
    fprintf(arch,"\nPuntos Obtenidos: %d \n\n",auxPartida ->puntajeObtenido);

    fflush(arch);
    return auxPartida->puntajeObtenido;
}
void registrarEnInformePuntosTotalesXJugador(FILE* arch,int PuntosTotales)
{
    fprintf(arch,"TOTAL DE PUNTOS: %d \n----------------------------------\n\n", PuntosTotales);
    fflush(arch);
}

int generarInformeDeGrupo(tLista* listaJugadores, tLista* partidasJugadas,int cantidadPartidas,int (*cmp)(const void*, const void*))
{
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


    while(*partidasJugadas)
    {

        while(i<=cantidadPartidas && *partidasJugadas)
        {

            totalPuntaje += registrarEnInformeJugadorPartidasPuntaje(arch,partidasJugadas,i);
            partidasJugadas=&(*partidasJugadas)->sig;
            i++;
        }
        registrarEnInformePuntosTotalesXJugador(arch,totalPuntaje);
        totalPuntaje=0;
        i=1;

    }
    registrarEnInformeMayoresPuntajes(arch,listaJugadores,cmp);

    fclose(arch);

    return TODO_OK;
}

int Jugar(char tablero[][3],tLista* listaJugadores,tLista* ListaPartidas,tConfiguracion* configuracion,int (cmp)(void*, void*))
{
    char ganador = ' ';
    int movimientos = 0, cantPartidasJugadas = 0;
    char turnoJugador;
    tNodo* jugadores = *listaJugadores;


    while(jugadores)
    {

        preparadoSiONo(jugadores->info);

        while(cantPartidasJugadas<configuracion->CantPartidas)
        {
            turnoJugador=quienEmpieza();

            while(ganador == ' ' && movimientos < TAM * TAM)
            {

                if(turnoJugador == 'X')
                {
                    actualizarPantalla(tablero,'X','O');
                    detectarMovDelJugador(tablero,'X');
                    movimientos++;
                    ganador = verificarGanador(tablero);

                    if(ganador==' ' && movimientos<TAM*TAM)
                    {
                        movimientoIA(tablero,'O');
                        movimientos++;
                        ganador = verificarGanador(tablero);
                    }
                }
                else
                {
                    movimientoIA(tablero,'X');
                    movimientos++;
                    ganador = verificarGanador(tablero);
                    actualizarPantalla(tablero,'O','X');

                    if(ganador==' '&& movimientos<TAM*TAM)
                    {
                        detectarMovDelJugador(tablero,'O');
                        movimientos++;
                        ganador = verificarGanador(tablero);
                    }
                }
            }

            actualizarPantalla(tablero,turnoJugador=='X'?'X':'O',turnoJugador=='O'?'X':'O');
            quienGana(jugadores,ListaPartidas,tablero,ganador,turnoJugador,registrarPartida);


            printf("\nPresione enter para comenzar el siguiente juego...");
            fflush(stdin);
            getchar();


            ganador=' ';
            movimientos=0;
            cantPartidasJugadas++;
            inicializarTablero(tablero);
        }
        jugadores=jugadores->sig;
        cantPartidasJugadas=0;
    }
    ordenarLista(listaJugadores,compararPuntajeTotal);
    generarInformeDeGrupo(listaJugadores,ListaPartidas,configuracion->CantPartidas,compararPuntajeTotalIgual);

    return 0;
}

