typedef struct fila* Fila; // Fila

int inserir(Fila F,int x); // Insere um elemento na fila. Retorna 1 se deu tudo certo, 0 se falhou.

int remover(Fila F); // Remove um elemento da fila. Retorna 1 se removeu com sucesso, 0 se falhou.

void imprimir(Fila F); // Imprime a fila.

Fila Inicializar(); // Inicializar (Construtor)

Fila Destruir(Fila F); // Destruir (~Construtor)




