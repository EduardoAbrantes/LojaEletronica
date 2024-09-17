#include "../include/cliente.h"

// Definição da struct Cliente
typedef struct Cliente {
    int id;                 // ID único do cliente
    char nome[100];         // Nome completo do cliente
    int solicitacoesSuporte; // Número de solicitações de suporte técnico realizadas
    struct Cliente* prox;   // Ponteiro para o próximo cliente (lista encadeada)
} Cliente;