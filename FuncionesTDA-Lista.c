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
    tNodo* newNodo;

    newNodo= malloc(sizeof(tNodo));
    if(!newNodo)
        return;
    newNodo->info = malloc(tamElem);
    if(!newNodo->info)
    {
        free(newNodo);
        return;
    }
    newNodo->tamInfo=tamElem;
    memcpy(newNodo->info,elem,tamElem);

    newNodo->sig=*l;
    *l=newNodo;
}

void listaInsertarEnPosAleatoria(tLista* l, int limite, void* elem, unsigned tamElem)
{

    tNodo* newNodo;
    int n, i=0;

    newNodo= malloc(sizeof(tNodo));
    if(!newNodo)
        return;

    newNodo->info = malloc(tamElem);
    if(!newNodo->info)
    {
        free(newNodo);
        return;
    }
    newNodo->tamInfo=tamElem;
    memcpy(newNodo->info,elem,tamElem);

    if(!*l)
    {
        newNodo->sig=*l;
        *l=newNodo;
        return;
    }

    n= rand()%(limite+1);


    while(i< n && (*l)->sig)
    {
        l = &(*l)->sig;
        i++;
    }
    newNodo->sig= *l;
    *l = newNodo;
}
int listaInsertarAlFinal(tLista* l,void* elem,unsigned tamElem)
{
    tNodo* aux= malloc(sizeof(tNodo));

    if(!aux)
        return ERROR;

    aux->info= malloc(tamElem);

    if(!aux->info)
    {
        free(aux);
        return ERROR;
    }

    memcpy(aux->info, elem, tamElem);
    aux->tamInfo = tamElem;

    if(!*l)
    {
        aux->sig=*l;
        *l=aux;
        return TODO_OK;
    }

    while((*l)->sig)
    {
        l =&(*l)->sig;
    }
    aux->sig = (*l)->sig;
    (*l)->sig = aux;

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

            tNodo *aux = (*p)->sig;

            (*p)->sig = aux->sig;

            while (cmp((*q)->info, aux->info) < 0)
                q = &(*q)->sig;

            aux->sig = *q;
            *q = aux;
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
