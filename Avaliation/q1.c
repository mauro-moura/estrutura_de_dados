
#include <stdio.h>
#include <stdlib.h>

struct no {
    int iVal;
    struct no *prox;
};

int empilha(int iVal, struct no **inicio) {
    struct no *aux;
    aux = (struct no *) malloc(sizeof(struct no));
    if (!aux) return -1;
    aux->iVal = iVal;
    aux->prox = *inicio;
    *inicio = aux;
    return 0;
}

int desempilha(int *piVal, struct no *inicio, struct no **raiz) {
    struct no *aux;
    if (!inicio) return -1;
    aux = inicio;
    *raiz = inicio->prox;
    *piVal = aux->iVal;
    free(aux);
    return 0;
}

void imprime(struct no *inicio) {
    struct no *aux;
    printf("-");
    for (aux = inicio; aux; aux = aux->prox) {
        printf(" %d ", aux->iVal);
    }
    printf("\n");
}

void resolucao(struct no *lista) {
    int iVal;
    struct no *pilha = NULL;
    struct no *aux;

    for (aux = lista; aux != NULL; aux = aux->prox) {
        empilha(aux->iVal, &pilha);
    }
    
    for (aux = lista; aux != NULL; aux = aux->prox) {
        desempilha(&iVal, pilha, &pilha);
        aux->iVal = iVal;
    }
}

int main() {
    struct no *lista = NULL;

    empilha(3, &lista);
    empilha(2, &lista);
    empilha(1, &lista);

    printf("Lista Original\n");
    imprime(lista);

    resolucao(lista);

    printf("Lista depois da resolução\n");
    imprime(lista);

}
