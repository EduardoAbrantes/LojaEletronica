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