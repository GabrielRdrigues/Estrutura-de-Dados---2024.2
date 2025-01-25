
#include "grafoTAD.h"
#include <stdio.h>


int main(){
    Grafo G;
    G = Inicializar();
    char c = 'c';
    int d = 12;
    Inserir_Aresta(G,2,&c,sizeof(c),1);
    Inserir_Aresta(G,3,&d,sizeof(c),1);
    printf("\n\n%d\n\n",Grau_Vertice(G,1));
    Imprimir_Grafo(G);

    printf("%c", *(char*)Search(G, 2,1));

}
