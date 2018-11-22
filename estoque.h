/* 
 * File:   estoque.h
 * Author: felipe luis pinheiro
 * matricula: 18/0052667
 * Created on 21 de Setembro de 2018, 19:55
 */

#ifndef ESTOQUE_H
#define ESTOQUE_H

#define codigo_produto_max 100
#define quantida_produto_padrao 10
#define tempo_espera 2
#define preco(c) 2 + 2 * c

/**
 * Estrutura Produto possui codigo do produto, valor do produto, e quantidade do produto
 */
typedef struct Produto {
    int codigo; /*codigo do produto valor sequencial*/
    float valor; /*valor do produto*/
    int quantidade; /*quantidade do produto em estoque*/
} Produto;

/**
 * Função @printProduto imprime o produto
 * @param @Produto ponteiro para produto
 */
void printProduto(Produto *);

/**
 * EStrutura Nodes é o nodo da lista Estoque
 */
typedef struct Nodes {
    Produto produto;
    struct Nodes * proximo;
    struct Nodes * anterior;
} Nodes;

/**
 * Lista EStoque
 */
typedef struct Estoque {
    Nodes * primeiro;
    int tamanho;
} Estoque;

/**
 * funcão @criaEstoqueVazio cria um estoque vazio
 * @param @Estoque recebe ponteiro para estoque
 */
void criaEstoqueVazio(Estoque *);

/**
 * funcão @criaEstoque cria um estoque vazio
 * @param @Estoque recebe ponteiro para estoque
 * @return 1 se conseguiu criar o estroque e 0 se não conseguiu 
 */
int criaEstoque(Estoque *);

/**
 * função @printEstoque imprime o estoque inteiro.
 * @param 
 */
void printEstoque(Estoque *);
/**
 * funcão @estoqueVazio verifica se o estoque está vazio
 * @param @estoque recebe ponteiro de estoque
 * @return 1 se estiver vazio (verdade) e 0 se não estiver (falso)
 */
int estoqueVazio(Estoque *);

/**
 * Função @inserirProduto inseri um produto no estoque na posição do codigo dele
 * @param @Estoque recebe um ponteiro de estoque
 * @param @Produto recebe um ponteiro de produto
 * @return retorna 1 se conseguiu inserir e 0 se não conseguiu
 */
int inserirProduto(Estoque *, int);

/**
 * Função @procura um determinado produto no estoque esoolhe uma das duas funções abaixo para fazer a busca dependendo do quem seja "mais rápido"
 * @param @Estoque ponteiro de estoque
 * @param @int codigo do produto a ser procurado
 * @return Retorna o ponteiro do produto se existir ou NULL se não existir
 */
Produto * procura(Estoque *, int);

/**
 * Função @procuraESquerda procura um determinado produto no estoque, porém percorre a lista sempre no sentido anti-horário, ou seja, do maior par ao menor
 * @param @Estoque ponteiro de estoque
 * @param @int codigo do produto a ser procurado
 * @return Retorna o ponteiro do produto se existir ou NULL se não existir
 */
Produto * procuraEsquerda(Estoque *, int);

/**
 * Função @procuraDireita procura um determinado produto no estoque , porém percorre a lista sempre no sentido horário, ou seja, do menor para o maior
 * @param @Estoque ponteiro de estoque
 * @param @int codigo do produto a ser procurado
 * @return Retorna o ponteiro do produto se existir ou NULL se não existir
 */
Produto * procuraDireita(Estoque *, int);

/**
 * função @removeProduto remove um produto da lista de produtos
 * @param @Estoque ponteiro para estoque
 * @param @int codigo do produto a ser removido
 * @return 1 se o produto foi corretamente removido e 0 se não conseguiu remover o produto
 */
int removeProduto(Estoque *, int);

/************************************************************************************/

/**
 * função @destroiEstoque destroi completamente o estoque liberando toda a memoria
 * @param @Estoque ponteiro de estoque
 */
void destroiEstoque(Estoque *);

/**
 * Estrutura Faltante: salva o codigo do produto e o tempo de espera para repor
 */
typedef struct Faltante{
    struct Faltante * proximo;
    int codigo;
    int espera;
}Faltante;

/**
 * Estrutura fila de reposição
 */
typedef struct Repor{
    Faltante * inicio;
    Faltante * fim;
}Repor;

/**
 * função @criaRepor cria uma fila de reposição vazia
 * @param @Repor ponteiro de Repor
 */
void criaRepor(Repor *);

/**
 * função @criaVazia verifica se a fila de reposição está vazia
 * @param @Repor ponteiro de Repor 
 * @return 1 se estiver vazia e 0 se não estiver vazia
 */
int reporVazia(Repor *);

/**
 * função @atualizaRepor atualiza a fila de reposiçao, diminiu o tempo de espera, 
 * se o tempo de espera estiver zerado acrescente o produto no estoque
 * @param @Repor ponteiro de repor
 * @param @Estoque ponteiro de estoque
 * @return 1 se bem sucessido e 0 se não foi bem sucessido
 */
int atualizaRepor(Repor *, Estoque *);

/**
 * função @procuraRepor procura o produto dentro da fila de reposição
 * @param @Repor ponteiro de repor
 * @param @inte codigo do produto a ser procurado
 * @return 1 se existe e 0 se não existe
 */
int procuraRepor(Repor *, int);

/**
 * funçào @adicionaRepor adiciona um produto na fila de reposição
 * @param @Repor ponteiro de repos
 * @param @int codigo do produto a ser adicionado
 * @return 1 se foi bem sucedido e 0 se não foi bem sucedido
 */
int adicionaRepor(Repor *, int);

/**
 * Função @removeRepor remove um produto da lista de repor
 * @param @Repor ponteiro de repor
 * @param @Produto ponteiro de produto
 * @return 1 se for bem sucedido e 0 se não foi bem sucessido
 */
int removeRepor(Repor *, Produto *);

/**
 * função @printRepor imprime a fila de reposição
 * @param @repor ponteiro de repor
 */
void printRepor(Repor *);

#endif /* ESTOQUE_H */
