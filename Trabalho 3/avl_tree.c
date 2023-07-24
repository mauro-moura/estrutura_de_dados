
/* Included because of NULL */
#include <stdio.h>
/* Included because of malloc */
#include <stdlib.h>

/* We define the values of the path for each node
Using this define instead of the intergers
To we track the last two positions*/

#define DIR 1
#define ESQ -1
#define IND 0

struct no {
    int iVal;
    int iAD;
    int iAE;
    struct no *dir;
    struct no *esq;
};

void imprime(struct no *n, int iAlt) {
    int i;
    if (!n) return;
    imprime(n->dir, iAlt + 1);
    for (i = 0; i < iAlt; i++){
        printf("   ");
    }
    printf("%d (%d, %d)\n", n->iVal, n->iAD, n->iAE);
    imprime(n->esq, iAlt +1);
}

struct no* buscar(struct no * raiz, int iVal) {
    if (!raiz) return raiz;
    if (raiz->iVal == iVal) return raiz;
    if (raiz->iVal > iVal) {
        return buscar(raiz->esq, iVal);
    }
    return buscar(raiz->dir, iVal);
}

struct no* buscarMinimo(struct no* n) {
    if (n == NULL)
        return NULL;
    
    if (n->esq != NULL)
        buscarMinimo(n->esq);
    
    return n;
}

int altura(struct no* n) {
    if (n == NULL)
        return 0;
    int alturaEsq = altura(n->esq);
    int alturaDir = altura(n->dir);
    return (alturaEsq > alturaDir) ? alturaEsq + 1 : alturaDir + 1;
}

void RE(struct no *A, struct no *B, struct no **pai){
    struct no *temp;
    temp = B->esq;
    B->esq = A;
    A->dir = temp;
    *pai = B;

    A->iAE = altura(A->esq);
    A->iAD = altura(A->dir);

    B->iAE = altura(B->esq);
    B->iAD = altura(B->dir);
}

void RD(struct no *A, struct no *B, struct no **pai){
    struct no *temp;
    temp = B->dir;
    B->dir = A;
    A->esq = temp;
    *pai = B;

    A->iAE = altura(A->esq);
    A->iAD = altura(A->dir);

    B->iAE = altura(B->esq);
    B->iAD = altura(B->dir);
}

int inclui(int iVal, struct no *n, struct no **pai) {
    /*
    Return Values
    -1  We get to the leafs
     0  We found the value in the three, not adding it
    10 Not able to allocate
    -3  OK
    */
    int iRet;
    struct no *aux;
    static int iUlt = IND, iPen = IND;

    if (!n) {
        if (iUlt == IND && iPen == IND) {  /* Empty Tree */
            aux = (struct no *) malloc(sizeof(struct no));
            if (!aux) {
                return 10;
            }
            aux->iVal = iVal;
            aux->dir = aux->esq = NULL;
            aux->iAE = aux->iAD = 0;
            *pai = aux;
            return -3;
        }
        return -1;
    }
    if (n->iVal == iVal) {
        return 0;
    }

    if (iVal > n->iVal) {
        iPen = iUlt;
        iUlt = DIR;
        iRet = inclui(iVal, n->dir, &n->dir);
    } else {
        iPen = iUlt;
        iUlt = ESQ;
        iRet = inclui(iVal, n->esq, &n->esq);
    }

    if (!iRet || iRet == 10) { /* Valor já existe */
        return iRet;
    }

    if (iRet == -1) { /* Valor será incluído */
        printf("Including in the tree\n");
        aux = (struct no *) malloc(sizeof(struct no));
        if (!aux) return 10;
        aux->iVal = iVal;
        aux->dir = aux->esq = NULL;
        aux->iAE = aux->iAD = 0;

        if (iVal > n->iVal) {
            n->dir = aux;
            n->iAD = 1;
        } else {
            n->esq = aux;
            n->iAE = 1;
        }
    }

    if (iRet == -1 || iRet == -2) {
        n->iAE = altura(n->esq);
        n->iAD = altura(n->dir);
        
        if (n->iAD == n->iAE) {
            /* Inclusão ocorreu, mas não precisa modificar altura */
            printf("Não precisa modificar altura\n");
            return -3;
        } else if (abs(n->iAD - n->iAE) == 1) {
            /* Inclusão ocorreu e precisa ajustar a altura */
            printf("Inclusão ocorreu e precisa ajustar a altura\n");
            return -2;
        } else {
            /* Balanceamento Ocorrendo */
            printf("Balanceamento Ocorrendo\n");
            if (iUlt == DIR) {
                if (iPen == DIR) {
                    /* DD -> RE */
                    RE(n, n->dir, pai);
                } else {
                    /* DE -> RE + RD */
                    RE(n->esq, n->esq->dir, &n->esq);
                    RD(n, n->esq, pai);
                }
            } else {
                if (iPen == ESQ) {
                    /* EE -> RD */
                    RD(n, n->esq, pai);
                } else {
                    /* ED -> RD + RE */
                    RD(n->dir, n->dir->esq, &n->dir);
                    RE(n, n->dir, pai);
                }
            }
        }
    }
    return -3;
}

/*
int excluir(int iVal, struct no * n, struct no **pai) {
    struct no * aux;
    int iRet, fatorBalanceamento;

    if (!n) {
        return -1;
    }


    if (iVal > n->iVal) {
        iRet = excluir(iVal, n->dir, &n->dir);
    } else if (iVal < n->iVal) {
        iRet = excluir(iVal, n->esq, &n->esq);
    } else {
        if (!n->dir || !n->esq) {
            struct no * temp = n->esq ? n->esq: n->dir;

            if (temp == NULL) {
                temp = n;
                n = NULL;
            } else {
                *n = *temp;
            }

            free(temp);
        } else {
            struct no * temp = buscaMinimo(n->dir);
            n->iVal = temp->iVal;
            n->dir = excluir(temp->iVal, n->dir, &n);
            n->iAD = altura(n->dir);
        }
        free(n);
    }

    if (iRet == -1) {
        return iRet;
    }

    if (iRet == -3) {
        n->iAE = altura(n->esq);
        n->iAD = altura(n->dir);
        fatorBalanceamento = altura(n->esq) - altura(n->dir);
        if (fatorBalanceamento > 1) {
            int fatorBalanceamentoFilho = altura(n->esq->esq) - altura(n->esq->dir);
            if (fatorBalanceamentoFilho >= 0) {
                RE(n, n->esq, pai);
            } else {
                n->esq = rotacaoEsquerda(n->esq);
                RE(n, n->esq, pai);
            }
            n = *pai;
        }
        if (fatorBalanceamento < -1) {
            int fatorBalanceamentoFilho = altura(n->dir->esq) - altura(n->dir->dir);
            if (fatorBalanceamentoFilho <= 0) {
                RD(n, n->dir, pai);
            } else {
                n->dir = rotacaoDireita(n->dir);
                RD(n, n->dir, pai);
            }
            n = *pai;
        }
    }
}
*/

int excluir(int iVal, struct no* n, struct no** pai) {
    /*
    Return Values
     0: Value not found
    -1: Node excluded (leaf)
    -3: Node excluded
    */
    struct no* temp;
    int iRet;
    if (n == NULL)
        return 0;

    if (iVal < n->iVal) {
        iRet = excluir(iVal, n->esq, &n);
        if (iRet == -3) {
            n->iAE = altura(n->esq);
            n->iAD = altura(n->dir);
            int fatorBalanceamento = n->iAE - n->iAD;
            if (fatorBalanceamento < -1) {
                int fatorBalanceamentoFilho = (n->dir == NULL) ? 0 : (n->dir->iAE - n->dir->iAD);
                if (fatorBalanceamentoFilho > 0)
                    RD(n, n->dir, pai);
                RE(n, n->dir, pai);
                n = *pai;
            }
        }
        return iRet;
    } else if (iVal > n->iVal) {
        iRet = excluir(iVal, n->dir, &n);
        if (iRet == -3) {
            n->iAE = altura(n->esq);
            n->iAD = altura(n->dir);
            int fatorBalanceamento = n->iAE - n->iAD;
            if (fatorBalanceamento > 1) {
                int fatorBalanceamentoFilho = (n->esq == NULL) ? 0 : (n->esq->iAE - n->esq->iAD);
                if (fatorBalanceamentoFilho < 0)
                    RE(n, n->esq, pai);
                RD(n, n->esq, pai);
                n = *pai;
            }
        }
        return iRet;
    } else {
        if (n->esq == NULL && n->dir == NULL) {
            free(n);
            *pai = NULL;
            return -1;
        } else if (n->esq == NULL) {
            temp = n->dir;
            *n = *temp;
            free(temp);
            return -3;
        } else if (n->dir == NULL) {
            temp = n->esq;
            *n = *temp;
            free(temp);
            return -3;
        } else {
            temp = buscarMinimo(n->dir);
            n->iVal = temp->iVal;
            iRet = excluir(temp->iVal, n->dir, &n);
            if (iRet == -3) {
                n->iAE = altura(n->esq);
                n->iAD = altura(n->dir);
                int fatorBalanceamento = n->iAE - n->iAD;
                if (fatorBalanceamento > 1) {
                    int fatorBalanceamentoFilho = (n->esq == NULL) ? 0 : (n->esq->iAE - n->esq->iAD);
                    if (fatorBalanceamentoFilho < 0)
                        RE(n, n->esq, pai);
                    RD(n, n->esq, pai);
                    n = *pai;
                }
            }
            return iRet;
        }
    }
}
