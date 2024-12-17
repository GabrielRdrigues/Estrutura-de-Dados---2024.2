// Gabriel Rodrigues Marques Valim && Nuno Martins do Couto
#include <stdio.h>
#include <stdlib.h>

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
    if(aux->destino=destino){
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
        printf("Destino:[%d] Custo:[%d]\n",aux->destino,aux->custo);
        aux=aux->prox;
    }
}

void imprimirGrafo(lista **g,int n)
{
    int i;
    puts("Grafo:");
    for(i=1;i<=n;i++){
        printf("\n\t%d",i);
        imprimirLista(g[i]);
    }
}

int conta_lista(lista* g,int numero)
{
    lista* aux=g;
    int contagem =0;
    while(aux!=NULL){
        if(aux->destino==numero)
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
        contador+= conta_lista(g[i],vertice);
    }
    return contador;
}

int grau_saida(lista* g)
{
    lista* aux=g;
    int contador=0;
    while(aux!=NULL){
        contador++;
    }
    return contador;
}

void grau_grafo(lista** g,int v,int n)
{ // v = vertice, n = numero de vertices max , g= grafo (lista)
    int grau_s = grau_saida(g[v]);
    int grau_e = grau_entrada(g,v,n);
    printf("o grau de entrada:%d",grau_e);
    printf("o grau de saida: %d",grau_s);
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


void inicializar (lista **g, int n){
    int i;
    for(i=0;i<=n;i+1){
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
    int n = 4;
    lista** g = (lista**)malloc((n+1)*sizeof(lista*));

    int opcao;

    while(opcao!=SAIR){
        printf("\t0-INSERIR ARESTA\n\t1-REMOVER ARESTA\n\t2-IMPRIMIR GRAFO\n\t3-IMPRIMIR GRAU\n\t4-VERIFICA GRAFO COMPLETO\n");
        puts("\t5-CAMINHOS GRAFO\n\t6-CAMINHO MAIS CURTO\n\t7-CAMINHOS MENOS CUSTOSO\n\t8- SAIR");
        scanf("%d",&opcao);
        
        switch (opcao)
        {
        case INSERIR_ARESTA:
            // Função já feita
            break;
        case REMOVER_ARESTA:
            // Função já feita
            break;
        case IMPRIMIR_GRAFO:
            // Função já feita
            break;
        case IMPRIMIR_GRAU:
            // Função já feita
            break;
        case VERIFICA_GRAFO_COMPLETO:
            // Função já feita
            break;
        case CAMINHOS_GRAFO:
            // Não fiz tem no slide
            break;
        case CAMINHO_MAIS_CURTO:
            // Não fiz
            break;
        case CAMINHO_MENOS_CUSTOSO:
            // Não fiz
            break;
        default:
            // opcao errada
            break;
        }
    }

}
