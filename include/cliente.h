#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

/**
 * @struct cliente
 * @brief Estrutura para representar um cliente.
 */
typedef struct cliente Cliente;

void inicializarTabela();
int funcaoHash(const char* nome, int tentativa);
void inserirCliente(const char* nome, const char* email, int idade);
void buscarCliente(const char* nome);
void salvarClientesArquivo();
void menuClientes();