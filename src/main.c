#include "suporte.c"

void limpar_tela() {
    printf("Pressione ENTER para limpar a tela...");
    getchar();
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(){

    NodoAVL* raiz = NULL;
    int opcao;
    Heap heap;
    
    inicializarTabela();
    inicializarHeap(&heap);

    carregarClientesArquivo();
    carregarItensArquivo("estoque.txt", &raiz);
    carregarPedidos(&heap, "pedidos.txt");
    limpar_tela();
    

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
                menuEstoque(&raiz);
                break;
            case 2:
                limpar_tela();
                menuSuporte(&heap, raiz);
                break;
            case 3:
                limpar_tela();
                menuClientes();
                break;
            case 4:
                limpar_tela();
                salvarPedidos(&heap, "pedidos.txt");
                printf("Saindo... Obrigado por usar o TechFix!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    FILE* arquivo = fopen("estoque.txt", "w");
    if (arquivo != NULL) {
        salvarItensArquivo(arquivo, raiz);
        fclose(arquivo);
    }

    return 0;

}