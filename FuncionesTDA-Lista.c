#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "TDALista.h"

void listaCrear(tLista * l)
{
    *l = NULL;
}

void listaInsertarAlInicio(tLista *l,void* elem, unsigned tamElem)
{
    tNodo* nuevo;

    nuevo= malloc(sizeof(tNodo));
    if(!nuevo)
        return;
    nuevo->info = malloc(tamElem);
    if(!nuevo->info)
    {
        free(nuevo);
        return;
    }
    nuevo->tamInfo=tamElem;
    memcpy(nuevo->info,elem,tamElem);

    nuevo->sig=*l;
    *l=nuevo;
}

void listaInsertarEnPosAleatoria(tLista* l, int limite, void* elem, unsigned tamElem)
{

    tNodo* nuevo;
    int n, i=0;

    nuevo= malloc(sizeof(tNodo));
    if(!nuevo)
        return;

    nuevo->info = malloc(tamElem);
    if(!nuevo->info)
    {
        free(nuevo);
        return;
    }
    nuevo->tamInfo=tamElem;
    memcpy(nuevo->info,elem,tamElem);

    if(!*l)
    {
        nuevo->sig=*l;
        *l=nuevo;
        return;
    }

    n= rand()%(limite+1);


    while(i< n && (*l)->sig)
    {
        l = &(*l)->sig;
        i++;
    }
    nuevo->sig= *l;
    *l = nuevo;
}
int listaInsertarAlFinal(tLista* l,void* elem,unsigned tamElem)
{
    tNodo* nuevo= malloc(sizeof(tNodo));

    if(!nuevo)
        return ERROR;

    nuevo->info= malloc(tamElem);

    if(!nuevo->info)
    {
        free(nuevo);
        return ERROR;
    }

    memcpy(nuevo->info, elem, tamElem);
    nuevo->tamInfo = tamElem;

    if(!*l)
    {
        nuevo->sig=*l;
        *l=nuevo;
        return TODO_OK;
    }

    while((*l)->sig)
    {
        l =&(*l)->sig;
    }
    nuevo->sig = (*l)->sig;
    (*l)->sig = nuevo;

    return TODO_OK;
}


int ordenarLista(tLista* p,int (*cmp)(const void*,const void*))
{

    tLista *pri = p;
    if (*p == NULL)
        return 0;
    while ((*p)->sig)
    {

        if (cmp((*p)->info, (*p)->sig->info) > 0)
        {

            tLista *q = pri;

            tNodo *auxNodo = (*p)->sig;

            (*p)->sig = auxNodo->sig;

            while (cmp((*q)->info, auxNodo->info) < 0)
                q = &(*q)->sig;

            auxNodo->sig = *q;
            *q = auxNodo;
        }
        else
            p = &(*p)->sig;
    }
    return 1;
}

void vaciarLista(tLista *lista)
{
    tNodo *elim;
    while(*lista)
    {
        elim = *lista;
        *lista = elim->sig;
        free(elim->info);
        free(elim);
    }
}
