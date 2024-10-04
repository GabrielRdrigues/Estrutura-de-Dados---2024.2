#include <stdio.h>
#include <stdlib.h>

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
        printf("%d\n",a->info);
        imprimir_pre_ordem(a->esq);
        imprimir_pre_ordem(a->dir);
    }
}

void imprimir_em_ordem(arvore* a){
    if(a!=NULL){
        imprimir_em_ordem(a->esq);
        printf("%d\n",a->info);
        imprimir_em_ordem(a->dir);
    }
}

void imprimir_pos_ordem(arvore* a){
    if(a!=NULL){
        imprimir_pos_ordem(a->esq);
        imprimir_pos_ordem(a->dir);
        printf("%d\n",a->info);
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

void free_tree(arvore* root){
   if(root != NULL){
       free_tree(root->esq);
       free_tree(root->dir);
       free(root);
   }
}

int main() {

    arvore* a;
    FILE* arq;
    int escolha=0;

    while(escolha!=6){
        scanf("%d",&escolha);
        switch(escolha){
            case 1:
                char nome[20];
                scanf("%s",nome);
                arq=fopen(nome,"r");
                a = LerArvore(arq);
                fclose(arq);
                puts("Arvore lida com sucesso");
                break;
            case 2:
                printf("\tPré ordem pressione 1\n \tEm ordem pressione 2\n \tposordem pressione 3\n");
                int escolha2=0;
                scanf("%d",&escolha2);
                if(escolha2==1)
                    imprimir_pre_ordem(a);
                if(escolha2==2)
                    imprimir_em_ordem(a);
                if(escolha2==3)
                    imprimir_pos_ordem(a);
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
                printf("o numero de elementos na arvore eh [%d]\n",aux);
                break;
            case 5:
                nos_folhas(a);
                break;
            case 6:
                printf("Saiu, obrigado por usar nosso programa\n");
                break;
            default:
                puts("Opção inválida, digite outra\n");
                break;
        }
    }

    free_tree(a);
    return 0;
}
