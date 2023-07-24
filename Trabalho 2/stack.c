
struct no {
    int iVal;
    struct no *prox;
};

void imprime_val(struct no *n) {
  if (!n) return;

  imprime_val(n->prox);
  printf(" %d ", n->iVal);
}

void imprime(struct no *inicio) {
    printf("-");
    imprime_val(inicio);
    printf("\n");
}

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
