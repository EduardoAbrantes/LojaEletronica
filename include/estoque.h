#include "../src/funções.c"


/**
 * @struct cliente
 * @brief Estrutura para representar um cliente.
 */
typedef struct Item Item;

/**
 * @struct cliente
 * @brief Estrutura para representar um cliente.
 */
typedef struct NodoAVL NodoAVL;

NodoAVL* criarNodoAVL(Item item);
NodoAVL* rotacaoDireita(NodoAVL* y);
NodoAVL* rotacaoEsquerda(NodoAVL* x);
int obterBalanceamento(NodoAVL* nodo);
NodoAVL* inserir(NodoAVL* nodo, Item item);
NodoAVL* buscar(NodoAVL* nodo, int id);
void imprimirEmOrdem(NodoAVL* nodo);
NodoAVL* menorValorNodo(NodoAVL* nodo);
NodoAVL* remover(NodoAVL* raiz, int id);
void carregarItensArquivo(const char* nomeArquivo, NodoAVL** raiz);
void salvarItensArquivo(FILE* arquivo, NodoAVL* nodo);
void adicionarItem(NodoAVL** raiz);
void buscarItem(NodoAVL* raiz);
void listarItens(NodoAVL* raiz);
void atualizarPreco(NodoAVL* raiz);
void removerItem(NodoAVL** raiz);