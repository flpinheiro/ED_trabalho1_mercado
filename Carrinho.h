/* 
 * File:   Carrinho.h
 * Author: felipe luis pinheiro
 * matricula: 18/0052667
 * Created on 24 de Setembro de 2018, 19:00
 */

#include "estoque.h"
#include "Cliente.h"

#ifndef CARRINHO_H
#define CARRINHO_H

/**
 * estutura nó de carrinho
 */
typedef struct Nodec {
    Produto produto;
    struct Nodec * proximo;
} Nodec;

/**
 * estrutura carrinho
 */
typedef struct Carrinho {
    Nodec * pilha;
    int tamanho;
} Carrinho;

/**
 * função @printCarrinho imprime todos os dados existentes no carrinho
 * @param @Carrinho ponteiro de carrinho
 * Imprime carrinho vazio se não tiver nada no carrinho
 */
void printCarrinho(Carrinho *);

/**
 * função @carrihoVazio verifica se o carrinho est'á vazio
 * @param @Carrinho ponteiro de carrinho
 * @return 1 se estíver vazio e 0 se não estiver.
 */
int carrinhoVazio(Carrinho *);

/**
 * função @criaCarrinho cria um carrinho vazio 
 * @param @Carrinho ponteiro de carrinho
 */
void criaCarrinho(Carrinho *);

/**
 * função @carrinhoPush adiciona um produto no carrinho
 * @param @Carrinho ponteiro para carrinho
 * @param @Produto ponteiro para produto
 * @param @int quantidade de produto a ser inserida no carrinho
 * @return 1 se bem sucessido e 0 se fracasso
 */
int carrinhoPush(Carrinho *, Produto *, int);

/**
 * Função @carrinhoPop retira um elemento do carrinho
 * @param @Carrinho ponteiro de carrinho
 * @param @Produto ponteiro de produto
 * @return 1 se realizou a operação e 0 se não realizou
 */
int carrinhoPop(Carrinho *, Produto *);

/**
 * função @carrinhoStackPop verifica o primeiro elemento do carrinho.
 * @param @Carrinho ponteiro de carrinho
 * @param @Produto ponteiro de produto
 * @return 1 se realizou a operação e 0 se não realizou
 */
int carrinhoStackPop(Carrinho *, Produto *);


/**
 * função @escolheProdutos escolhe produto de estoque
 * @param @Carrinho ponteiro de carrinho
 * @param @Estoque ponteiro de estoque
 * @param @int quantidade de produtos a ser adicionado aos carrinho
 * @return 1 se conseguiu resolver
 */
int escolheProdutos(Carrinho *, Estoque *, int, Repor *);

/**
 * Função @primeiroCarrinho retorno o ponteiro para o primeiro produto no 
 * carrinho, ou null se o carrinho estiver vazio
 * @param @Carrinho pontiero de carrinho
 * @return @Produto ponteiro de produto
 */
Produto * primeiroCarrinho(Carrinho *);

#endif /* CARRINHO_H */
