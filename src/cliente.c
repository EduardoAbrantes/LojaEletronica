#include "../include/cliente.h"
//struct Cliente* prox;   
#define TAMANHO_TABELA 100  // Tamanho fixo da tabela hash


struct cliente {
    char nome[50];
    char email[50];
    int idade;
    int carteira;  // Dinheiro que o cliente tem
    int ativo;     // Marca se o espaço está ocupado: 1 - Ativo, 0 - Vazio
};

Cliente tabelaHash[TAMANHO_TABELA];

void inicializarTabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabelaHash[i].ativo = 0;
    }
}

int funcaoHash(const char* nome) {
    int hash = 0;
    for (int i = 0; nome[i]; i++) {
        hash += toupper((unsigned char)nome[i]);
    }
    return hash % TAMANHO_TABELA;
}

void inserirCliente(const char* nome, const char* email, int idade, int carteira) {
    int posicao = funcaoHash(nome);
    int original = posicao;
    int i = 0;

    while (tabelaHash[posicao].ativo == 1) {
        if (strcmp(tabelaHash[posicao].nome, nome) == 0) {
            printf("Erro: Cliente %s já existe. Tente novamente com outro nome.\n", nome);
            return;
        }
        posicao = (original + ++i) % TAMANHO_TABELA;

        if (posicao == original) {  // Tabela cheia
            printf("Erro: A tabela hash está cheia.\n");
            return;
        }
    }

    // Inserção do cliente na posição encontrada.
    strcpy(tabelaHash[posicao].nome, nome);
    strcpy(tabelaHash[posicao].email, email);
    tabelaHash[posicao].idade = idade;
    tabelaHash[posicao].carteira = carteira;
    tabelaHash[posicao].ativo = 1;

    printf("Cliente %s inserido com sucesso!\n", nome);
}

void buscarCliente(const char* nome) {
    int posicao = funcaoHash(nome);
    int original = posicao;
    int i = 0;

    while (tabelaHash[posicao].ativo) {
        if (strcasecmp(tabelaHash[posicao].nome, nome) == 0) {
            printf("Cliente encontrado: Nome: %s, Email: %s, Idade: %d, Carteira: %d\n",
                   tabelaHash[posicao].nome,
                   tabelaHash[posicao].email,
                   tabelaHash[posicao].idade,
                   tabelaHash[posicao].carteira);
            return;
        }
        posicao = (original + ++i) % TAMANHO_TABELA;

        if (posicao == original) {
            break;
        }
    }
    printf("Cliente %s não encontrado.\n", nome);
}

void salvarClientesArquivo() {
    FILE* arquivo = fopen("clientes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return;
    }

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        if (tabelaHash[i].ativo) {
            fprintf(arquivo, "Nome: %s, Email: %s, Idade: %d, Carteira: %d\n",
                    tabelaHash[i].nome,
                    tabelaHash[i].email,
                    tabelaHash[i].idade,
                    tabelaHash[i].carteira);
        }
    }

    fclose(arquivo);
    printf("Clientes salvos em clientes.txt com sucesso!\n");
}

void alterarCarteira(const char* nome, int novaCarteira) {
    int posicao = funcaoHash(nome);
    int original = posicao;
    int i = 0;

    while (tabelaHash[posicao].ativo) {
        if (strcasecmp(tabelaHash[posicao].nome, nome) == 0) {
            tabelaHash[posicao].carteira = novaCarteira;
            printf("Carteira do cliente %s alterada com sucesso! Nova carteira: %d\n",
                   tabelaHash[posicao].nome, novaCarteira);
            return;
        }
        posicao = (original + ++i) % TAMANHO_TABELA;

        if (posicao == original) {
            break;
        }
    }
    printf("Cliente %s não encontrado.\n", nome);
}

// Função para carregar clientes do arquivo clientes.txt
void carregarClientesArquivo() {
    FILE* arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura. Pode ser que não existam clientes registrados.\n");
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome[50], email[50];
        int idade, carteira;
        sscanf(linha, "Nome: %49[^,], Email: %49[^,], Idade: %d, Carteira: %d", nome, email, &idade, &carteira);
        inserirCliente(nome, email, idade, carteira);
    }

    fclose(arquivo);
}

// Função de menu para o gerenciamento de clientes.
void menuClientes() {
    int opcao;
    do {
        printf("\n--- Menu de Clientes ---\n");
        printf("1. Inserir Cliente\n");
        printf("2. Buscar Cliente\n");
        printf("3. Alterar Carteira do Cliente\n");
        printf("4. Salvar e Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer

        if (opcao == 1) {
            char nome[50], email[50];
            int idade, carteira;
            printf("Digite o nome do cliente: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0';  // Remove o \n
            printf("Digite o email do cliente: ");
            fgets(email, 50, stdin);
            email[strcspn(email, "\n")] = '\0';  // Remove o \n
            printf("Digite a idade do cliente: ");
            scanf("%d", &idade);
            printf("Digite a carteira do cliente: ");
            scanf("%d", &carteira);
            inserirCliente(nome, email, idade, carteira);
        } else if (opcao == 2) {
            char nome[50];
            printf("Digite o nome do cliente a ser buscado: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0';  // Remove o \n
            buscarCliente(nome);
        } else if (opcao == 3) {
            char nome[50];
            int novaCarteira;
            printf("Digite o nome do cliente cuja carteira deseja alterar: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = '\0';  // Remove o \n
            printf("Digite a nova quantidade na carteira: ");
            scanf("%d", &novaCarteira);
            alterarCarteira(nome, novaCarteira);
        } else if (opcao == 4) {
            salvarClientesArquivo();
            printf("Saindo...\n");
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);
}