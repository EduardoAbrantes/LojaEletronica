#include "../include/cliente.h"
//struct Cliente* prox;   
#define TAMANHO_TABELA 100  // Tamanho fixo da tabela hash


typedef struct cliente {
    char nome[50];
    char email[50];
    int idade;
    int ativo;  // Marca se o espaço está ocupado: 1 - Ativo, 0 - Vazio
};

Cliente tabelaHash[TAMANHO_TABELA];

void inicializarTabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabelaHash[i].ativo = 0;
    }
}

int ToInt(const char* nome) {
    int valor = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        valor += nome[i];
    }
    return valor;
}

int funcaoHash(const char* nome, int tentativa) {
    int chaveNumerica = ToInt(nome);
    return (chaveNumerica + tentativa) % TAMANHO_TABELA;
}

void inserirCliente(const char* nome, const char* email, int idade) {
    int tentativa = 0;
    int posicao = funcaoHash(nome, tentativa);
    int original = posicao;

    while (tabelaHash[posicao].ativo == 1) {
        if (strcmp(tabelaHash[posicao].nome, nome) == 0) {
            printf("Erro: Cliente com nome '%s' já existe. Tente outro nome.\n", nome);
            return;
        }
        tentativa++;
        posicao = funcaoHash(nome, tentativa);

        if (posicao == original) {
            printf("Erro: A tabela hash está cheia.\n");
            return;
        }
    }

    strcpy(tabelaHash[posicao].nome, nome);
    strcpy(tabelaHash[posicao].email, email);
    tabelaHash[posicao].idade = idade;
    tabelaHash[posicao].ativo = 1;

    printf("Cliente %s inserido com sucesso!\n", nome);
}

void buscarCliente(const char* nome) {
    int tentativa = 0;
    int posicao = funcaoHash(nome, tentativa);
    int original = posicao;

    while (tabelaHash[posicao].ativo) {
        if (strcmp(tabelaHash[posicao].nome, nome) == 0) {
            printf("Cliente encontrado: Nome: %s, Email: %s, Idade: %d\n",
                   tabelaHash[posicao].nome,
                   tabelaHash[posicao].email,
                   tabelaHash[posicao].idade);
            return;
        }
        tentativa++;
        posicao = funcaoHash(nome, tentativa);

        if (posicao == original) {
            break;
        }
    }
    printf("Cliente com nome '%s' não encontrado.\n", nome);
}

void salvarClientesArquivo() {
    FILE* arquivo = fopen("clientes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return;
    }

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        if (tabelaHash[i].ativo) {
            fprintf(arquivo, "Nome: %s, Email: %s, Idade: %d\n",
                    tabelaHash[i].nome,
                    tabelaHash[i].email,
                    tabelaHash[i].idade);
        }
    }

    fclose(arquivo);
    printf("Clientes salvos em clientes.txt com sucesso!\n");
}

void menuClientes() {
    int opcao;
    do {
        printf("\n--- Menu de Clientes ---\n");
        printf("1. Inserir Cliente\n");
        printf("2. Buscar Cliente\n");
        printf("3. Salvar e Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            char nome[50], email[50];
            int idade;
            printf("Digite o nome do cliente: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            printf("Digite o email do cliente: ");
            fgets(email, 50, stdin);
            email[strcspn(email, "\n")] = '\0';
            printf("Digite a idade do cliente: ");
            scanf("%d", &idade);
            getchar();

            inserirCliente(nome, email, idade);
        } else if (opcao == 2) {
            char nome[50];
            printf("Digite o nome do cliente a ser buscado: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            buscarCliente(nome);
        } else if (opcao == 3) {
            salvarClientesArquivo();
            printf("Saindo...\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);
}