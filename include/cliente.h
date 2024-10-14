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
int funcaoHash(const char* nome);
void inserirCliente(const char* nome, const char* email, int idade, int carteira);
Cliente* buscarClientePedido(const char* nome);
void buscarCliente(const char* nome);
void salvarClientesArquivo();
void alterarCarteira(const char* nome, int novaCarteira);
void carregarClientesArquivo();
void listarClientes();
void menuClientes();
