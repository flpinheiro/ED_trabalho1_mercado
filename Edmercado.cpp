/* 
 * File:   Edmercado.cpp
 * Author: felipe luis pinheiro
 * matricula: 18/0052667
 * Created on 20 de Setembro de 2018, 18:14
 * programa desenvolvido como parte da avaliação do professor Bruno macchiavelo 
 * da materia Estrutura de dados do departamento de ciência da computação da 
 * universidade de brasilia - DF
 */
/*biblioteca padrão c++*/
#include <ctime>
#include <cstdlib>
#include <iostream>
/*biblioteca padrão C*/
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*biblioteca pessoal*/
#include "Cliente.h"
#include "utiil.h"
#include "estoque.h"
#include "Carrinho.h"

#define qtd_fila 4 // quantidade de caixas que existem nesse mercado
#define unity 5 //quantidade de itens que podem ser processado por unidade de tempo nesse mercado.

using namespace std;

int main(int argc, char** argv) {
    /*gerador de numeros aleatorios*/
    srand(time(NULL));
    /* inicia as variaveis */
    int freg = 10; // numero de fregueses
    int temp = 10; // tempo de espera
    int fila_escolha; //fila a ser escolhida
    int qtd_clientes_fila; //quantidade do clientes na fila observada
    int total_cliente = 0; //total de clientes atualmente no mercado
    /*cria estoque do mercado*/
    Estoque estoque; //estoque do mercado
    criaEstoqueVazio(&estoque);
    criaEstoque(&estoque);
    /*cria o repor*/
    Repor repor; //lista (fila) de reposiçào
    criaRepor(&repor);
    /*cria fila do mercado*/
    Fila * fila = (Fila *) malloc(sizeof (Fila) * qtd_fila);
    Cliente * primeiro[qtd_fila]; // cliente que está sendo atendido no caixa
    /*total gasto por cada cliente atualmente atendido*/
    float * total_gasto = (float *) calloc(sizeof (float), qtd_fila);
    /*cria as filas vazias*/
    for (int i = 0; i < qtd_fila; i++) {
        criaFila(&fila[i]);
    }
    /*variaveis de tempo*/
    time_t current_time; // tempo de entrada de abertura do mercado
    char* c_time_string; // hora de abretura do mercado em formato de string
    /*
     * se tiver menos de 4 argumentos na linha de comando não existe argumentos 
     * suficiente para o programa funcinonar como deveria, então  trabalha com 
     * os valores padrões 
     */
    if (argc >= 2) {
        /*
         * percorre os argumentos de linha de comando e verifica o numero de 
         * fregueses -f e o tempo de espera -s
         */
        for (int cont = 1; cont < argc; cont++) {
            if (!strcmp(argv[cont], "-f")) {
                freg = atoi(argv[++cont]);
            }
            if (!strcmp(argv[cont], "-s")) {
                temp = atoi(argv[++cont]);
                /*
                 * Verifica se o tempo mínimo é de pelo menos 5 segundos.
                 */
                if (temp < 5) {
                    temp == 5;
                }
            }
        }
    }
    /*
     * imprime o tempo mínimo e a quantidade de fregues para conferencia.
     */
    cout << "numero de clientes -f: " << freg << endl;
    cout << "tempo mínimo de espera -s: " << temp << endl;
    /* Obtain current time. */
    current_time = time(NULL);
    if (current_time == ((time_t) - 1)) {
        (void) fprintf(stderr, "ERRO: Falha em obter a hora atual.\n");
        exit(EXIT_FAILURE);
    }
    /* Convert to local time format. */
    c_time_string = ctime(&current_time);
    if (c_time_string == NULL) {
        (void) fprintf(stderr, "ERRO: falha em converter a hora atual em string.\n");
        exit(EXIT_FAILURE);
    }
    cout << "Seja bem vindo ao EDmercado\nEsperamos que as suas compras sejam as melhores possiveis." << endl;
    cout << "O mercado foi aberto as " << c_time_string << endl;
    sleep(temp);
    /*executa até a quantidade máxima a ser atendida por dia*/
    int clientes = 1;
    for (int ciclo = 1; ciclo <= 50; ciclo++) {
        /* realiza a escolha da fila com a menor quantidade de pessoas */
        fila_escolha = 0;
        qtd_clientes_fila = fila[0].tamanho;
        for (int i = 0; i < qtd_fila; i++) {
            if (qtd_clientes_fila > fila[i].tamanho) {
                qtd_clientes_fila = fila[i].tamanho;
                fila_escolha = i;
            }
        }
        /*verifica se o mercado está cheio, se não estiver continua entrando clientes*/
        if (total_cliente < freg) {
            entraCliente(&fila[fila_escolha], clientes, &estoque, &repor);
            clientes++;
        }
        /*o cliente paga a conta no caixa*/
        for (int i = 0; i < qtd_fila; i++) {
            for (int j = 0; j < unity; j++) {
                /*recebe o primeiro cliente da fila*/
                primeiro[i] = primeiroFila(&fila[i]);
                /*verifica se a fila não está vazia*/
                if (primeiro[i] != NULL) {
                    /*verifica se o carrinho está vazio*/
                    if (carrinhoVazio(&primeiro[i]->carrinho)) {
                        /*coloca o gasto total do cliente*/
                        cout << "Cliente " << primeiro[i]->codigo << endl <<
                                "gastou " << total_gasto[i] << endl;
                        saiCliente(&fila[i]);
                        total_gasto[i] = 0;
                        break;
                    } else {
                        /*soma o gasto do cliente*/
                        total_gasto[i] += compra(&fila[i]);
                    }
                }
            }
        }
        /*zera a quantidade de clientes*/
        total_cliente = 0;
        for (int j = 0; j < qtd_fila; j++) {
            /* imprime todas as filas mostrando os cliente em cada fila */
            cout << "Caixa " << j + 1 << endl;
            printFila(&fila[j]);
            /*verifica o total de clientes atualmente no mercado.*/
            total_cliente += fila[j].tamanho;
        }
        cout << endl;
        /*imprime o total de clientes  no estoque*/
        cout << "total de clientes no mercado " << total_cliente << endl;
        /*atualiza o estoque*/
        atualizaRepor(&repor, &estoque);
        /*Espera para criar novo freques*/
        sleep(temp);
    }
    /*libera o espaço alocado e finaliza o programa*/
    free(fila);
    free(total_gasto);
    cout << "Volte sempre" << endl;
    return 0;
}
