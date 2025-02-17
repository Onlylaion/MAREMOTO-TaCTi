#ifndef TDALISTA_H_INCLUDED
#define TDALISTA_H_INCLUDED

#define MINIMO(x,y)((x > y) ? x : y )
#define TODO_OK 1
#define DUPLICADO 2
#define LIMITE_ALCANZADO 3
#define ERROR_MEM 2
#define ERROR_ARCH 3
#define SIN_MEM 2
#define ERROR 0

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;

void listaCrear(tLista * l);
int listaVacia(tLista* l);
int listaInsertarAlInicio(tLista *l,void* elem, unsigned tamElem);
int listaInsertarEnPosAleatoria(tLista* l, int limite, void* elem, unsigned tamElem, int (*cmp)(const void* a, const void* b));
int listaInsertarAlFinal(tLista* l,void* elem,unsigned tamElem);
int ordenarLista(tLista* l,int (*cmp)(const void*, const void* ));
void listaVaciar(tLista *l);
void listaFuncionMap(tLista* l, void (*accion)(const void*,const void*));
int insertarOrdenadoLimitado(tLista* pl, int limite, const void* elem, unsigned tamElem,int (*cmp)(const void*, const void*));

#endif // TDALISTA_H_INCLUDED
