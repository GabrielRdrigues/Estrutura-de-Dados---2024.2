#include "grafoTAD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct lista
{
    int destino;
    void* custo;
    struct lista *prox;
}lista;

struct grafo
{
    lista** g;
    int n; // Número de vértices
};

Grafo Inicializar()
{
    Grafo grapho = (Grafo) malloc(sizeof(Grafo));
    grapho->n=10;
    grapho->g = (lista**)malloc(((grapho->n)+1)*sizeof(lista*));
    return grapho;
}

void free_list(lista* head){
   if(head){
       free_list(head->prox);
       free(head);
   }
}

Grafo Destruir(Grafo G)
{
    for(int i=0;i<=G->n;i++)
    {
        free_list(G->g[i]);
    }
}

lista* inserirLista(lista* l,int chave,void* custo,int SizeObj)
{
    lista* aux = (lista*)malloc(sizeof(lista));
    aux->custo = malloc(SizeObj);
    memcpy(aux->custo,custo,SizeObj);
    aux->destino = chave;
    aux->prox = l;
    return aux;
}

void Inserir_Aresta(Grafo G,int chave /*chave=destino*/,void* custo,int SizeObj,int origem)
{
    G->g[origem] = inserirLista(G->g[origem],chave,custo,SizeObj);
}

lista* removerLista(lista* l,int destino,void* custo,int SizeObj)
{
    if(l->destino=destino)
    {
        lista* aux = l->prox;
        memcpy(custo,l->custo,SizeObj);
        free(l->custo);
        free(l);
        return aux;
    }
    lista* p = l;
    lista* n = p->prox;
    while(n!=NULL)
    {
        if(n->destino==destino)
        {
            p->prox=n->prox;
            memcpy(custo,n->custo,SizeObj);
            free(n->custo);
            free(n);
        }
        p=p->prox;
    }
    return l;
}

void Remover_Aresta(Grafo G,void* custo,int SizeObj,int origem,int destino)
{
    G->g[origem] = removerLista(G->g[origem],destino,custo,SizeObj);
}

void imprimir_lista(lista* l)
{
    lista* auxiliar = l;
    while(auxiliar!=NULL)
    {
        printf("Destino:[%d] ",auxiliar->destino);
        auxiliar=auxiliar->prox;
    }
}

void Imprimir_Grafo(Grafo G)
{
    for(int i=1;i<=G->n;i++)
    {
        printf("Origem:[%d] | ",i);
        imprimir_lista(G->g[i]);
        printf("\n");
    }
}

int conta_origem(lista* l) {
    int count = 0;
    lista* aux = l;
    while(aux != NULL) {
        count++;
        aux = aux->prox;
    }
    return count;
}

int conta_vertice(lista* l, int vertice) {
    int count = 0;
    lista* aux = l;
    while (aux != NULL) {
        if (aux->destino == vertice)
            count++;
        aux = aux->prox;
    }
    return count;
}

int Grau_Vertice(Grafo G,int vertice) {
    int count = 0;
    for (int i=1; i<=G->n; i++) {
        if (i==vertice) {
            count += conta_origem(G->g[i]);
        }
        count += conta_vertice(G->g[i], vertice);
    }
    return count;
}

void* procura_lista(lista* l,int destino)
{
    lista* aux = l;
    while(aux!=NULL)
    {
        if(aux->destino==destino)
            return aux->custo;
        aux=aux->prox;
    }
    return NULL;
}

void* Search(Grafo G,int destino,int origem)
{
    return procura_lista(G->g[origem],destino);
}
