#include "grafoTAD.h"
#include <stdio.h>


int main(){
    Grafo G;
    G = Inicializar();
    char c = 'c';
    int d = 12;
    Inserir_Aresta(G,2,&c,sizeof(c),1);
    Inserir_Aresta(G,3,&d,sizeof(c),1);
    Imprimir_Grafo(G);
    
}