#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

#define N 100

struct fila
{
    int vet[N];
    int proximo;
};

Fila Inicializar()
{
    Fila F = (Fila)malloc(sizeof(Fila));
    F->proximo=0;
    return F;
}

Fila Destruir(Fila F)
{
    free(F);
    return NULL;
}

int inserir(Fila F,int x )
{
    if(F->proximo<N)
    {
        F->vet[F->proximo]= x;
        (F->proximo)++;
        return 1;
    }
    puts("Fila cheia");
    return 0;
}

int remover(Fila F)
{
    if(F->proximo!=0)
    {
        printf("o elemento removido eh :[%d]",F->vet[0]);
        for(int i=0;i<(F->proximo)-1;i++)
        {
            F->vet[i]=F->vet[i+1];
        }
        F->proximo--;
        return 1;
    }
    printf("Fila vazia\n");
    return 0;
}

void imprimir(Fila F)
{
    for(int i=0;i<F->proximo;i++)
        printf("%d ",F->vet[i]);
}