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


NodoAVL* inserir(NodoAVL* nodo, Item item) {
    if (nodo == NULL)
        return criarNodoAVL(item);

    if (item.id < nodo->item.id)
        nodo->esquerda = inserir(nodo->esquerda, item);
    else if (item.id > nodo->item.id)
        nodo->direita = inserir(nodo->direita, item);
    else
        return nodo; 

    nodo->altura = 1 + max(altura(nodo->esquerda), altura(nodo->direita));

    int balanceamento = obterBalanceamento(nodo);

    if (balanceamento > 1 && item.id < nodo->esquerda->item.id)
        return rotacaoDireita(nodo);

    if (balanceamento < -1 && item.id > nodo->direita->item.id)
        return rotacaoEsquerda(nodo);

    if (balanceamento > 1 && item.id > nodo->esquerda->item.id) {
        nodo->esquerda = rotacaoEsquerda(nodo->esquerda);
        return rotacaoDireita(nodo);
    }

    if (balanceamento < -1 && item.id < nodo->direita->item.id) {
        nodo->direita = rotacaoDireita(nodo->direita);
        return rotacaoEsquerda(nodo);
    }

    return nodo;
}


NodoAVL* buscar(NodoAVL* nodo, int id) {
    if (nodo == NULL || nodo->item.id == id)
        return nodo;

    if (id < nodo->item.id)
        return buscar(nodo->esquerda, id);

    return buscar(nodo->direita, id);
}


void imprimirEmOrdem(NodoAVL* nodo) {
    if (nodo != NULL) {
        imprimirEmOrdem(nodo->esquerda);
        printf("ID: %d, Nome: %s, Preço: %.2f\n", nodo->item.id, nodo->item.nome, nodo->item.preco);
        imprimirEmOrdem(nodo->direita);
    }
}


NodoAVL* menorValorNodo(NodoAVL* nodo) {
    NodoAVL* atual = nodo;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

NodoAVL* remover(NodoAVL* raiz, int id) {
    if (raiz == NULL)
        return raiz;

    if (id < raiz->item.id)
        raiz->esquerda = remover(raiz->esquerda, id);
    else if (id > raiz->item.id)
        raiz->direita = remover(raiz->direita, id);
    else {
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            NodoAVL* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;
            free(temp);
        } else {
            NodoAVL* temp = menorValorNodo(raiz->direita);
            raiz->item = temp->item;
            raiz->direita = remover(raiz->direita, temp->item.id);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    int balanceamento = obterBalanceamento(raiz);

    if (balanceamento > 1 && obterBalanceamento(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);

    if (balanceamento > 1 && obterBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (balanceamento < -1 && obterBalanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);

    if (balanceamento < -1 && obterBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}