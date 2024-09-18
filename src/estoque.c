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
