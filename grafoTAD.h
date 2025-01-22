typedef struct grafo* Grafo;


Grafo Inicializar(void);
Grafo Destruir (Grafo G);
void Inserir_Aresta(Grafo G,int chave,void* objeto,int SizeObj,int origem);
void Remover_Aresta(Grafo G,void* objeto,int sizeObj,int origem,int destino);
void Grau_Vertice(Grafo G,int vertice);
void Imprimir_Grafo(Grafo G);
void* Search(Grafo G,int chave,int origem);