#include "utiil.h"
#include <stdlib.h>
/**
 * Função @aleatorio gera um numero aleatroio entre o maximo e o minimo
 * @param @maximo Valor máximo a ser gerado
 * @param @minimo valor minimo a ser gerado
 * @return um numero inteiro.
 */
int aleatorio(int maximo, int minimo) {
    return rand() % (maximo) + minimo;
}
