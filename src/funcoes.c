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