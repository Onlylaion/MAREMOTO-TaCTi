#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define SIN_MEM 1
#define CLA_DUP 2
#define TODO_BIEN 0
#define minimo(X, Y) ((X) <= (Y) ? (X) : (Y))

typedef struct sNodo {
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;
typedef tNodo *tLista;

typedef struct
{
    int puntaje;
    char nya[31];
}tjugador;
//todo este elenco abarca la función de carga
void crearLista(tLista *p);
int ponerAlFinal(tLista *p, const void *d, unsigned cantBytes);
int ponerAlComienzo(tLista *p, const void *d, unsigned cantBytes);
int listaVacia(const tLista *p);
int listaLlena(const tLista *p, unsigned cantBytes);
void cargar_jugadores(tLista*pl);
//void mostrar
void mostraDatos(void*info);
void map(tLista*pl,void accion(void *info));





int main()
{
    tLista pl;
    crearLista(&pl);
    srand(time(NULL)); // Inicializa la semilla
    cargar_jugadores(&pl);
    map(&pl,mostraDatos);
    return 0;
}

void cargar_jugadores(tLista*pl)
{
    tjugador ply;

    printf("Ingresar el nombre del jugador\n");
    printf("Para finalizar la carga de jugadores escriba 'fin'\n");
    gets(ply.nya);
    while(strcmpi(ply.nya,"FIN")!=0)
    {
        ply.puntaje=0; //por las moscas
        int aleatorio = rand() % 2;  // Genera 0 o 1 directamente
//al pedo total si está vacía va a ponerse primero
//        if(!listaVacia(pl))
//            ponerAlComienzo(pl,&ply,sizeof(tjugador));

        if(aleatorio == 0)
            ponerAlComienzo(pl,&ply,sizeof(tjugador));

        else
            ponerAlFinal(pl,&ply,sizeof(tjugador));

        printf("Ingresar el nombre del jugador\n");
        fflush(stdin);
        gets(ply.nya);
    }
}

// Inicializa la lista, asignándole NULL
void crearLista(tLista *p) {
    *p = NULL;
}

// Verifica si la lista está vacía
int listaVacia(const tLista *p) {
    return *p == NULL;
}

// Verifica si la lista está llena, intentando reservar memoria para un nodo y su contenido
int listaLlena(const tLista *p, unsigned cantBytes) {
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);
    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

// Vacía la lista liberando la memoria de todos sus nodos
void vaciarLista(tLista *p) {
    while (*p) {
        tNodo *aux = *p;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
}

// Inserta un elemento al comienzo de la lista
int ponerAlComienzo(tLista *p, const void *d, unsigned cantBytes) {
    tNodo *nue;

    // Intenta reservar memoria para el nuevo nodo y su información
    if ((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
        (nue->info = malloc(cantBytes)) == NULL) {
        free(nue);
        return 0;  // Error de memoria
    }

    // Copia la información al nuevo nodo
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;

    // Inserta el nuevo nodo al inicio de la lista
    nue->sig = *p;
    *p = nue;

    return 1;
}

// Extrae el primer elemento de la lista
int sacarPrimeroLista(tLista *p, void *d, unsigned cantBytes) {
    tNodo *aux = *p;

    if (aux == NULL)  // Si la lista está vacía, no se puede extraer
        return 0;

    *p = aux->sig;  // Mueve el puntero de la lista al siguiente nodo

    // Copia la información del nodo eliminado al buffer de salida
    memcpy(d, aux->info, minimo(cantBytes, aux->tamInfo));

    free(aux->info);
    free(aux);

    return 1;
}

// Obtiene el primer elemento de la lista sin eliminarlo
int verPrimeroLista(const tLista *p, void *d, unsigned cantBytes) {
    if (*p == NULL)  // Si la lista está vacía, no hay nada que ver
        return 0;

    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}

// Inserta un elemento al final de la lista
int ponerAlFinal(tLista *p, const void *d, unsigned cantBytes) {
    tNodo *nue;

    // Avanza hasta el final de la lista
    while (*p)
        p = &(*p)->sig;

    // Intenta reservar memoria para el nuevo nodo y su información
    if ((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
        (nue->info = malloc(cantBytes)) == NULL) {
        free(nue);
        return 0;  // Error de memoria
    }

    // Copia la información y asigna el nodo como último
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    *p = nue;

    return 1;
}

// Extrae el último elemento de la lista
int sacarUltimoLista(tLista *p, void *d, unsigned cantBytes) {
    if (*p == NULL)  // Si la lista está vacía, no se puede extraer
        return 0;

    // Avanza hasta el último nodo
    while ((*p)->sig)
        p = &(*p)->sig;

    // Copia la información del último nodo antes de eliminarlo
    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));

    free((*p)->info);
    free(*p);
    *p = NULL;  // La lista queda vacía si era el único nodo

    return 1;
}

// Obtiene el último elemento de la lista sin eliminarlo
int verUltimoLista(const tLista *p, void *d, unsigned cantBytes) {
    if (*p == NULL)  // Si la lista está vacía, no hay nada que ver
        return 0;

    // Avanza hasta el último nodo
    while ((*p)->sig)
        p = &(*p)->sig;

    memcpy(d, (*p)->info, minimo(cantBytes, (*p)->tamInfo));
    return 1;
}

void map(tLista*pl, void accion(void*info))
{
    tLista aux = *pl;
    while(aux)
    {
        accion(aux->info);
        aux = aux->sig;
    }
}

void mostraDatos(void*info)
{
    tjugador *jug=(tjugador *)info;
    printf("%s\t,%d \n",jug->nya,jug->puntaje);
}
