#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

enum escolha
{
    Inserir, // Por default começa no 0, logo Inserir = 0 e assim por diante
    Remover,    
    Imprimir,
    Sair
};

int main(){

    int escolha = 1; // Inicializando com qualquer coisa diferente de Sair
    Fila F=Inicializar();
    
    while(escolha!=Sair)
    {
        puts("\n\t 0 - Inserir\n\t 1 - Remover\n\t 2 - Imprimir\n\t 3 - Sair\n\t");
        scanf("%d",&escolha);
        switch (escolha)
        {
        case Inserir:
            int elemento;
            printf("digite o elemento a ser inserido:");
            scanf("%d",&elemento);
            inserir(F,elemento);
            break;
        case Remover:
            remover(F);
            break;
        case Imprimir:
            imprimir(F);
            break;
        case Sair:
            F = Destruir(F);
            break;
        default:
            puts("opcao errada");
        }
    }
}