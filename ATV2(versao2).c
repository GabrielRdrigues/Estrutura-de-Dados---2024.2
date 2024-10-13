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

int existe(arvore* a,int x){
    if(a==NULL)
        return 0;
    else if(a->info==x)
        return 1;
    else{
        int ret=existe(a->esq,x);
        if(ret==1)
            return 1;
        return existe(a->dir,x);
    }
}

int contar_numero_elementos(arvore* a){
    if(a!=NULL){
        return 1 + contar_numero_elementos(a->esq) + contar_numero_elementos(a->dir);
    }
    return 0;
}

void nos_folhas(arvore* a){
    if(a!=NULL){
        if(a->dir==NULL && a->esq==NULL)
            printf("no [%d] é folha\n",a->info);
        else{
            nos_folhas(a->esq);
            nos_folhas(a->dir);
        }
    }

}

arvore* free_tree(arvore* raiz){
   if(raiz != NULL){
       raiz->esq=free_tree(raiz->esq);
       raiz->dir=free_tree(raiz->dir);
       free(raiz);
   }
   return NULL;
}

int Imprimir_nivel_no_x(arvore* a, int nivel, int x) {
    if(a!=NULL) {
        if(a->info != x) {
            int aux = Imprimir_nivel_no_x(a->esq,nivel+1,x);
            if(aux!=-1)
                return aux;
            aux = Imprimir_nivel_no_x(a->dir,nivel+1,x);
            if(aux!=-1)
                return aux;
            return -1;
        }else {
            return nivel;
        }
    }
    return -1;
}

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

int balanceamento(arvore* a){
    if(a==NULL)
        return 0;
    else{
        int aux1= altura(a->esq); 
        int aux2= altura(a->dir); 
        if(aux1 - aux2 > 1 || aux1 - aux2 <-1)
            return -1;
        if(balanceamento(a->esq) == -1 || balanceamento(a->dir) == -1) 
            return -1;
    }
}

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
        largura(a,cont+1,altura);
    }
}

int arvore_cheia(arvore* a,int cont,int n){
    if(a==NULL)
        return 0;
    else{
        if(cont==n)
            return 1;
        else
            return arvore_cheia(a->esq,cont+1,n) + arvore_cheia(a->dir,cont+1,n);
    }
}

int main() {

    arvore* a=NULL;
    FILE* arq;
    char nome[20];
    int escolha=0;
    puts("Gabriel Rodrigues Marques Valim E Nuno Martins Do Couto");
    while(escolha!=9){
        puts("\n1 - Ler arvore\n2 - Imprimir arvore \n3 - Busca elemento\n4 - Contagem de nós\n5 - Nós folhas");
        puts("6- Verificar balanceamento\n7- Verificar se é cheia\n8- Imprimir o nível de um nó X\n9- Sair");
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
                printf("\tPré ordem pressione 1\n \tEm ordem pressione 2\n \tposordem pressione 3\nPorLargura pressione 4\n");
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
                int aux = contar_numero_elementos(a);
                printf("o numero de nós na arvore eh [%d]\n",aux);
                break;
            case 5:
                nos_folhas(a);
                break;
            case 6:
                int auxiliar = balanceamento(a);
                if(auxiliar!=-1){
                    printf("balanceada\n");
                }
                else{
                    printf("nao balanceada");
                }
                break;
            case 7:
                int h = altura(a);
                if(arvore_cheia(a,0,h-1)== pow(2,h-1))
                    puts("é cheia");
                else
                    puts("nao eh cheia");
               // Verificar se a árvore é cheia
               break;
            case 8:
                int escolha3;
                puts("Qual número quer saber o nível:");
                scanf("%d",&escolha3);
                int b = Imprimir_nivel_no_x(a,0,escolha3);
                if(b>=0)
                    printf("o nível eh %d\n",b);
                else
                    puts("nao existe na arvore");
                break;
            case 9:
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
