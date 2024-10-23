#ifndef SUPORTE_H
#define SUPORTE_H

#include "cliente.h"
#include "estoque.h"

// Definição do tamanho máximo da heap de pedidos
#define TAMANHO_HEAP 100

// Estrutura do pedido de suporte
typedef struct {
    Cliente* cliente;     // Referência ao cliente que fez o pedido
    char descricao[100];  // Descrição do pedido
    int prioridade;       // Menor valor = maior prioridade
} PedidoSuporte;

// Estrutura da heap mínima para armazenar pedidos
typedef struct {
    PedidoSuporte pedidos[TAMANHO_HEAP];  // Array de pedidos
    int tamanho;                          // Tamanho atual da heap
} Heap;

// Funções da heap
void inicializarHeap(Heap* heap);
void inserirPedido(Heap* heap, Cliente* cliente, const char* descricao, int prioridade);
PedidoSuporte removerPedido(Heap* heap);
void listarPedidos(Heap* heap);

// Funções adicionais
void realizarCompra(Heap* heap, int idItem, int quantidade, const char* nomeCliente);

// Funções de persistência
void salvarPedidos(Heap* heap, const char* arquivo);
void carregarPedidos(Heap* heap, const char* arquivo);

// Menu de suporte
void menuSuporte(Heap* heap);

#endif  // SUPORTE_H