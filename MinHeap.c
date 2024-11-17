#include <stdio.h>
#include <math.h>

int totalElementos=0;
/*Funções auxiliares*/
int indiceFilhoEsq(int x){
    int indice = (2*x)+1;
    if(indice >= totalElementos || x>= totalElementos)
        return -1;
    return indice;
}

int indiceFilhoDir(int x){
    int indice = (2*x)+2;
    if(indice >= totalElementos || x>= totalElementos)
        return -1;
    return indice;
}

int indicePai(int x){
    int indice = (int)floor((x-1)/2);
    if(x >= totalElementos || x<= 0)
        return -1;
    return indice;
}
/*--------------------------------*/
/*Inserção de Elemento na minHeap*/
void AjustarSubindo(int* heap,int pos){
    if(pos!=-1){
        int pai = indicePai(pos);
        if(pai!=-1){
            if(heap[pos]<heap[pai]){
                int aux=heap[pos];
                heap[pos]=heap[pai];
                heap[pai]=aux;
                AjustarSubindo(heap,pai);
            }
        }
    }
}

void inserir(int* heap,int x){
    heap[totalElementos]=x;
    totalElementos++;
    AjustarSubindo(heap,totalElementos-1);
}
/*-------------------------------------------*/

void AjustarDescendo(int* heap,int pos){
    if(pos!=-1 && indiceFilhoEsq(pos)!=-1){
        int indiceMenorFilho = indiceFilhoEsq(pos);
        if(indiceFilhoDir(pos)!=-1 && 
        heap[indiceFilhoDir(pos)]<heap[indiceMenorFilho])
            indiceMenorFilho=indiceFilhoDir(pos);
        if(heap[indiceMenorFilho]<heap[pos]){
            int aux=heap[pos];
            heap[pos]=heap[indiceMenorFilho];
            heap[indiceMenorFilho]=aux;
            AjustarDescendo(heap,indiceMenorFilho);
        }
    }
}

int remover(int* heap){
    if(totalElementos==0)
        return -1;
    int retorno = heap[0];
    heap[0]= heap[totalElementos-1];
    totalElementos--;
    AjustarDescendo(heap,0);
    return retorno;
}

void imprimirHeap(int* heap){
    for(int i =0;i<totalElementos;i++)
        printf("[%d] ",heap[i]);
}

int main(){
    int heap[50];
    int escolha,elemento;
    while(escolha!=-1){
        puts("1-Insere\n2-Remove\n3-Imprime\n4-Sair");
        scanf("%d",&escolha);
        switch (escolha)
        {
        case 1:
            puts("Qual elemento quer inserir:");
            scanf("%d",&elemento);
            inserir(heap,elemento);
            break;
        case 2:
            puts("Remoção do elemento:");
            printf("%d\n",remover(heap));
            break;
        case 3:
            imprimirHeap(heap);
            break;
        case 4:
            escolha=-1;
            break;
        default:
            puts("Número errado");
            break;
        }
    // FIM WHILE
    }


}
