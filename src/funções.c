#include "../include/funções.h"

void limpar_tela() {
    printf("Pressione ENTER para limpar a tela...");
    getchar();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void MenuPrincipal() {
    int opcao;
    do {
        printf("*************************************************\n");
        printf("*              Bem-vindo à TechFix              *\n");
        printf("*               Soluções em Eletrônicos          *\n");
        printf("*************************************************\n");
        printf("1. Gestão de Estoque\n");
        printf("2. Suporte Técnico e Assistência\n");
        printf("3. Gestão de clientes\n");
        printf("4. Sair\n");
        printf("Por favor, selecione uma opção (1-4): ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                limpar_tela();
                menuEstoque();
                break;
            case 2:
                limpar_tela();
                menuSuporte();
                break;
            case 3:
                limpar_tela();
                menuClientes();
                break;
            case 4:
                limpar_tela();
                printf("Saindo... Obrigado por usar o TechFix!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);
}

void menuEstoque() {
    int opcao;
    do {
        printf("*************************************************\n");
        printf("*               Gestão de Estoque               *\n");
        printf("*************************************************\n");
        printf("1. Visualizar Estoque\n");
        printf("2. Adicionar Novo Produto\n");
        printf("3. Atualizar Quantidade de Produto\n");
        printf("4. Remover Produto do Estoque\n");
        printf("5. Registrar Compra de Produto\n");
        printf("6. Buscar Produto por Nome\n");
        printf("7. Voltar ao Menu Principal\n");
        printf("Por favor, selecione uma opção (1-7): ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado após scanf

        switch (opcao) {
            case 1:
                // Função para visualizar o estoque
                break;
            case 2:
                // Função para adicionar novo produto
                break;
            case 3:
                // Função para atualizar quantidade de produto
                break;
            case 4:
                // Função para remover produto do estoque
                break;
            case 5:
                // Função para registrar compra de produto
                break;
            case 6:
                // Função para buscar produto por nome
                break;
            case 7:
                printf("Voltando ao Menu Principal...\n");
                limpar_tela();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);
}

void menuSuporte() {
    int opcao;
    do {
        printf("*************************************************\n");
        printf("*      Suporte Técnico e Assistência            *\n");
        printf("*************************************************\n");
        printf("1. Registrar Nova Solicitação de Suporte\n");
        printf("2. Verificar Status de Solicitação\n");
        printf("3. Atualizar Status de Solicitação\n");
        printf("4. Histórico de Solicitações por Cliente\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Por favor, selecione uma opção (1-5): ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Função de registrar nova solicitação de suporte não implementada.\n");
                break;
            case 2:
                printf("Função de verificar status de solicitação não implementada.\n");
                break;
            case 3:
                printf("Função de atualizar status de solicitação não implementada.\n");
                break;
            case 4:
                printf("Função de visualizar histórico de solicitações por cliente não implementada.\n");
                break;
            case 5:
                printf("Voltando ao Menu Principal...\n");
                limpar_tela();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);
}

void menuClientes() {
    int opcao;
    do {
        printf("*************************************************\n");
        printf("*                Gestão de Clientes             *\n");
        printf("*************************************************\n");
        printf("2. Adicionar Novo Cliente\n");
        printf("3. atualizar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("5. Buscar Cliente por Nome\n");
        printf("6. Voltar ao Menu Principal\n");
        printf("Por favor, selecione uma opção (1-6): ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Função de visualizar clientes não implementada.\n");
                break;
            case 2:
                printf("Função de adicionar novo cliente não implementada.\n");
                break;
            case 3:
                printf("Função de editar informações de cliente não implementada.\n");
                break;
            case 4:
                printf("Função de remover cliente não implementada.\n");
                break;
            case 5:
                printf("Função de buscar cliente por nome não implementada.\n");
                break;
            case 6:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);
}