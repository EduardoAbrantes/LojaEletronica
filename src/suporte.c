#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cliente.c"
#include "estoque.c"

#define TAMANHO_HEAP 100

typedef struct {
    Cliente* cliente;  // Referência ao cliente que fez o pedido
    char descricao[100];
    int prioridade;  // Menor valor = maior prioridade
} PedidoSuporte;

typedef struct {
    PedidoSuporte pedidos[TAMANHO_HEAP];
    int tamanho;
} Heap;

// Inicializa a heap vazia
void inicializarHeap(Heap* heap) {
    heap->tamanho = 0;
}

// Função auxiliar para trocar dois pedidos na heap
void trocar(PedidoSuporte* a, PedidoSuporte* b) {
    PedidoSuporte temp = *a;
    *a = *b;
    *b = temp;
}

// Função para subir um pedido na heap
void subir(Heap* heap, int index) {
    while (index > 0) {
        int pai = (index - 1) / 2;
        if (heap->pedidos[index].prioridade >= heap->pedidos[pai].prioridade)
            break;
        trocar(&heap->pedidos[index], &heap->pedidos[pai]);
        index = pai;
    }
}

// Função para descer um pedido na heap
void descer(Heap* heap, int index) {
    int menor = index;
    int esquerda = 2 * index + 1;
    int direita = 2 * index + 2;

    if (esquerda < heap->tamanho &&
        heap->pedidos[esquerda].prioridade < heap->pedidos[menor].prioridade) {
        menor = esquerda;
    }
    if (direita < heap->tamanho &&
        heap->pedidos[direita].prioridade < heap->pedidos[menor].prioridade) {
        menor = direita;
    }
    if (menor != index) {
        trocar(&heap->pedidos[index], &heap->pedidos[menor]);
        descer(heap, menor);
    }
}

// Insere um novo pedido na heap
void inserirPedido(Heap* heap, Cliente* cliente, const char* descricao, int prioridade) {
    if (heap->tamanho >= TAMANHO_HEAP) {
        printf("Erro: A fila de pedidos está cheia.\n");
        return;
    }
    PedidoSuporte novoPedido;
    novoPedido.cliente = cliente;  // Usa o cliente encontrado
    strcpy(novoPedido.descricao, descricao);
    novoPedido.prioridade = prioridade;

    heap->pedidos[heap->tamanho] = novoPedido;
    subir(heap, heap->tamanho);
    heap->tamanho++;
    printf("Pedido inserido com sucesso!\n");
}

// Remove e retorna o pedido de maior prioridade
PedidoSuporte removerPedido(Heap* heap) {
    if (heap->tamanho == 0) {
        printf("Erro: Não há pedidos na fila.\n");
        PedidoSuporte vazio = {NULL, "", -1};
        return vazio;
    }
    PedidoSuporte topo = heap->pedidos[0];
    heap->pedidos[0] = heap->pedidos[--heap->tamanho];
    descer(heap, 0);
    return topo;
}

void realizarCompra(Heap* heap, NodoAVL* raizEstoque, int idItem, int quantidade, const char* nomeCliente) {
    // Buscar cliente pelo nome
    Cliente* cliente = buscarClientePedido(nomeCliente);
    if (cliente == NULL) {
        printf("Erro: Cliente não encontrado.\n");
        return;
    }

    // Buscar item pelo ID no estoque
    NodoAVL* itemEncontrado = buscar(raizEstoque, idItem);
    if (itemEncontrado == NULL) {
        printf("Erro: Item com ID %d não encontrado no estoque.\n", idItem);
        return;
    }

    // Verificar se há quantidade suficiente em estoque
    if (itemEncontrado->item.quantidade < quantidade) {
        printf("Erro: Quantidade insuficiente em estoque.\n");
        return;
    }

    // Calcular o preço total da compra
    int precoTotal = itemEncontrado->item.preco * quantidade;

    // Verificar se o cliente tem saldo suficiente na carteira
    if (cliente->carteira < precoTotal) {
        printf("Erro: Saldo insuficiente na carteira do cliente.\n");
        return;
    }

    // Realizar a compra
    cliente->carteira -= precoTotal;
    itemEncontrado->item.quantidade -= quantidade;

    printf("Compra realizada com sucesso!\n");
    printf("Cliente: %s\n", cliente->nome);
    printf("Item: %s | Quantidade: %d | Preço Total: %d\n",
           itemEncontrado->item.nome, quantidade, precoTotal);
    printf("Saldo restante na carteira: %d\n", cliente->carteira);
}

// Lista todos os pedidos na heap
void listarPedidos(Heap* heap) {
    if (heap->tamanho == 0) {
        printf("Nenhum pedido na fila.\n");
        return;
    }
    printf("--- Pedidos de Suporte ---\n");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("Cliente: %s | Descrição: %s | Prioridade: %d\n",
               heap->pedidos[i].cliente->nome,
               heap->pedidos[i].descricao,
               heap->pedidos[i].prioridade);
    }
}

// Função de menu para o suporte ao cliente
void menuSuporte(Heap* heap, NodoAVL* raizEstoque) {
    int opcao;
    do {
        printf("\n--- Menu de Suporte ---\n");
        printf("1. Inserir Pedido\n");
        printf("2. Atender Pedido\n");
        printf("3. Listar Pedidos\n");
        printf("4. realizar compra\n");
        printf("5. sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer

        if (opcao == 1) {
            char nomeCliente[50], descricao[100];
            int prioridade;

            printf("Digite o nome do cliente: ");
            fgets(nomeCliente, 50, stdin);
            nomeCliente[strcspn(nomeCliente, "\n")] = '\0';  // Remove o \n

            // Busca o cliente independentemente de maiúsculas/minúsculas
            Cliente* clienteEncontrado = buscarClientePedido(nomeCliente);
            if (clienteEncontrado == NULL) {
                printf("Erro: Cliente não encontrado.\n");
                continue;  // Volta ao início do loop
            }

            printf("Digite a descrição do pedido: ");
            fgets(descricao, 100, stdin);
            descricao[strcspn(descricao, "\n")] = '\0';  // Remove o \n

            printf("Digite a prioridade do pedido (1 = Alta, 5 = Baixa): ");
            scanf("%d", &prioridade);

            inserirPedido(heap, clienteEncontrado, descricao, prioridade);
        } else if (opcao == 2) {
            PedidoSuporte pedido = removerPedido(heap);
            if (pedido.prioridade != -1) {
                printf("Atendendo pedido de %s: %s\n",
                       pedido.cliente->nome, pedido.descricao);
            }
        } else if (opcao == 3) {
            listarPedidos(heap);
        } else if (opcao == 4) {
            int idItem, quantidade;
            char nomeCliente[50];

            printf("Digite o ID do item: ");
            scanf("%d", &idItem);
            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);
            getchar();  // Limpar buffer

            printf("Digite o nome do cliente: ");
            fgets(nomeCliente, 50, stdin);
            nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

            realizarCompra(heap, raizEstoque, idItem, quantidade, nomeCliente);
        } else if (opcao != 5) {
            printf("Opção inválida. Tente novamente.\n");
        }
        
    } while (opcao != 5);
}

void salvarPedidos(Heap* heap, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo %s para salvar.\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < heap->tamanho; i++) {
        PedidoSuporte* p = &heap->pedidos[i];
        fprintf(arquivo, "%s\n%s\n%d\n", 
                p->cliente->nome, p->descricao, p->prioridade);
    }

    fclose(arquivo);
    printf("Pedidos salvos com sucesso em %s!\n", nomeArquivo);
}

void carregarPedidos(Heap* heap, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de pedidos encontrado. Começando com a fila vazia.\n");
        return;
    }

    char nomeCliente[50], descricao[100];
    int prioridade;

    while (fscanf(arquivo, "%49[^\n]\n%99[^\n]\n%d\n", 
                  nomeCliente, descricao, &prioridade) == 3) {
        Cliente* cliente = buscarClientePedido(nomeCliente);
        if (cliente == NULL) {
            printf("Erro: Cliente %s não encontrado. Ignorando pedido.\n", nomeCliente);
            continue;
        }

        inserirPedido(heap, cliente, descricao, prioridade);
    }

    fclose(arquivo);
    printf("Pedidos carregados com sucesso de %s!\n", nomeArquivo);
}