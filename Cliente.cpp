/* 
 * File:   Cliente.cpp
 * Author: felipe luis pinheiro
 * matricula: 18/0052667
 * Created on 20 de Setembro de 2018, 18:20
 */

#include "Cliente.h"
#include "utiil.h"

#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void printCliente(Cliente * cliente) {
    /*imprime as informações do cliente*/
    cout << "Cliente: " << cliente->codigo << endl;
    cout << "total de pacotes: " << cliente->total_pacotes << endl;
    /*converte a hora de entrada do cliente em string para impressão e verifica se foi possivel fazer a conversão*/
    char* current_time_string;
    current_time_string = ctime(&(cliente->current_time));
    if (current_time_string == NULL) {
        (void) fprintf(stderr, "ERRO: Falha em converter hora atual em string\n");
        cout << "ERRO: Falha em converter hora atual em string" << endl;
        exit(EXIT_FAILURE);
    }
    /*imprime a hora de entrada do cliente*/
    cout << "Hora de entrada do cliente" << current_time_string << endl;
    /* imprime o tempo de espera do cliente */
    time_t current_time;
    /*recupera a hora de entrada do cliente no mercado e verifica se foi possivel recuperar essa hora*/
    time(&(current_time));
    if (current_time == ((time_t) - 1)) {
        /* se não foir possivel recuperar a hora finaliza em erro */
        (void) fprintf(stderr, "ERRO: Falha em obter hora atual.\n");
        cout << "ERRO: Falha em obter hora atual." << endl;
        //        exit(EXIT_FAILURE);
        return ;
    }
    cout << "O cliente está esperando a: " << current_time - cliente->current_time << endl;
    /*espaço recervado para a impressão do carrinho*/
    printCarrinho(&(cliente->carrinho));
    return;
}

void criaFila(Fila * fila) {
    /*define os ponteiros da fila como vazio*/
    fila->final = NULL;
    fila->inicio = NULL;
    /*define o tamanho da fila para 0*/
    fila->tamanho = 0;
}

int filaVazia(Fila * fila) {
    /*verifica que a fila não tem nó inicial e final*/
    return (fila->final == NULL && fila->inicio == NULL);
}

void printFila(Fila * fila) {
    /*verifica se a fila está vazia*/
    if (filaVazia(fila)) {
        cout << "fila Vazia" << endl;
        return;
    } else if (fila->tamanho == 1) {
        cout << "Tem apenas um cliente na fila" << endl;
    } else {
        cout << "Existem " << fila->tamanho << " Clientes na fila" << endl;
    }
    /*percorre a fila até achar um nó nulo imprimindo todos os clientes com todos os seus dados*/
    Node * aux = fila->inicio;
    while (aux != NULL) {
        printCliente(&(aux->cliente));
        aux = aux->proximo;
    }
    return;
}

int entraCliente(Fila * fila, int codigo_cliente, Estoque * estoque, Repor * repor) {
    /*cria um cliente(no) novo e verifica se foi criado*/
    Node * no;
    no = (Node *) malloc(sizeof (Node));
    if (no == NULL) {
        cout << "ERRO:Impossivel criar cliente novo." << endl;
        (void) fprintf(stderr, "ERRO:Impossivel criar cliente novo.\n");
        return 0;
    }
    /* salca as informaçoes no novo cliente */
    no->cliente.codigo = codigo_cliente;
    no->cliente.total_pacotes = aleatorio(100, 1);
    /*define um carrinho vazio*/
    criaCarrinho(&no->cliente.carrinho);
    /*cliente escolhe os produtos e coloca no carrinho*/
    if (!escolheProdutos(&no->cliente.carrinho, estoque, no->cliente.total_pacotes, repor)) {
        criaCarrinho(&no->cliente.carrinho);
    }
    /*recupera a hora de entrada do cliente no mercado e verifica se foi possivel recuperar essa hora*/
    time(&(no->cliente.current_time));
    if (no->cliente.current_time == ((time_t) - 1)) {
        /* se não foir possivel recuperar a hora finaliza em erro */
        (void) fprintf(stderr, "ERRO: Falha em obter hora atual.\n");
        cout << "ERRO: Falha em obter hora atual." << endl;
        //        exit(EXIT_FAILURE);
        return 0;
    }
    no->proximo = NULL;
    /*verifica se a fila está vazia, se estiver o nó entra no inicio, se não entra depois do ultimo*/
    if (filaVazia(fila)) {
        fila->inicio = no;
    } else {
        fila->final->proximo = no;
    }
    /*o nó novo vai para o final da fila e o tamanho da fila aumenta de 1*/
    fila->final = no;
    fila->tamanho++;
    /*cliente entra na fila*/
    return 1;
}

int saiCliente(Fila * fila) {
    /* Verifica se a fila está vazia */
    if (filaVazia(fila)) {
        /* retorna fracasso */
        return 0;
    }
    /* retira o primeiro elemento da fila */
    Node * aux = fila->inicio;
    if (fila->inicio == fila->final) {
        fila->final = NULL;
    }
    fila->inicio = fila->inicio->proximo;
    /* libera o espaço do elemento que saiu */
    free(aux);
    /* reduz o tamanho da fila */
    fila->tamanho--;
    /* retorna sucesso */
    return 1;
}

void destroiFila(Fila * fila) {
    Node * aux = fila->inicio;
    Node * aux2;
    /*percorre a fila*/
    while (aux != NULL) {
        aux2 = aux;
        aux = aux->proximo;
        /*libera a memoria alocada*/
        free((aux2));
    }
    /*define a fila como vazia*/
    fila->inicio = NULL;
    fila->final = NULL;
    fila->tamanho = 0;
}

int clienteCarrinho(Fila * fila, Carrinho * carrinho) {
    /*verifica se a fila está vazia*/
    if (filaVazia(fila)) {
        return 0;
    }
    /*poneiro do carrinho do cliente*/
    *carrinho = fila->inicio->cliente.carrinho;
    return 1;
}

Cliente * primeiroFila(Fila * fila) {
    /*verifica se a fila está vazia*/
    if (filaVazia(fila)) {
        return NULL;
    }
    /*retorna poneiro do primeiro cliente*/
    return &(fila->inicio->cliente);
}

Carrinho * carrinhoCliente(Cliente * cliente) {
    /*verifica se o carrinho está vazio*/
    if (carrinhoVazio(&cliente->carrinho)) {
        return NULL;
    }
    /*retorna o ponteiro para o carriho*/
    return &(cliente->carrinho);
}

float compra(Fila * fila) {
    /*recebe o ponteiro do cliente*/
    Cliente * cliente = primeiroFila(fila);
    /*recebe o ponteiro do carrinho*/
    Carrinho * carrinho = carrinhoCliente(cliente);
    /*recebo o ponteiro de produto*/
    Produto * produto = primeiroCarrinho(carrinho);
    /*diminui a quantidade de produtos em 1*/
    produto->quantidade--;
    float valor = produto->valor;
    /*se a quantidade do produto estiver zero o produto é retirado do carrinho*/
    if (produto->quantidade <= 0) {
        carrinhoPop(carrinho, produto);
    }
    /*retorna o valor do produto*/
    return valor;
}