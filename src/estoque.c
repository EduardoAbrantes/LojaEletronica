#include "../include/estoque.h"

struct Item {
    int id;             
    char nome[100];     
    float preco;   
    int quantidade;
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
    if (nodo == NULL || nodo->item.id == id) {
        return nodo;  // Retorna o nodo se encontrado ou NULL se não
    }
    if (id < nodo->item.id) {
        return buscar(nodo->esquerda, id);  // Busca na subárvore esquerda
    } else {
        return buscar(nodo->direita, id);  // Busca na subárvore direita
    }
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

void carregarItensArquivo(const char* nomeArquivo, NodoAVL** raiz) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado. Iniciando com estoque vazio.\n");
        return;
    }

    Item item;
    while (fscanf(arquivo, "%d;%[^;];%f;%d\n", 
                  &item.id, item.nome, &item.preco, &item.quantidade) == 4) {
        *raiz = inserir(*raiz, item);
    }

    fclose(arquivo);
}


void salvarItensArquivo(FILE* arquivo, NodoAVL* nodo) {
    if (nodo != NULL) {
        salvarItensArquivo(arquivo, nodo->esquerda);
        fprintf(arquivo, "%d;%s;%.2f;%d\n", 
                nodo->item.id, nodo->item.nome, nodo->item.preco, nodo->item.quantidade);
        salvarItensArquivo(arquivo, nodo->direita);
    }
}


void adicionarItem(NodoAVL** raiz) {
    Item novoItem;

    while (1) {  // Loop até que o usuário digite um ID válido
        printf("ID do novo item: ");
        scanf("%d", &novoItem.id);
        getchar();

        // Verifica se o ID já existe na árvore
        if (buscar(*raiz, novoItem.id) != NULL) {
            printf("Erro: O ID %d já existe! Digite outro.\n", novoItem.id);
        } else {
            break;  // Sai do loop se o ID for único
        }
    }

    printf("Nome do item: ");
    fgets(novoItem.nome, 50, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;  // Remove o '\n'

    printf("Preço do item: ");
    scanf("%f", &novoItem.preco);

    printf("Quantidade do item: ");
    scanf("%d", &novoItem.quantidade);

    *raiz = inserir(*raiz, novoItem);
    printf("Item adicionado com sucesso!\n");
}


void buscarItem(NodoAVL* raiz) {
    int id;
    printf("Digite o ID do item a ser buscado: ");
    scanf("%d", &id);

    NodoAVL* resultado = buscar(raiz, id);
    if (resultado != NULL) {
        printf("Item encontrado: ID: %d, Nome: %s, Preço: %.2f, quantidade: %d\n", resultado->item.id, resultado->item.nome, resultado->item.preco, resultado->item.quantidade);
    } else {
        printf("Item não encontrado!\n");
    }
}

void listarItens(NodoAVL* raiz) {
    if (raiz != NULL) {
        listarItens(raiz->esquerda);
        printf("ID: %d | Nome: %s | Preço: %.2f | Quantidade: %d\n", 
               raiz->item.id, raiz->item.nome, raiz->item.preco, raiz->item.quantidade);
        listarItens(raiz->direita);
    }
}

void atualizarPreco(NodoAVL* raiz) {
    int id;
    printf("Digite o ID do item para atualizar o preço: ");
    scanf("%d", &id);

    NodoAVL* nodo = buscar(raiz, id);
    if (nodo != NULL) {
        float novoPreco;
        printf("Digite o novo preço: ");
        scanf("%f", &novoPreco);
        nodo->item.preco = novoPreco;
        printf("Preço atualizado com sucesso!\n");
    } else {
        printf("Item não encontrado!\n");
    }
}

void removerItem(NodoAVL** raiz) {
    int id;
    printf("Digite o ID do item a ser removido: ");
    scanf("%d", &id);

    *raiz = remover(*raiz, id);
    printf("Item removido com sucesso!\n");
}

// Menu para gestão de estoque
void menuEstoque(NodoAVL** raiz) {
    int opcao;

    do {
        printf("\n--- Menu de Estoque ---\n");
        printf("1. Adicionar item ao estoque\n");
        printf("2. Buscar item no estoque\n");
        printf("3. Listar todos os itens do estoque\n");
        printf("4. Atualizar preço de um item\n");
        printf("5. Remover item do estoque\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarItem(raiz);
                break;
            case 2:
                buscarItem(*raiz);
                break;
            case 3:
                listarItens(*raiz);
                break;
            case 4:
                atualizarPreco(*raiz);
                break;
            case 5:
                removerItem(raiz);
                break;
            case 0:
                printf("Saindo do menu de estoque.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

NodoAVL* buscarItemAVL(NodoAVL* raiz, int id) {
    if (raiz == NULL) {
        return NULL;  // Item não encontrado.
    }
    if (id < raiz->item.id) {
        return buscarItemAVL(raiz->esquerda, id);  // Busca na subárvore esquerda.
    } else if (id > raiz->item.id) {
        return buscarItemAVL(raiz->direita, id);  // Busca na subárvore direita.
    } else {
        return raiz;  // Item encontrado.
    }
}
