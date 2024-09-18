#include "../include/estoque.h"

struct Item {
    int id;             
    char nome[100];     
    float preco;        
};

struct NodoAVL {
    Item item;                 
    struct NodoAVL* esquerda;  
    struct NodoAVL* direita;   
    int altura;                
};

int altura(NodoAVL* nodo) {
    if (nodo == NULL)
        return 0;
    return nodo->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

NodoAVL* criarNodoAVL(Item item) {
    NodoAVL* nodo = (NodoAVL*)malloc(sizeof(NodoAVL));
    nodo->item = item;
    nodo->esquerda = nodo->direita = NULL;
    nodo->altura = 1;
    return nodo;
}

NodoAVL* rotacaoDireita(NodoAVL* y) {
    NodoAVL* x = y->esquerda;
    NodoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

NodoAVL* rotacaoEsquerda(NodoAVL* x) {
    NodoAVL* y = x->direita;
    NodoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

int obterBalanceamento(NodoAVL* nodo) {
    if (nodo == NULL)
        return 0;
    return altura(nodo->esquerda) - altura(nodo->direita);
}
