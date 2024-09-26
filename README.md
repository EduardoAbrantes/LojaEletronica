# **Gereciamento de LojaEletronica**
Projeto de  um sistema na Linguagem C para gerenciamento de um sistema de loja de eletrônicos.  

## **Desenvolvedor**
> [Eduardo Pereira Abrantes](https://github.com/EduardoAbrantes)
>
***

# **Tabela de conteúdo**
> [Introdução](#introdução)
> 
> [Problemática](#problemática)

***

## **Introdução**

O Projeto Loja de Eletrônicos é um sistema desenvolvido para gerenciar diversos aspectos operacionais de uma loja de eletrônicos. Este sistema foi projetado para fornecer uma solução prática e eficiente para gerenciar o estoque de produtos, lidar com suporte técnico e assistência e gerenciamento de clientes.

## **Problemática**

O sistema da loja de eletronicos em questão necessita de 3 funcionalidades principais, cada uma usando uma estrutura de dados para o seu funcionamento e um menu para cada uma delas. Para esse projeto as funcionalidades escolhidas foram gerenciamento de estoque, gerenciamento de clientes e suporte tecnico, com as estruturas arvore AVL, Tabela Hash e Heap respectivamente.

### Funcionalidades Principais:

- Gerenciamento de Estoque:
  - Adicionar, remover, buscar e atualizar itens de tecnologia.
  - Estrutura de dados: Árvore AVL para garantir eficiência.
  
- Gerenciamento de Clientes:
  - Adicionar, remover, buscar e atualizar perfis de clientes do sistema.
  - Estrutura de dados: Tabela Hash para permitir acesso rápido e eficiente de dados.

- Suporte Técnico:
  - Armazenamento de pedidos de suporte.
  - Estrutura de dados: Heap para ter controle de prioridade sobre os pedidos de suporte.


### 2. Compilação e Execução
```bash
Compilação:
gcc -g -o gestao_estoque src/main.c src/estoque.c src/funcoes.c -Iinclude

Execução:
./gestao_estoque