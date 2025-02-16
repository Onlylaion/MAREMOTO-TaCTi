#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "Juego.h"


int cmpNombres(const void* a, const void* b)
{
    return strcmp((((tJugador*)a)->nombre), (((tJugador*)b)->nombre));
}

void normalizar_minusculas(char* str)
{
    while (*str != '\0') {
        *str = tolower((unsigned char)*str);  // Convertir a minúsculas
        str++;  // Mover al siguiente carácter
    }
}

void ingresarJugadores(tLista* pl)
{
    tJugador jugador;
    int cantidad = 0;
    printf("Ingresar Nombres (termina con FIN/fin):\n");

    // Usamos fgets para leer el nombre
    fgets(jugador.nombre, sizeof(jugador.nombre), stdin);
    jugador.nombre[strcspn(jugador.nombre, "\n")] = '\0';  // Eliminar salto de línea

    jugador.puntaje = 0;

    // Convertir el nombre ingresado a minúsculas
    normalizar_minusculas(jugador.nombre);

    // Mientras el jugador no ingrese "FIN" o "fin"
    while (strcmp(jugador.nombre, "fin") != 0)  // Comparar con "fin" en minúsculas
    {
        listaInsertarEnPosAleatoria(pl, cantidad, &jugador, sizeof(jugador),cmpNombres);
        cantidad++;

        // Volver a leer el siguiente nombre
        fgets(jugador.nombre, sizeof(jugador.nombre), stdin);
        jugador.nombre[strcspn(jugador.nombre, "\n")] = '\0';  // Eliminar salto de línea

        // Convertir el nombre a minúsculas antes de la comparación
        normalizar_minusculas(jugador.nombre);

        jugador.puntaje = 0;
    }

    system("cls");
}

void mostrarJugador(const void* a,const void* b)
{
    int* posicion= (int*)b;
    tJugador* jugador=(tJugador*)a;
    printf("%d-%s\n",*posicion,jugador->nombre);
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

    if(x>=11 && x<=17 && y>=6 && y<=9)
        return tablaTaTeTi[0][0]==' ' ? (tablaTaTeTi[0][0]=letra) : 0;
    else if(x>=19 && x<=25 && y>=6 && y<=9)
        return tablaTaTeTi[0][1]==' ' ? (tablaTaTeTi[0][1]=letra) : 0;
    else if(x>=27 && x<=33 && y>=6 && y<=9)
        return tablaTaTeTi[0][2]==' ' ? (tablaTaTeTi[0][2]=letra) : 0;
    else if(x>=11 && x<=17 && y>=10 && y<=14)
        return tablaTaTeTi[1][0]==' ' ? (tablaTaTeTi[1][0]=letra) : 0;
    else if(x>=19 && x<=25 && y>=10 && y<=14)
        return tablaTaTeTi[1][1]==' ' ? (tablaTaTeTi[1][1]=letra) : 0;
    else if(x>=27 && x<=33 && y>=10 && y<=14)
        return tablaTaTeTi[1][2]==' ' ? (tablaTaTeTi[1][2]=letra) : 0;
    else if(x>=11 && x<=17 && y>=15 && y<=19)
        return tablaTaTeTi[2][0]==' ' ? (tablaTaTeTi[2][0]=letra) : 0;
    else if(x>=19 && x<=25 && y>=15 && y<=19)
        return tablaTaTeTi[2][1]==' ' ? (tablaTaTeTi[2][1]=letra) : 0;
    else if(x>=27 && x<=33 && y>=15 && y<=19)
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
//            printf("x: %d----y: %d\n",x,y);
            if(registrarMovEnTablero(tablero,letra, x, y))
            {
                system("cls");
                fflush(stdout);
                Sleep(10);
                return;
            }
            else
            {
                printf("\nError al realizar el movimiento.\n");
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

// en el menú ahora están las funciones 'ordenar lista' y 'generar informe'
void menu(tLista* listaJugadores,tLista* listaPartidas,tConfiguracion* configuracion, char tablero[TAM][TAM])
{
    char opcion;
    int dif;
    tLista listaRanking;
    char json_data[TAM_MAX_JSON];
    tRespuesta respuesta;

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
                cargarDificultad(&dif);
                if(*listaJugadores)
                {
                    mostrarEnOrdenJugadores(listaJugadores,mostrarJugador);
                    Jugar(tablero,listaJugadores,dif,listaPartidas,configuracion);
                    ordenarLista(listaJugadores,compararPuntajeTotal);
                    generarInformeDeGrupo(listaJugadores,listaPartidas,configuracion->CantPartidas,compararPuntajeTotalIgual);
                    prepararDatoJSON(listaJugadores,configuracion,json_data);
                    peticionPOST(&respuesta,listaJugadores,configuracion->urlApi,json_data);

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
                listaCrear(&listaRanking);
                if(obtenerRanking(&listaRanking, configuracion)){
                    printf("El ranking es: \n");
                    listaFuncionMap(&listaRanking, mostrarJugadorAPI);
                }
                printf("\nPresion enter para avanzar al menu...");
                fflush(stdout);
                getchar();
                vaciarLista(&listaRanking);

            }
            break;
            case 'C':
                return;
            }
        }

        system("cls");
    }
    while(opcion=='A'||opcion=='B'||opcion=='C');

    return;
}

int obtenerRanking(tLista *lista, tConfiguracion* configuracion){
    CURLcode res;
    tJugadorAPI jugador;
    tRespuesta resAPI  = {NULL, 0};
    char pathGet[TAM_CADENA_ARCH];

    snprintf(pathGet, TAM_CADENA_ARCH, "%s/%s", configuracion->urlApi, configuracion->codIdenGrupo);

    res = peticionGET(&resAPI, pathGet);
    if (res != CURLE_OK){
        printf("Error en la solicitud a la API.\n");
        return ERROR;
    }
    else{
        while(parsearJugadores(&resAPI, &jugador)){
            insertarOrdenadoLimitadoSinDuplicado(lista, 10, &jugador, sizeof(tJugadorAPI), compararJugAPI);
        }
    }
    free(resAPI.info);
    return TODO_OK;
}



void mostrarEnOrdenJugadores(tLista* jugadores,void (*accion)(const void*,const void*))
{
    printf("Orden de Juego:\n");
    listaFuncionMap(jugadores,accion);
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

// IA con dos niveles de dificultad
void movimientoIA(char tablero[TAM][TAM], char letraIA, int dificultad)
{
    int fila, columna;
    char letraJug;

    (letraIA == 'X') ? (letraJug = 'O') : (letraJug = 'X');

    if(dificultad == 1)
    {

        // si la IA puede ganar, lo hace. si no puede ganar, entonces bloquea al jugador.
        if (puedeGanar(tablero, letraIA, &fila, &columna) || puedeGanar(tablero, letraJug, &fila, &columna))
        {
            tablero[fila][columna] = letraIA;
            return;
        }

    }
    else
    {

        // la IA solo verifica si puede ganar.
        if (puedeGanar(tablero, letraIA, &fila, &columna))
        {
            tablero[fila][columna] = letraIA;
            return;
        }

    }

    do
    {
        fila = rand() % TAM;
        columna = rand() % TAM;
    }
    while (tablero[fila][columna] != ' ');

    tablero[fila][columna] = letraIA;

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

// Se asignan los simbolos aleatoriamente al jugador y a la IA
void asignarSimbolos(char* jugador, char* ia)
{
    if (rand() % 2 == 0)
    {
        *jugador = 'X';
        *ia = 'O';
    }
    else
    {
        *jugador = 'O';
        *ia = 'X';
    }
    return;
}

// Actualizar se usa mientras se está jugando y al final para mostrar quién ganó (por eso el parámetro turno es opcional, en el final no se usa)
void actualizarPantalla(char tablero[TAM][TAM], char jugador, char ia, char turno)
{
    system("cls");
    printf("Jugador: %c | IA: %c\n", jugador, ia);

    if(turno!='\0' && turno==jugador)
        printf("\n\nTurno de JUGADOR (%c):", jugador);
    else if(turno!='\0')
        printf("\n\nTurno de IA (%c):", ia);
    else
        printf("\n\nFIN DEL JUEGO!");

    mostrarTablero(tablero);

    return;
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

void quienGana(tNodo* listaJugadores,tLista* partidas,char tablero[][TAM],char ganador,char jug, void(*accion)(tLista*, void*, char[][TAM],int))
{
    tJugador* jugador = (tJugador*)listaJugadores->info;

    if (ganador == jug)
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
        printf("Jugador %s, estas preparado?\nPresiona enter para continuar... ",a->nombre);
        fflush(stdin);
        getchar();
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

//
void cargarDificultad(int* num)
{

    printf("Ingrese dificultad ('0' facil - '1' dificil) = ");
    scanf("%d", num);

    while(*num!=0 && *num!=1)
    {
        printf("Incorrecto. Ingrese '0' o '1': ");
        scanf("%d", num);
    }

    return;
}

// Modifiqué jugar para que haga lo mismo con dos ifs menos que eran muy parecidos. Agregué los char jugador y ia para no usar 'x' o 'y' directamente. Aparte, estos char son necesarios
// para que ande bien la funcion de la IA.
int Jugar(char tablero[][3], tLista* listaJugadores, int dif, tLista* ListaPartidas, tConfiguracion* configuracion)
{
    char ganador = ' ';
    char turno;
    char jugador, ia;
    int movimientos = 0, cantPartidasJugadas = 0;
    tNodo* jugadores = *listaJugadores;

    asignarSimbolos(&jugador, &ia);


    while(jugadores)
    {
        preparadoSiONo(jugadores->info);

        while(cantPartidasJugadas<configuracion->CantPartidas)
        {
            turno = 'X';

            while(ganador == ' ' && movimientos < TAM*TAM)
            {

                if(turno == jugador)
                {
                    actualizarPantalla(tablero,jugador,ia,turno);
                    detectarMovDelJugador(tablero,jugador);
                    movimientos++;
                    ganador = verificarGanador(tablero);
                    turno = ia;
                }
                else
                {
                    actualizarPantalla(tablero,jugador,ia,turno);
                    movimientoIA(tablero,ia,dif);
                    movimientos++;
                    ganador = verificarGanador(tablero);
                    turno = jugador;
                }

            }

            actualizarPantalla(tablero,jugador,ia,'\0');
            quienGana(jugadores,ListaPartidas,tablero,ganador,jugador,registrarPartida);

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

    return 0;
}
