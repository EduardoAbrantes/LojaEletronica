#include "../include/funcoes.h"

void limpar_tela() {
    printf("Pressione ENTER para limpar a tela...");
    getchar();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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
void menuGestaoClientes() {
    int opcao;
    do {
        printf("*************************************************\n");
        printf("*             Gestão de Clientes                *\n");
        printf("*************************************************\n");
        printf("1. Adicionar Cliente\n");
        printf("2. Remover cliente\n");
        printf("3. Atualizar um cliente\n");
        printf("4. buscar um cliente\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Por favor, selecione uma opção (1-5): ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Função de adicionar cliente.\n");
                break;
            case 2:
                printf("Função de remover cliente.\n");
                break;
            case 3:
                printf("Função atualizar um cliente.\n");
                break;
            case 4:
                printf("Função de buscar um cliente.\n");
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