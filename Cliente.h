/* 
 * File:   Cliente.h
 * Author: felipe luis pinheiro
 * matricula: 18/0052667
 * Created on 20 de Setembro de 2018, 18:20
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include <ctime>
#include <string>
#include "Carrinho.h"

using namespace std;

/**
 * strutura @Cliente possui:
 * @codigo @int: codigo de entrada do cliente
 * @total_pacotes @int: numero de pacotes comprado pelo cliente varia entre 1 e 10.
 * @current_time @time_t: hora de entrada do cliente no mercado
 */
typedef struct Cliente {
    int codigo;
    int total_pacotes;
    time_t current_time;
    Carrinho carrinho;
} Cliente;

/**
 * função @printCliente imprime o cliente com todos os dados dele
 * @param @Cliente recebe ponteiro de cliente
 */
void printCliente(Cliente *);

/**
 * Estrutura Node: nó da fila de Clientes, tem ponteiro para proximo nó e informações do cliente
 */
typedef struct Node {
    Cliente cliente;
    struct Node * proximo;
} Node;

/**
 * estrutura Fila: Define uma fila de clientes possui Nó inicial e nó final e tamanho
 */
typedef struct Fila {
    Node * inicio;
    Node * final;
    int tamanho;
} Fila;

/**
 * função @criaFila cria uma fila vazia
 * @param @Fila recebe um ponteiro de fila para armazenar a fila vazia
 */
void criaFila(Fila *);

/**
 * Função @filaVazia verifica se a fila está vazia
 * @param @Fila recebe um ponteiro de fila
 * @return 1 se estiver vazia (true) ou 0 se estiver cheia (false)
 */
int filaVazia(Fila *);

/**
 * Função @printFila imprime a fila toda
 * @param @Fila recebe ponteiro para fila
 */
void printFila(Fila *);

/**
 * Função @entraCliente cria e adiciona um cliente novo na fila, quando terminada deve tambem deduzir os itens do estoque e outras tarefas
 * @param @Fila recebe um ponteiro de fila 
 * @param @codigo_cliente codigo do cliente que está entrando na fila
 * @param ponteiro para estoque
 * @return 1 se o cliente conseguiu entrar na fila e 0 se o cliente não conseguiu entrar na fila
 */
int entraCliente(Fila *, int, Estoque *, Repor *);

/**
 * função @destroiFila essa função destroi completamente uma fila liberando todo o espaço armazenado
 * @param 
 */
void destroiFila(Fila *);

/**
 * função @saiCliente sai o primeiro cliente da fila
 * @param @Fila ponteiro de fila
 * @return 1 se conseguiu retirar o cliente e 00 se não conseguiu
 */
int saiCliente(Fila *);

/**
 * função @clienteCarrinho retorna o carrinho do primeiro cliente da fila
 * @param @Fila ponteiro de fila
 * @param @Carrinho ponteiro de carrinho
 * @return 1 se conseguiu e 0 se não conseguiu
 */
int clienteCarrinho(Fila *, Carrinho *);

/**
 * função @primeiroFila retorna o ponteiro para o primeiro cliente da fila
 * @param @Fila ponteiro de fila
 * @return @Cliente ponteiro de cliente
 */
Cliente * primeiroFila(Fila *);

/**
 * função @carrinhoCliente retorn o ponteiro para o carrinho do cliente
 * @param @Cliente ponteiro para cliente 
 * @return @Carrinho ponteiro de carrinho
 */
Carrinho * carrinhoCliente(Cliente *);

/**
 * função @compra realiza a compra do cliente
 * @param @Fila ponteiro de fila
 * @return @float o valor do produto comprado pelo cliente
 */
float compra(Fila *);

#endif /* CLIENTE_H */
