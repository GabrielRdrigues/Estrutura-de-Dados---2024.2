// Gabriel Rodrigues Marques Valim e Nuno Martins Do Couto
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct arvore {
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

arvore* LerArvore(FILE* arq) {
    char c;
    int num;
    fscanf(arq,"%c",&c);
    fscanf(arq,"%d",&num);

    if(num==-1) {
        fscanf(arq,"%c",&c);
        return NULL;
    }else {
        arvore* a=(arvore*) malloc(sizeof(arvore));
        a->info=num;
        a->esq=LerArvore(arq);
        a->dir=LerArvore(arq);
        fscanf(arq,"%c",&c);
        return a;
    }
}

void imprimir_pre_ordem(arvore* a){
    if(a!=NULL){
        printf("%d ",a->info);
        imprimir_pre_ordem(a->esq);
        imprimir_pre_ordem(a->dir);
    }
}

void imprimir_em_ordem(arvore* a){
    if(a!=NULL){
        imprimir_em_ordem(a->esq);
        printf("%d ",a->info);
        imprimir_em_ordem(a->dir);
    }
}

void imprimir_pos_ordem(arvore* a){
    if(a!=NULL){
        imprimir_pos_ordem(a->esq);
        imprimir_pos_ordem(a->dir);
        printf("%d ",a->info);
    }
}

// -------------------------------------------------------------------------- //

int existe(arvore* a,int x){ // Tirando proveito da Arvore Binária de Busca ABB
    if(a!=NULL){
        if(x > a->info)
            return existe(a->dir,x);
        if(x < a->info)
            return existe(a->esq,x);
        if(x==a->info)
            return 1;
    }
    return 0;  
}

// ------------------------------------------------------------------------------

/* Imprimir as folhas menores do que um valor x*/

void imprimir_folhas_menores_valor_x(arvore* a,int x){
    if(a!=NULL){
        if(a->info < x){
            if(a->dir==NULL && a->esq==NULL)
                printf("O nó [%d]\n",a->info);
            else{
                imprimir_folhas_menores_valor_x(a->esq,x);
                imprimir_folhas_menores_valor_x(a->dir,x);
            }
        }
        if(a->info >= x)
            imprimir_folhas_menores_valor_x(a->esq,x);
    }
}
// ---------------------------------------------- //

// Destruir a árvore
arvore* free_tree(arvore* raiz){
   if(raiz != NULL){
       raiz->esq=free_tree(raiz->esq);
       raiz->dir=free_tree(raiz->dir);
       free(raiz);
   }
   return NULL;
}
// -------------------------------------------------//

// Imprimir nível de um nó, considerando arvore ABB
int Imprimir_nivel_no_x(arvore* a, int nivel, int x) { // Imprimir nível de um nó N arvore ABB
    if(a!=NULL) {
        if(x > a->info){
            int aux = Imprimir_nivel_no_x(a->dir,nivel+1,x);
            if(aux!=-1)
                return aux;
        }
        if(x < a->info){
            int aux = Imprimir_nivel_no_x(a->esq,nivel+1,x);
            if(aux!=-1)
                return aux;
        }
        if(x==a->info)
            return nivel;
    }
    return -1;
}

/*A função altura é utilizada, nesse programa, para o imprimir em largura*/
int altura(arvore* a){
    if(a==NULL)
        return 0;
    else{
        int he = altura(a->esq);
        int hd = altura(a->dir);
        if(he>hd)
            return he+1;
        else
            return hd+1;
    }
}
// ---------------------------------------------------------------------- //

void imprimir_nivel(arvore *a,int cont,int nivel){
    if(a!=NULL){  // NULL?
        if(cont==nivel)
            printf("%d ",a->info); // Raiz
        else{
            imprimir_nivel(a->esq,cont+1,nivel);
            imprimir_nivel(a->dir,cont+1,nivel);
        }
    }
}

void largura(arvore* a, int cont, const int altura){
    if(cont<=altura){
        imprimir_nivel(a,0,cont);
        puts("");
        largura(a,cont+1,altura);
    }
}

// Rotações da árvore //

//Rotação a esquerda simples
arvore *RotacaoEsqSimples(arvore *p)
{
    arvore *b = p->dir;
    p->dir = b->esq;
    b->esq = p;
    return b;
}

// Rotação a direita simples
arvore *RotacaoDirSimples(arvore *p)
{
    arvore *b = p->esq;
    p->esq = b->dir;
    b->dir = p;
    return b;
}

// Rotação direita dupla
arvore *RotacaoDirDupla(arvore *p)
{
    p->esq = RotacaoEsqSimples(p->esq);
    p = RotacaoDirSimples(p);
    return p;
}

//Rotação a esquerda dupla
arvore *RotacaoEsqDupla(arvore *p)
{
    p->dir = RotacaoDirSimples(p->dir);
    p = RotacaoEsqSimples(p);
    return p;
}

//Rotação a esquerda geral
arvore *RotacaoEsq(arvore *p)
{
    int he = altura(p->esq);
    int hd = altura(p->dir);
    if (fabs(hd - he) > 1){
        arvore *b = p->dir;
        he = altura(b->esq);
        hd = altura(b->dir);
        if (he > hd)
            p = RotacaoEsqDupla(p);
        else
            p = RotacaoEsqSimples(p);
        }
    return p;
}

// Rotação a direita geral

arvore *RotacaoDir(arvore *p)
{
    int he = altura(p->esq);
    int hd = altura(p->dir);
    if (fabs(hd - he) > 1){
        arvore *b = p->esq;
        he = altura(b->esq);
        hd = altura(b->dir);
        if (hd > he)
            p = RotacaoDirDupla(p);
        else
            p = RotacaoDirSimples(p);
                        }
    return p;
}

// ----------------- Inserir elemento ---------- //

arvore* inserir_elemento(arvore* a,int x){
    if(a == NULL) //Momento de inserir
    {
        a = (arvore*)malloc(sizeof(arvore));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
    }
    else
    {
        if (x <= a->info){
            a->esq = inserir_elemento(a->esq,x);
            a = RotacaoDir(a);
                    }
        else{
            a->dir = inserir_elemento(a->dir,x);
            a = RotacaoEsq(a);
            }
    }
    return a;
}
// --------------------------------------------

// ----------------Remover um nó-----------------

arvore* remover_no(arvore* a,int x){
    
    if (a != NULL) {
        if (a->info == x) {
            // Verificar se é folha
            if (a->esq == NULL && a->dir == NULL) {
            free(a);
            return NULL;
            }
            // Verificar se um dos filhos é nulo
            else if (a->esq == NULL || a->dir == NULL) {
            arvore *aux;
            if (a->esq == NULL)
                aux = a->dir;
            else
                aux = a->esq;
            free(a);
            return aux;
            }
            // Nenhum filho nulo
            else {
            arvore *maiorEsq = a->esq;
            while (maiorEsq->dir != NULL)
                maiorEsq = maiorEsq->dir;
            a->info = maiorEsq->info;
            a->esq = remover_no(a->esq, a->info);
            a = RotacaoEsq(a);
            }
        } else if (x < a->info) {
            a->esq = remover_no(a->esq, x);
            a = RotacaoEsq(a);
        } else {
            a->dir = remover_no(a->dir, x);
            a = RotacaoDir(a);
        }
  }
return a;
}

// --------------------------------------------

int main() {

    arvore* a=NULL;
    FILE* arq;
    char nome[20];
    int escolha=0;
    puts("Gabriel Rodrigues Marques Valim e Nuno Martins do Couto");
    while(escolha!=8){
        puts("\n1 - Ler árvore\n2 - Imprimir árvore \n3 - Verificar se X existe\n4 - Imprimir Nível do nó X\n5 - Nós folhas menores que X");
        puts("6- Inserir um nó\n7- Remover um nó\n8- Sair\n");
        scanf("%d",&escolha);
        switch(escolha){
            case 1:
                puts("Digite o nome do arquivo no formato: NomeArquivo.txt");
                scanf("%s",nome);
                arq=fopen(nome,"rt");
                a = LerArvore(arq);
                fclose(arq);
                puts("Arvore lida com sucesso");
                break;
            case 2:
                printf("\tPré ordem pressione 1\n \tEm ordem pressione 2\n \tposordem pressione 3\n \tPorLargura pressione 4\n");
                int escolha2=0;
                scanf("%d",&escolha2);
                if(escolha2==1)
                    imprimir_pre_ordem(a);
                if(escolha2==2)
                    imprimir_em_ordem(a);
                if(escolha2==3)
                    imprimir_pos_ordem(a);
                if(escolha2==4){
                    puts("arvore por largura:");
                    int auxiliar4 = altura(a);
                    largura(a,0,auxiliar4-1);
                }
                break;
            case 3:
                int elemento;
                puts("Digite o elemento,por favor: ");
                scanf("%d",&elemento);
                if(existe(a,elemento)==1)
                    printf("[%d] existe na arvore\n",elemento);
                else
                    printf("[%d] nao existe na arvore\n",elemento);
                break;
            case 4:
                int escolha3;
                puts("Qual número deseja saber o nível:");
                scanf("%d",&escolha3);
                int b = Imprimir_nivel_no_x(a,0,escolha3);
                if(b>=0)
                    printf("O nível é %d\n",b);
                else
                    puts("Não existe na árvore");
                break;
            case 5:
                puts("Digite o valor X");
                int aux5;
                scanf("%d",&aux5);
                printf("Os nós folhas menores que o valor [%d] são: ",aux5);
                imprimir_folhas_menores_valor_x(a,aux5);
                break;
            case 6:
                puts("Qual elemento quer inserir?");
                int aux6;
                scanf("%d",&aux6);
                a = inserir_elemento(a,aux6);
                break;
            case 7:
                puts("Qual elemento quer remover?");
                int aux7;
                scanf("%d",&aux7);
                a = remover_no(a,aux7);
                break;
            case 8:
                printf("Saiu, obrigado por usar nosso programa\n");
                break;
            default:
                puts("Opção inválida, digite outra\n");
                break;
        }
    }

    a=free_tree(a);
    return 0;
}
