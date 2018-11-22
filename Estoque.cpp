#include "estoque.h"
#include "Cliente.h"
#include <string.h>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>

#include <cstdlib>
#include <iostream>

using namespace std;

void printProduto(Produto * produto) {
    /*verifica se produto está vazio*/
    if (produto == NULL) {
        return;
    }
    /*imprime o produto*/
    cout << "codigo: #" << produto->codigo << endl;
    cout << "quantidade: " << produto->quantidade << endl;
    cout << "Valor: R$" << produto->valor << endl;
}

void criaEstoqueVazio(Estoque * estoque) {
    /*define o estoque como vazio*/
    (estoque->primeiro) = NULL;
    estoque->tamanho = 0;
}

int criaEstoque(Estoque * estoque) {
    criaEstoqueVazio(estoque);
    /* neste ponto o estoque está vazio, iserção do primeiro elemento */
    Nodes * aux = (Nodes *) malloc(sizeof (Nodes));
    /*verifica se o nó foi alocado*/
    if (aux == NULL) {
        (void) fprintf(stderr, "ERRO: Impossivel alocar memoria\n");
        return 0;
    }
    /*define o primeiro elemento do estoque, elemento zero*/
    estoque->primeiro = aux;
    aux->produto.codigo = 0;
    aux->produto.quantidade = quantida_produto_padrao;
    aux->produto.valor = 2;
    estoque->tamanho++;
    aux->anterior = aux;
    aux->proximo = aux;
    /*acrescento os outros elementos do estoque*/
    Nodes * novo;
    for (int i = 1; i < codigo_produto_max; i++) {
        novo = (Nodes *) malloc(sizeof (Nodes));
        /*verifica se o nó foi alocado*/
        if (novo == NULL) {
            (void) fprintf(stderr, "ERRO: Impossivel alocar memoria\n");
            return 0;
        }
        /*define os paramentros do produto*/
        novo->produto.codigo = i;
        novo->produto.quantidade = quantida_produto_padrao;
        novo->produto.valor = preco(i);
        aux->proximo = novo;
        novo->anterior = aux;
        aux = novo;
        estoque->tamanho++;
    }
    aux = estoque->primeiro;
    aux->anterior = novo;
    novo->proximo = aux;
    return 1;
}

void printEstoque(Estoque * estoque) {
    /*verifica se o estoque está vazio*/
    if (estoqueVazio(estoque)) {
        cout << "Estoque Vazio" << endl;
        return;
    }
    int cont = 0;
    Nodes * aux = estoque->primeiro;
    /*imprime os nós do estoque até chegar no inicio novamente*/
    do {
        cont += aux->produto.quantidade;
        printProduto(&(aux->produto));
        aux = aux->proximo;
    } while (aux != estoque->primeiro);
    /*impirme a quantidade de produtos no estoque*/
    cout << "Quantidade de produtos classificados no estoque: " << estoque->tamanho << endl;
    cout << "quantidade de produtos atualmente em estoque: " << cont << endl;
}

int estoqueVazio(Estoque * estoque) {
    /*verfica se o estoque está vazio*/
    return (estoque->primeiro == NULL);
}

Produto * procura(Estoque * estoque, int codigo) {
    /*verifica se o estoque está vazio*/
    if (estoqueVazio(estoque)) {
        return NULL;
    }
    /*se o codigo for maior do que a metade procura pela direita, se for menor procura pela esquerda*/
    if (codigo <= codigo_produto_max / 2) {
        return procuraDireita(estoque, codigo);
    } else {
        return procuraEsquerda(estoque, codigo);
    }
}

Produto * procuraDireita(Estoque * estoque, int codigo) {
    /*verfica se o estoque está vazio*/
    if (estoqueVazio(estoque)) {
        return NULL;
    }
    Nodes * aux;
    aux = estoque->primeiro;
    for (int i = 0; i < estoque->tamanho; i++) {
        if (codigo == aux->produto.codigo) {
            /*se achar retorna o ponteiro do produto*/
            return &(aux->produto);
        }
        aux = aux->proximo;
    }
    /*se não achou o produto retorna null*/
    return NULL;
}

Produto * procuraEsquerda(Estoque * estoque, int codigo) {
    /*verifica se o estoque está vazio*/
    if (estoqueVazio(estoque)) {
        return NULL;
    }
    Nodes * aux;
    aux = estoque->primeiro;
    for (int i = 0; i < estoque->tamanho; i++) {
        if (codigo == aux->produto.codigo) {
            /*retorna o ponteiro do produto caso tenha achado*/
            return &(aux->produto);
        }
        aux = aux->anterior;
    }
    /*retorna vazio caso não tenha achado o produto*/
    return NULL;
}

int removeProduto(Estoque * estoque, int codigo) {
    /* verifica se o estoque está vazio */
    if (estoqueVazio(estoque)) {
        return 0;
    }
    Nodes * aux;
    Nodes * proximo;
    Nodes * anterior;
    aux = estoque->primeiro;
    /* 
     * verifica se o produto que está sendo procurado é o primeiro, se for é 
     * tratado separadamente
     */
    if (codigo == estoque->primeiro->produto.codigo) {
        anterior = aux->anterior;
        proximo = aux->proximo;
        anterior->proximo = proximo;
        proximo->anterior = anterior;
        free((aux));
        estoque->primeiro = proximo;
        estoque->tamanho--;
        /*verifica se não tem mais produtos no estoque então o estoque é definido como vazio*/
        if (estoque->tamanho == 0) {
            estoque->primeiro = NULL;
        }
        return 1;
    }
    if (codigo <= codigo_produto_max / 2) {
        /*percorre o estoque pela direita*/
        while (aux->produto.codigo != codigo) {
            aux = aux->proximo;
            /*caso não ache o produto*/
            if (aux == estoque->primeiro) {
                return 0;
                break;
            }
        }
    } else {
        /*percorre o estoque pela esquerda*/
        while (aux->produto.codigo != codigo) {
            aux = aux->anterior;
            /*caso não ache o produto*/
            if (aux == estoque->primeiro) {
                return 0;
                break;
            }
        }
    }
    /*verfica se o codigo do produto é o desejado*/
    if (aux->produto.codigo == codigo) {
        /*salva os laterais*/
        anterior = aux->anterior;
        proximo = aux->proximo;
        anterior->proximo = proximo;
        proximo->anterior = anterior;
        free((aux));
        /*diminuiu o tamanho do estoque depois de retirar o produto do estoque*/
        estoque->tamanho--;
    }
    /*verifica se o tamanho do estoque está vazio, se estiver o estoque é definido como vazio*/
    if (estoque->tamanho == 0) {
        estoque->primeiro = NULL;
    }
    return 1;
}

void destroiEstoque(Estoque * estoque) {
    Nodes * aux;
    Nodes * aux2;
    aux = estoque->primeiro->proximo;
    /*percorre até voltar para o primeiro item do estoque*/
    while (aux != estoque->primeiro) {
        aux2 = aux->proximo;
        /*libera a memoria do nó*/
        free(aux);
        aux = aux2;
    }
    /*libera a memoria do primeiro elemento do estoque e define o estoque como vazio*/
    free(estoque->primeiro);
    estoque->primeiro = NULL;
    estoque->tamanho = 0;
}

int inserirProduto(Estoque * estoque, int codigo) {
    if (codigo >= codigo_produto_max) {
        return 0;
    }
    Nodes * novo;
    /*verifica se o estoque está vazio, se estiver é recolocado todos os itens do estoque*/
    if (estoqueVazio(estoque)) {
        criaEstoqueVazio(estoque);
        criaEstoque(estoque);
        return 1;
    }
    Nodes * aux;
    aux = estoque->primeiro;
    Nodes * proximo;
    Nodes * anterior;
    /*aloca o novo no*/
    novo = (Nodes *) malloc(sizeof (Nodes));
    if (novo == NULL) {
        (void) fprintf(stderr, "ERRO: Impossivel alocar memoria\n");
        return 0;
    }

    if (codigo <= codigo_produto_max / 2) {
        /*percorre pela direita*/
        while (aux->proximo->produto.codigo <= codigo) {
            /*procura o codigo -> proximo*/
            aux = aux->proximo;
        }
        if (aux->produto.codigo == codigo) {
            //            cout << codigo << " produto já existe, não recadastrado " << endl;
        } else {
            //            cout << codigo << " Recadastrando " << endl;
            /*define os termos do novo produto*/
            anterior = aux->anterior;
            proximo = aux->proximo;
            aux->proximo = novo;
            novo->anterior = aux;
            novo->proximo = proximo;
            proximo->anterior = novo;
        }
    } else {
        /* ando pela esquerda -> anterior */
        while (aux->anterior->produto.codigo >= codigo) {
            aux = aux->anterior;
        }
        if (aux->produto.codigo == codigo) {
            //            cout << codigo << " produto já existe, não recadastrado " << endl;
        } else {
            //            cout << codigo << " Recadastrando " << endl;
            /*define os termos do novo produto*/
            anterior = aux->anterior;
            proximo = aux->proximo;
            aux->anterior = novo;
            novo->proximo = aux;
            novo->anterior = anterior;
            anterior->proximo = novo;
        }
    }
    /*define o produto novo*/
    novo->produto.codigo = codigo;
    novo->produto.quantidade = quantida_produto_padrao;
    novo->produto.valor = preco(codigo);
    return 1;
}

/*******************************************************************************/

void criaRepor(Repor * repor) {
    /*define o repor como vazio*/
    repor->inicio = NULL;
    repor->fim = NULL;
}

int reporVazia(Repor * repor) {
    /*verifica se a fila de repor está vazia*/
    return (repor->fim == NULL && repor->inicio == NULL);
}

int atualizaRepor(Repor * repor, Estoque * estoque) {
    /*verifica se a fila de repor está vazia*/
    if (reporVazia(repor)) {
        return 0;
    }
    Faltante * f;
    Produto produto;
    f = repor->inicio;
    /*percorre enquanto a fila não está vazia*/
    while (f != NULL) {
        /*
         * refica se o tempo de espera é zero, se for remove o produto da fila 
         * de reposição e insere no estoque
         */
        if (f->espera == 0) {
            f = f->proximo;
            removeRepor(repor, &produto);
            inserirProduto(estoque, produto.codigo);
        } else {
            /*diminui o tempo de espera*/
            --(f->espera);
            f = f->proximo;
        }
    }
    return 1;
}

int procuraRepor(Repor * repor, int codigo) {
    /*verifica se a fila de reposição está vazia*/
    if (reporVazia(repor)) {
        return 0;
    }
    Faltante * aux;
    aux = repor->inicio;
    /*procura o codigo enquanto a fila não acabou, se achou retorna 1*/
    while (aux != NULL) {
        if (aux->codigo == codigo) {
            return 1;
        }
        aux = aux->proximo;
    }
    return 0;
}

int adicionaRepor(Repor * repor, int codigo) {
    /*procura o produto na lista de reposição se já existe sai sem acresctentar o produto*/
    if (procuraRepor(repor, codigo)) {
        return 1;
    }
    Faltante * aux;
    aux = (Faltante *) malloc(sizeof (Faltante));
    if (aux == NULL) {
        return 0;
    }
    aux->codigo = codigo;
    aux->espera = tempo_espera;
    aux->proximo = NULL;
    /*verfica se a lista de reposição está vazia*/
    if (reporVazia(repor)) {
        /* se estiver adiciona no inicio*/
        repor->inicio = aux;
    } else {
        /*se não estiver adiciona no fim*/
        repor->fim->proximo = aux;
    }
    /*faz o fim ser igual ao no novo*/
    repor->fim = aux;
    return 1;
}

void printRepor(Repor * repor) {
    /*verifica se a fila de repor está vazia*/
    if (reporVazia(repor)) {
        return;
    }
    Faltante * f;
    f = repor->inicio;
    /*imprime a fila de repor até achar o final da fila*/
    while (f != NULL) {
        cout << "codigo " << f->codigo << endl;
        cout << "tempo de espera " << f->espera << endl;
        f = f->proximo;
    }
}

int removeRepor(Repor * repor, Produto * produto) {
    /*verifaca se a fila de repor está vazia*/
    if (reporVazia(repor)) {
        return 0;
    }
    Faltante * f;
    /*se o inicio for igual ao final,então a fila só tem um termo, definimos final como vazio*/
    if (repor->inicio == repor->fim) {
        repor->fim = NULL;
    }
    /*retira o primeiro elemento da fila*/
    f = repor->inicio;
    produto->codigo = f->codigo;
    repor->inicio = repor->inicio->proximo;
    free(f);
    return 1;
}
