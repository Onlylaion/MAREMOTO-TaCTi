#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "Juego.h"
#include "utilidades.h"
#include "informe.h"




void ingresarJugadores(tLista* pl)
{
    tJugador jugador;
    int cantidad = 0;

    printf("Ingresar Nombres (termina con FIN/fin):\n");

    // Usamos fgets para leer el nombre, permitiendo espacios
    fgets(jugador.nombre, sizeof(jugador.nombre), stdin);
    jugador.nombre[strcspn(jugador.nombre, "\n")] = '\0';
    jugador.puntaje = 0;

    // Convertir el nombre ingresado a minúsculas
    //normalizar_minusculas(jugador.nombre);

    while (strcmpi(jugador.nombre, "fin") != 0)
    {
        if (!listaInsertarEnPosAleatoria(pl, cantidad, &jugador, sizeof(jugador), cmpNombres))
            printf("Error: Nombre duplicado. Intente nuevamente.\n");
        else
        {
            cantidad++;
            jugador.puntaje = 0;
        }
        // Volver a leer el siguiente nombre con fgets para permitir espacios
        fflush(stdin);
        fgets(jugador.nombre, sizeof(jugador.nombre), stdin);
        jugador.nombre[strcspn(jugador.nombre, "\n")] = '\0';
        // Convertir el nombre a minúsculas antes de la comparación
        //        normalizar_minusculas(jugador.nombre);
    }
    system("cls");
}

int obtenerDatosArchConfiguracion(char* ruta, tConfiguracion* configuracion)
{
    char cadena[TAM_CADENA_ARCH];
    FILE* arch = fopen(ruta,"rt");
    if(!arch)
        return ERROR_ARCH;

    fgets(cadena,TAM_CADENA_ARCH,arch);
    sscanf(cadena,"%[^|]|%[^\n]",configuracion->urlApi,configuracion->codIdenGrupo);
    fgets(cadena,TAM_TABLERO,arch);
    sscanf(cadena,"%d",&configuracion->CantPartidas);
    fclose(arch);

    return TODO_OK;
}

int registrarMovEnTablero(char tablaTaTeTi[][TAM_TABLERO], char letra, int x, int y)
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

void detectarMovDelJugador(char tablero[][TAM_TABLERO], char letra)
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
        if (ir.EventType == MOUSE_EVENT && ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && ir.Event.MouseEvent.dwEventFlags != MOUSE_MOVED)
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


void menu(tLista* listaJugadores,tLista* listaPartidas,tLista* listaRanking,tConfiguracion* configuracion, char tablero[][TAM_TABLERO])
{
    // en el menú ahora están las funciones 'ordenar lista' y 'generar informe'
    char opcion;
    int dif;
    char jsonData[TAM_MAX_JSON];
    tRespuesta respuesta;

    do
    {
        //muestra las opciones en pantalla y verifica el ingreso correcto
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
            //En caso de elegir una opcion correcta
            switch(opcion)
            {
            case 'A':
            {
                //solicitamos ingreso de los jugadores y la dificultad
                ingresarJugadores(listaJugadores);
                cargarDificultad(&dif);
                system("cls");

                //si hay jugadores en la lista se inicia el juego
                if(*listaJugadores)
                {
                    //mostramos los jugadores en orden
                    mostrarEnOrdenJugadores(listaJugadores,mostrarJugador);
                    //ejecutamos la lógica del juego
                    Jugar(tablero,listaJugadores,dif,listaPartidas,configuracion);
                    //ordenamos la lista segun el puntaje
                    ordenarLista(listaJugadores,compararPuntajeTotal);

                    //generamos el informe acorde a la cantidad de partidas jugadas
                    generarInformeDeGrupo(listaJugadores,listaPartidas,configuracion->CantPartidas,compararPuntajeTotalIgual);
                    printf("\nSe ha generado un informe de las partidas y puntajes obtenidos del grupo de jugadores.\nPresiona enter para continuar...");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    prepararDatoJSON(listaJugadores,configuracion,jsonData,sizeof(jsonData));
                    peticionPOST(&respuesta,configuracion->urlApi,jsonData);
                    listaVaciar(listaJugadores);
                    listaVaciar(listaPartidas);

                }
                else
                {
                    printf("No se ha ingresado ningun jugador. Presionar enter para avanzar al menu...");
                    fflush(stdin);
                    getchar();
                    system("cls");
                }

            }
            break;
            case 'B':
            {
                //Obtenemos los datos de la Api para realizar el ranking.
                if(obtenerRanking(listaRanking, configuracion))
                {
                    if(!listaVacia(listaRanking))//verifico si la lista esta vacia, sino lo esta muestro el ranking.
                    {
                        imprimirEncabezadoRanking();
                        listaFuncionMap(listaRanking, mostrarJugadorAPI);
                    }
                    else
                        printf("No hay datos cargados en el ranking.\n");
                }
                printf("\nPresionar enter para avanzar al menu...");
                fflush(stdout);
                getchar();
                listaVaciar(listaRanking);

            }
            break;
            case 'C'://salimos del programa.
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

    snprintf(pathGet, sizeof(pathGet), "%s/%s", configuracion->urlApi, configuracion->codIdenGrupo);

    res = peticionGET(&resAPI, pathGet);
    if (res != CURLE_OK){
        printf("Error en la solicitud a la API.\n");
        return ERROR;
    }
    else{
        while(parsearJugadores(&resAPI, &jugador))
            insertarOrdenadoLimitado(lista, LIMITE_RANKING, &jugador, sizeof(tJugadorAPI), compararJugAPI);
    }
    free(resAPI.info);
    return TODO_OK;
}


void inicializarTablero(char tablero[][TAM_TABLERO])
{

    for (int i = 0; i < TAM_TABLERO; i++)
    {
        for (int j = 0; j < TAM_TABLERO; j++)
        {
            tablero[i][j] = ' ';
        }
    }

}

void mostrarTablero(char tablero[][TAM_TABLERO])
{
    printf("\n\n\n");

    for (int i = 0; i < TAM_TABLERO; i++)
    {
        // Imprime las filas del tablero
        for (int fila = 0; fila < 4; fila++)
        {
            // Espaciado para centrar el tablero
            printf("           ");


            for (int j = 0; j < TAM_TABLERO; j++)
            {
                if (fila == 2)
                    printf("   %c   ", tablero[i][j]);
                else
                    printf("       ");
                // Separadores verticales
                if (j < TAM_TABLERO - 1) printf("|");
            }
            printf("\n");
        }

        // linea horizontal
        if (i < TAM_TABLERO - 1)
            printf("           =======|=======|=======\n");
    }
}

char verificarGanador(char tablero[][TAM_TABLERO])
{

    // verifica horizontal y vertical
    for(int i = 0; i < TAM_TABLERO; i++)
    {
        if (tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) return tablero[i][0];
        if (tablero[0][i] != ' ' && tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i]) return tablero[0][i];
    }

    // verifica diagonales
    if (tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) return tablero[0][0];
    if (tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) return tablero[0][2];

    return ' ';
}


void movimientoIA(char tablero[TAM_TABLERO][TAM_TABLERO], char letraIA, int dificultad)
{
    // IA con dos niveles de dificultad
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
    //movimiento aleatorio si no se encuentra una jugada ganadora o de bloqueo
    do
    {
        fila = rand() % TAM_TABLERO;
        columna = rand() % TAM_TABLERO;
    }
    while (tablero[fila][columna] != ' ');

    tablero[fila][columna] = letraIA;

    return;
}

int puedeGanar(char tablero[][TAM_TABLERO], char jugador, int* fila, int* columna)
{

    for (int i = 0; i < TAM_TABLERO; i++)
    {

        for (int j = 0; j < TAM_TABLERO; j++)
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


void asignarSimbolos(char* jugador, char* ia)
{
    // Se asignan los símbolos aleatoriamente al jugador y a la IA
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

void actualizarPantalla(char tablero[TAM_TABLERO][TAM_TABLERO], char jugador, char ia, char turno)
{
     // Actualizar se usa mientras se está jugando y al final para mostrar quién ganó (por eso el parámetro turno es opcional, en el final no se usa)
    //limpiamos la consola
    system("cls");
    //mostramos que caracter le toca al usuario y a la IA
    printf("\t      Jugador: %c | IA: %c\n", jugador, ia);
    //Si el turno no es '\0' entonces la partida sigue en curso
    if(turno!='\0' && turno==jugador)
    {
        printf("\n\n\t    Turno de JUGADOR (%c):", jugador);
        mostrarTablero(tablero);
    }//si turno es '\0', significa que el juego ha terminado
    else if(turno!='\0')
    {
        printf("\n\n\t       Turno de IA (%c):", ia);
        //mostramos el tablero para visualizar como va la partida
        mostrarTablero(tablero);
        //salimos de la funcion
        Sleep(1000);
    }
    else
    {
        mostrarTablero(tablero);
        printf("\n\n\t        FIN DEL JUEGO!!");
    }
    return;
}


void registrarPartida(tLista* partidas, void* jugador, char tablero[][TAM_TABLERO],int puntajeObtenido)
{
    tPartida partida;
    tJugador* auxJugador=(tJugador*)jugador;
    int i,j;

    for( i=0; i<TAM_TABLERO; i++)
    {
        for( j=0; j<TAM_TABLERO; j++)
            partida.tablero[i][j]= tablero[i][j];
    }
    //Cargamos el puntaje de la partida
    partida.puntajeObtenido = puntajeObtenido;
    //cargamos el nombre del jugador
    strcpy(partida.jugador,auxJugador->nombre);
    //insertamos toda la información
    listaInsertarAlFinal(partidas,&partida,sizeof(partida));
}


void quienGana(tNodo* listaJugadores,tLista* partidas,char tablero[][TAM_TABLERO],char ganador,char jug, void(*accion)(tLista*, void*, char[][TAM_TABLERO],int))
{
    //guardamos la información del jugador en una variable axiliar para luego decidir quien gano
    tJugador* jugador = (tJugador*)listaJugadores->info;
    //Caso donde el jugador salio victorioso, se imprime el msj y sumamos 3 puntos
    if (ganador == jug)
    {
        printf("\n\n\t    El jugador %s gana!!\n", jugador->nombre);
        jugador->puntaje +=3;
        accion(partidas,jugador,tablero,3);
    }//Caso donde el jugador salio NO victorioso, se imprime el msj y restamos 1 punto
    else if(ganador!=' ')
    {
        printf("\n\n\t         La IA gana!!\n");
        jugador->puntaje -=1;
        accion(partidas,jugador,tablero,-1);
    }//Si no gano, ni perdión, la 3 opción es el empate
    else
    {
        printf("\n\n\t        Es un empate!!\n");
        jugador->puntaje +=2;
        accion(partidas,jugador,tablero,2);
    }
}

int preparadoSiONo(void* jugador )
{
    tJugador* a = (tJugador*)jugador;
    system("cls");
    printf("\nJugador %s, estas preparado?\n\nPresiona enter para continuar... ",a->nombre);
    fflush(stdin);
    getchar();
    return TODO_OK;
}

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


void Jugar(char tablero[][TAM_TABLERO], tLista* listaJugadores, int dif, tLista* ListaPartidas, tConfiguracion* configuracion)
{
    char ganador = ' ';
    char turno;
    char jugador, ia;
    int movimientos = 0, cantPartidasJugadas = 0;
    tNodo* jugadores = *listaJugadores;




    while(jugadores)
    {
        //pregunto antes de iniciar al jugador si esta listo
        preparadoSiONo(jugadores->info);

        while(cantPartidasJugadas<configuracion->CantPartidas)
        {
            turno = 'X';
            //asigno el simbolo de forma aleatoria, cada que termina una partida
            asignarSimbolos(&jugador, &ia);

            while(ganador == ' ' && movimientos < TAM_TABLERO*TAM_TABLERO)
            {
                if(turno == jugador)//caso en el que el jugador comienza
                {
                    actualizarPantalla(tablero,jugador,ia,turno);
                    detectarMovDelJugador(tablero,jugador);
                    movimientos++;
                    ganador = verificarGanador(tablero);
                    turno = ia;
                }
                else//caso en el que la IA comienza
                {
                    actualizarPantalla(tablero,jugador,ia,turno);
                    movimientoIA(tablero,ia,dif);
                    movimientos++;
                    ganador = verificarGanador(tablero);
                    turno = jugador;
                }

            }

            actualizarPantalla(tablero,jugador,ia,'\0');

            //Determino el ganador de la partida por pantalla
            //A su vez registro las partidas, en una lista para poder generar luego el informe
            quienGana(jugadores,ListaPartidas,tablero,ganador,jugador,registrarPartida);

            ganador=' ';
            movimientos=0;
            cantPartidasJugadas++;
            inicializarTablero(tablero);

            if(cantPartidasJugadas!=configuracion->CantPartidas)
                printf("\nPresione enter para comenzar el siguiente juego...");
            else
                printf("\nPresione enter para continuar...");
            fflush(stdin);
            getchar();


        }

        jugadores=jugadores->sig;
        cantPartidasJugadas=0;
    }
    system("cls");
}
