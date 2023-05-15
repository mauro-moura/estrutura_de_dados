
#include <stdio.h>
#include <stdlib.h>

struct node {
    int iVal;
    struct node *pProx;
} *pIni = NULL;

void print_list(struct node *pIni) {
    struct node *pAux;
    for (pAux = pIni; pAux; pAux = pAux->pProx) {
        printf("%5d->", pAux->iVal);
    }
    printf("\n");
    return;
}

int search() {

}

int include(struct node **pIni, int iVal) {
    struct node *pAux, *pAux2, *pAux3;

    for (pAux = *pIni, pAux2 = NULL;
         pAux && pAux->iVal < iVal;
         pAux2 = pAux, pAux = pAux->pProx
        );
    
    if (pAux && pAux->iVal == iVal) {
        printf("Item already eixsts");
        return 1;
    }

    pAux3 = (struct node *) malloc(sizeof(struct node));
    if (!pAux3) {
        printf("Not possible to allocate");
        return -1;
    }

    pAux3->iVal = iVal;
    pAux3->pProx = pAux;

    if (!pAux2) {
        *pIni = pAux3;
    } else {
        pAux2->pProx = pAux3;
    }
    return 0;
}

int exclude(struct node **pIni, int iVal) {
    struct node *pAux;
    for (pAux = *pIni; pAux && pAux->iVal < iVal; pAux = pAux->pProx);

    if (pAux && pAux->iVal == iVal) {
        
    }
}

int main() {
    print_list(pIni);
    include(&pIni, 10);
    print_list(pIni);

    return 0;
}
