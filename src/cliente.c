#include "../include/cliente.h"

// Definição da struct Cliente
struct cliente {
    int id;                 // ID único do cliente
    char nome[100];         // Nome completo do cliente
    struct Cliente* prox;   // Ponteiro para o próximo cliente (lista encadeada)
};