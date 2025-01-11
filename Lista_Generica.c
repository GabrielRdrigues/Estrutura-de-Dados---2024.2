#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct pessoa {
    int tipo;
    void* item;
}Pessoa;

typedef struct professor {
    int matricula;
    char nome[20];
    float salario;
}Professor;

typedef struct aluno {
    int matricula;
    char nome[20];
    char curso[20];
    int ano;
}Aluno;

void inicializar(Pessoa* p) {
    for (int i=0; i<100; i++) {
        p[i].tipo=0;
        p[i].item=NULL;
    }
}

void inserir(Pessoa* p, void* item, int tipo, int pos) {
    p[pos].tipo = tipo;
    p[pos].item = item;
}

void ajustaLista(Pessoa* p, int n, int pos) {
    for (int i=n; i<pos; i++) {
        p[i] = p[i+1];
    }
}

void remover(Pessoa* p,int pos, int matricula) {
    for (int i=0; i<pos; i++) {
        if (p[i].tipo==1) {
            Professor* f = (Professor*)p[i].item;
            if (f->matricula == matricula) {
                p[i].tipo = 0;
                free(p[i].item);
                pos--;
                ajustaLista(p, i, pos);
                puts("Pessoa removida com sucesso!");
                return;
            }
        } else if(p[i].tipo==2) {
            Aluno* a = (Aluno*)p[i].item;
            if (a->matricula == matricula) {
                p[i].tipo = 0;
                free(p[i].item);
                pos--;
                ajustaLista(p, i, pos);
                puts("Pessoa removida com sucesso!");
                return;
            }
        }
    }
    puts("Não existe professor ou aluno com essa matrícula");
}

void imprimeProfessor(Professor* f) {
    puts("Imprimindo dados do Professor:");
    printf("\n\t Matricula: %d\n\t Nome: %s\n\t Salario: %.2f\n\t", f->matricula, f->nome, f->salario);
}

void imprimeAluno(Aluno* a) {
    puts("Imprimindo dados do Aluno:");
    printf("\n\t Matricula: %d\n\t Nome: %s\n\t Curso: %s\n\t Ano: %d\n\t", a->matricula, a->nome, a->curso, a->ano);
}

void buscar(Pessoa* p, int pos, int matricula) {
    for (int i=0; i<pos; i++) {
        if (p[i].tipo==1) {
            Professor* f = (Professor*)p[i].item;
            if (f->matricula == matricula) {
                imprimeProfessor(f);
                return;
            }
        } else if(p[i].tipo==2) {
            Aluno* a = (Aluno*)p[i].item;
            if (a->matricula == matricula) {
                imprimeAluno(a);
                return;
            }
        }
    }
    puts("Não existe professor ou aluno com essa matrícula");
}

int contaAlunos(Pessoa* p,int pos, const char curso[20]) {
    int cont=0;
    for (int i=0; i<pos; i++) {
        if(p[i].tipo==2) {
            Aluno* a = (Aluno*)p[i].item;
            if (strcmp(a->nome, curso)) {
                cont++;
            }
        }
    }
    return cont;
}


enum escolha {
    Inserir,
    Remover,
    Buscar,
    Contar,
    Imprimir,
    Sair
};

int main(void) {
    Pessoa p[100];
    inicializar(p);
    int pos=0;
    int matricula;
    int tipo=0;
    char curso[20];

    int escolha=0;

    while (escolha!=Sair) {
        puts("\n\t 0 - Inserir\n\t 1 - Remover\n\t 2 - Buscar\n\t 3 - Contar Alunos por Curso\n\t 4 - Imprimir Professores de Maior Salario\n\t 5 - Sair\n\t");
        scanf(" %d",&escolha);
        switch (escolha)
        {
            case Inserir:
                puts("Por favor, Informe o tipo:\n\t 1 - Professor\n\t 2 - Aluno\n\t");
                scanf(" %d", &tipo);
                if (tipo == 1) {
                    Professor* f = (Professor*)malloc(sizeof(Professor));
                    puts("Informe a matricula (ex.: 223060063):");
                    scanf(" %d", &f->matricula);

                    puts("Informe o nome:");
                    scanf(" %20[^\n]", f->nome);

                    puts("Informe o salario:");
                    scanf(" %f", &f->salario);

                    inserir(p, f, tipo, pos);
                    pos++;
                    puts("Professor adicionado com sucesso");
                } else if (tipo == 2){
                    Aluno* a = (Aluno*)malloc(sizeof(Aluno));
                    puts("Informe a matricula (ex.: 223060063): ");
                    scanf(" %d", &a->matricula);

                    puts("Informe o nome: ");
                    scanf(" %20[^\n]", a->nome);

                    puts("Informe o curso: ");
                    scanf(" %20[^\n]", a->curso);

                    puts("Informe o Ano de Ingresso: ");
                    scanf(" %d", &a->ano);

                    inserir(p, a, tipo, pos);
                    pos++;
                    puts("Aluno adicionado com sucesso");
                }

                break;
            case Remover:
                puts("Informe a matricula de quem deseja remover: ");
                scanf(" %d", &matricula);
                remover(p, pos, matricula);
                pos--;

                break;
            case Buscar:
                puts("Informe a matricula de quem deseja buscar: ");
                scanf(" %d", &matricula);
                buscar(p, pos, matricula);

                break;
            case Contar:
                puts("Informe o curso: ");
                scanf(" %20[^\n]", curso);
                printf("Existem %d alunos no curso %s", contaAlunos(p, pos, curso), curso);

                break;
            case Imprimir:

                break;
            case Sair:

                break;
            default:
                puts("opcao errada");
        }
    }
}

