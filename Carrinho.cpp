#include "Carrinho.h"
#include "estoque.h"
#include "utiil.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

int carrinhoVazio(Carrinho * carrinho) {
    /*verifica se o carrinho está vazio*/
    return (carrinho->pilha == NULL);
}

void criaCarrinho(Carrinho * carrinho) {
    /*cria um carrinho vazio*/
    carrinho->pilha = NULL;
    carrinho->tamanho = 0;
}

int carrinhoPush(Carrinho * carrinho, Produto * produto, int quantidade) {
    /*cria um novo nó de carrinho e verifica se foi alocada a memoria, se não foi retorna erro*/
    Nodec * novo;
    novo = (Nodec *) malloc(sizeof (Nodec));
    if (novo == NULL) {
        (void) fprintf(stderr, "ERRO: Impossivel alocar no item em carrinho.\n");
        return 0;
    }
    /*salva os dados novos no nó criado*/
    novo->produto.codigo = produto->codigo;
    novo->produto.valor = produto->valor;
    novo->produto.quantidade = quantidade;
    /*verifica se o carrinho está vazio se estiver o nó anterior da pilha é definido como vazio*/
    if (carrinhoVazio(carrinho)) {
        novo->proximo = NULL;
    } else {
        novo->proximo = carrinho->pilha;
    }
    /*define a onó novo como topo da pilha e aumenta o tamanho da pilha*/
    carrinho->pilha = novo;
    carrinho->tamanho++;
    return 1;
}

int carrinhoPop(Carrinho * carrinho, Produto * produto) {
    /*verifica se o carrinho está vazio*/
    if (carrinhoVazio(carrinho)) {
        return 0;
    }
    Nodec * aux;
    aux = carrinho->pilha;
    /*recupera o produto do alto da pilha do carrinho*/
    *produto = carrinho->pilha->produto;
    carrinho->pilha = aux->proximo;
    /*libera o espaço alocado do produto do alto do carrinho*/
    free(aux);
    /*diminui o tamanho do carrinho*/
    carrinho->tamanho--;
    return 1;
}

int carrinhoStackPop(Carrinho * carrinho, Produto * produto) {
    /*verifica se o carrinho está vazio*/
    if (carrinhoVazio(carrinho)) {
        return 0;
    }
    /*recupera o produto do alto do carrinnho*/
    *produto = carrinho->pilha->produto;
    return 1;
}

void printCarrinho(Carrinho * carrinho) {
    /*verifica se o carrinho  está vazio*/
    if (carrinhoVazio(carrinho)) {
        cout << "carrinho vazio" << endl;
        return;
    }
    /*percorre todos os nós do carrinho*/
    Nodec * aux;
    aux = carrinho->pilha;
    while (aux != NULL) {
        /*imprime os produtos do carrinho*/
        printProduto(&(aux->produto));
        aux = aux->proximo;
    }
    return;
}

int escolheProdutos(Carrinho * carrinho, Estoque * estoque, int quantidade, Repor * repor) {
    Produto * produto;
    /*codigo do produto que será comprado*/
    int codigo_produto;
    /*quantidade  de produto que será comprado*/
    int quantidade_produto;
    int tentativas = 25;
    /*enquanto a quantidade de produtos não for alcançada o cliente oontinua comprando*/
    while (quantidade > 0) {
        /*escole o produto*/
        codigo_produto = aleatorio(codigo_produto_max, 0);
        /*procura o produto*/
        produto = procura(estoque, codigo_produto);
        if (produto == NULL) {
            /*produt inexistente, tem que salvar para comprar depois*/
            //            cout << "produto em falta " << codigo_produto << endl;
            /*se não achar o produto reduz a quantidade de tentativas*/
            tentativas--;
            adicionaRepor(repor, codigo_produto);
        } else {
            /*escolhe a quantidade de produto*/
            quantidade_produto = aleatorio(quantida_produto_padrao, 1);
            /*
             * verifica se a quantidade de produtos escolhido é maior do que a 
             * quantidade de produtos que o cliente ainda pode comprar
             */
            if (quantidade_produto > quantidade) {
                quantidade_produto = quantidade;
            }
            /*
             * verifica se a quantidade do produtos escolhido é maior do que a 
             * desejada
             */
            if (quantidade_produto < produto->quantidade) {
                carrinhoPush(carrinho, produto, quantidade_produto);
                produto->quantidade -= quantidade_produto;
                quantidade -= quantidade_produto;
            } else {
                /*
                 * se for escolhido mais produtoo do que a quantidade em estoque, 
                 * o produto é removido do estoque
                 */
                carrinhoPush(carrinho, produto, produto->quantidade);
                quantidade -= produto->quantidade;
                removeProduto(estoque, codigo_produto);
            }
        }
        /*caso tenha procurado varios produtos e não conseguiu achar, verifica se o cliente conseguiu ou não compra algo*/
        if (tentativas <= 0) {
            if (carrinhoVazio(carrinho)) {
                return 0;
            } else {
                return 1;
            }
        }
    }
    /*retorna true*/
    return 1;
}

Produto * primeiroCarrinho(Carrinho * carrinho) {
    /*verifica se o carrinho está vazio, se estiver volta pontiero para NULL*/
    if (carrinhoVazio(carrinho)) {
        return NULL;
    }
    /*retorn o ponteiro para carrinho*/
    return &(carrinho->pilha->produto);
}
