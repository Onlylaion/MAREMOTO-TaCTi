#ifndef TDALISTA_H_INCLUDED
#define TDALISTA_H_INCLUDED

#define MINIMO(x,y)((x > y) ? x : y )
#define TODO_OK 1
#define ERROR_MEM 2
#define ERROR_ARCH 3
#define ERROR 0

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;

void listaCrear(tLista * l);
void listaInsertarAlInicio(tLista *l,void* elem, unsigned tamElem);
void listaInsertarEnPosAleatoria(tLista* l, int limite, void* elem, unsigned tamElem);
int listaInsertarAlFinal(tLista* l,void* elem,unsigned tamElem);
int ordenarLista(tLista* l,int (*cmp)(const void*, const void* ));
void vaciarLista(tLista *l);
void listaFuncionMap(tLista* l, int (*accion)(void*,void*));

#endif // TDALISTA_H_INCLUDED
