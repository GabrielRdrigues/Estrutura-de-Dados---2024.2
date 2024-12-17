// Gabriel Rodrigues Marques Valim && Nuno Martins do Couto
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define N 4             //Máximo de vértices

//Variáveis globais para as funções 6 e 7

int menor_caminho[N+1];
int tamanho_menor_caminho = N+1;
int menor_custo = 99999;


typedef struct lista{
    int destino;
    int custo;
    struct lista *prox;
}lista;


lista* inserirLista(lista *l,int destino,int custo)
{
    lista* no = (lista*)malloc(sizeof(lista));
    no->destino=destino;
    no->custo=custo;
    no->prox=l;
    return no;
}

lista* removerlista(lista* l,int destino)
{
    lista* aux=l;
    if(aux==NULL)
        return NULL;
    if(aux->destino==destino){
        lista* new_head= aux->prox;
        free(aux);
        return new_head;
    }
    while(aux->prox!=NULL && aux->prox->destino!=destino){
        aux=aux->prox;
    }
    if(aux->prox!=NULL){
        lista* auxiliar = aux->prox->prox;
        free(aux->prox);
        aux->prox = auxiliar;
    }
    return l;
}

void InserirAresta(lista** g,int origem,int destino,int custo)
{
    g[origem]= inserirLista(g[origem],destino,custo);
}

void RemoverAresta(lista** g,int origem,int destino)
{
    g[origem]=removerlista(g[origem],destino);
}

void imprimirLista(lista* l)
{
    lista* aux = l;
    while(aux!=NULL){
        printf("Destino:[%d] Custo:[%d]   ",aux->destino,aux->custo);
        aux=aux->prox;
    }
}

void imprimirGrafo(lista **g,int n)
{
    int i;
    puts("Grafo:");
    for(i=1;i<=n;i++){
        printf("\n\tOrigem: [%d] ",i);
        imprimirLista(g[i]);
    }
    puts("");
}

int conta_lista(lista* g,int vertice)
{
    lista* aux=g;
    int contagem =0;
    while(aux!=NULL){
        if(aux->destino==vertice)
            contagem++;
        aux=aux->prox;
    }
    return contagem;
}


int grau_entrada(lista** g,int vertice,int n)
{
    int i;
    int contador=0;
    for(i=1;i<=n;i++){
        contador += conta_lista(g[i],vertice);
    }
    return contador;
}

int grau_saida(lista* g)
{
    lista* aux=g;
    int contador=0;
    while(aux!=NULL){
        contador++;
        aux = aux->prox;
    }
    return contador;
}

void grau_grafo(lista** g,int v,int n)
{ // v = vertice, n = numero de vertices max , g= grafo (lista)
    int grau_s = grau_saida(g[v]);
    int grau_e = grau_entrada(g,v,n);
    printf("O grau de entrada:%d\n",grau_e);
    printf("O grau de saida: %d\n",grau_s);
}

void grafo_completo_verifica(lista** g,int n)
{ // n = numero de vertices max
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j && (conta_lista(g[i],j)==0)){
                puts("não é completo");
                return;
            }

        }
    }
    puts("é completo");
}

int existe(int *vet,int valor,int n)
{
    int i;
    for(i=0;i<n;i++)
        if(vet[i]==valor)
            return 1;
    return 0;
}


void caminhos(lista** g,int b,int* vet, int pos) // b = destino
{
    if(vet[pos-1]==b)
    {
        int i;
        puts("");
        for(i=0;i<pos;i++)
            printf("%d ",vet[i]);
    }
    else
    {
        lista* p =g[vet[pos-1]];
        while(p!=NULL)
        {
            if(!existe(vet,p->destino,pos))
            {
                vet[pos]=p->destino;
                caminhos(g,b,vet,pos+1);
            }
            p=p->prox;
        }
    }
}

int CalcularCusto(lista** g, int* vet, int pos){
    int custo=0;
    for (int i=0; i<pos-1; i++) {
        int origem = vet[i];
        int destino = vet[i+1];

        lista* l = g[origem];
        while(l!=NULL) {
            if (l->destino == destino) {
                custo += l->custo;
                break;
            }
            l = l->prox;
        }
    }
    return custo;
}

int existe_custo(int* vet, int pos, int destino) {
    for (int i=0; i<pos; i++) {
        if (vet[i]==destino) {
            return 1;
        }
    }
    return 0;
}

void imprimirCaminhos(lista** g, int *vet, int pos, int destino, int modo) {
    if (vet[pos-1]==destino) {
        if (modo==0) {
            if (pos < tamanho_menor_caminho) {
                tamanho_menor_caminho = pos;
                for(int i=0; i<pos;i++) {
                    menor_caminho[i] = vet[i];
                }
            }
        } else {
            int custo = CalcularCusto(g, vet, pos);
            if (custo < menor_custo) {
                tamanho_menor_caminho = pos;
                menor_custo = custo;
                for (int i=0; i<pos; i++) {
                    menor_caminho[i] = vet[i];
                }
            }
        }
    }else {
        lista* l = g[vet[pos-1]];
        while (l!=NULL) {
            if(!existe_custo(vet, pos, l->destino)) {
                vet[pos] = l->destino;
                imprimirCaminhos(g, vet, pos+1, destino, modo);
            }
            l = l->prox;
        }
    }
}


void inicializar (lista **g, int n){
    int i;
    for(i=0;i<=n;i++){
        g[i]=NULL;
    }
}


enum opcao{
    INSERIR_ARESTA,
    REMOVER_ARESTA, 
    IMPRIMIR_GRAFO,
    IMPRIMIR_GRAU,
    VERIFICA_GRAFO_COMPLETO,
    CAMINHOS_GRAFO,
    CAMINHO_MAIS_CURTO,
    CAMINHO_MENOS_CUSTOSO,
    SAIR
};


void main(){
    setlocale(LC_ALL, "portuguese");

    int n = N;

    lista** g = (lista**)malloc((n+1)*sizeof(lista*));

    int origem;
    int destino;
    int custo;

    int vet1[N+1];

    int opcao;


    inicializar(g, n);

    while(opcao!=SAIR){
        printf("\t0-INSERIR ARESTA\n\t1-REMOVER ARESTA\n\t2-IMPRIMIR GRAFO\n\t3-IMPRIMIR GRAU\n\t4-VERIFICA GRAFO COMPLETO\n");
        puts("\t5-CAMINHOS GRAFO\n\t6-CAMINHO MAIS CURTO\n\t7-CAMINHOS MENOS CUSTOSO\n\t8- SAIR");
        scanf("%d",&opcao);
        
        switch (opcao)
        {
        case INSERIR_ARESTA:
            printf("\nInforme o vértice de origem: ");
            scanf("%d", &origem);
            printf("\nInforme o vértice de destino: ");
            scanf("%d", &destino);
            printf("\nInforme o custo da aresta: ");
            scanf("%d", &custo);
            InserirAresta(g, origem, destino, custo);
            puts("Aresta adicionada com sucesso!\n");
            break;
        case REMOVER_ARESTA:
            printf("Informe a origem da aresta que deseja remover: ");
            scanf("%d", &origem);
            puts("Informe o destino da aresta que deseja remover: ");
            scanf("%d", &destino);
            RemoverAresta(g, origem, destino);
            break;

        case IMPRIMIR_GRAFO:
            imprimirGrafo(g, n);
            break;

        case IMPRIMIR_GRAU:
            int vertice;
            printf("Informe o vétice que deseja saber os graus: ");
            scanf("%d", &vertice);
            grau_grafo(g, vertice, n);
            break;

        case VERIFICA_GRAFO_COMPLETO:
            grafo_completo_verifica(g, n);
            break;

        case CAMINHOS_GRAFO:
            printf("Informe a origem: ");
            scanf("%d", &origem);
            printf("Informe o destino: ");
            scanf("%d", &destino);
            int* vet= (int*)malloc(n*sizeof(int));
            vet[0] = origem;
            caminhos(g, destino, vet, 1);
            puts("");
            break;

        case CAMINHO_MAIS_CURTO:
            tamanho_menor_caminho = N+1;
            printf("Informe a origem: ");
            scanf("%d", &origem);
            printf("Informe o destino: ");
            scanf("%d", &destino);
            vet1[0] = origem;

            imprimirCaminhos(g, vet1, 1, destino, 0);

            for (int i=0; i<tamanho_menor_caminho; i++) {
                printf("%d ", menor_caminho[i]);
            }
            puts("");
            break;

        case CAMINHO_MENOS_CUSTOSO:
            tamanho_menor_caminho = n+1;
            menor_custo = 99999;
            printf("Informe a origem: ");
            scanf("%d", &origem);
            printf("Informe o destino: ");
            scanf("%d", &destino);
            vet1[0] = origem;

            imprimirCaminhos(g, vet1, 1, destino, 1);

            for (int i=0; i<tamanho_menor_caminho; i++) {
                printf("%d ", menor_caminho[i]);
            }
            printf("\nCusto: %d", menor_custo);
            puts("");
            break;

        default:
            // opcao errada
            break;
        }
    }

}
