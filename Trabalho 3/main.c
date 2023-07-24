
#include <stdio.h>
#include "avl_tree.c"

void menu(struct no **raiz) {
    
}

int main() {
    int iVal, iRet, RUN = 1;
    char answer;
    struct no *raiz = NULL;

    // printf("Árvore AVL\n");
    // imprime(raiz, 0);
    // inclui(10, raiz, &raiz, 0, 0);
    // imprime(raiz, 0);

    // inclui(5, raiz, &raiz, 0, 0);
    // inclui(15, raiz, &raiz, 0, 0);
    // imprime(raiz, 0);

    printf("Árvore AVL\n");
    while (RUN) {
        printf("Menu (Digite um dos valores para iniciar):\n");
        printf("1. Incluir valor\n");
        printf("2. Excluir valor\n");
        printf("3. Buscar valor\n");
        printf("4. Imprimir árvore\n");
        printf("5. Sair\n");
        scanf(" %c", &answer);

        switch (answer) {
            case '1':
                printf("Digite o valor que deseja inserir: ");
                scanf(" %d", &iVal);
                iRet = inclui(iVal, raiz, &raiz);
                printf("%d\n", iRet);
                if (!iRet) {
                    printf("O varlor já está na árvore\n");
                } else {
                    printf("\nA árvore ficou:\n");
                    imprime(raiz, 0);
                }
                break;
            case '2':
                printf("Digite o valor que deseja excluir: ");
                scanf(" %d", &iVal);
                // exclui(iVal, raiz, &raiz, 0, 0);
                printf("\nA árvore ficou:\n");
                imprime(raiz, 0);
                break;
            case '3':
                printf("Digite o valor que deseja buscar: ");
                scanf(" %d", &iVal);
                if (buscar(raiz, iVal)) {
                    printf("\nO valor foi encontrado\n\n");
                } else {
                    printf("\nO valor não foi encontrado\n\n");
                }
                break;
            case '4':
                printf("\n");
                imprime(raiz, 0);
                printf("\n");
                break;
            case '5':
                printf("Saindo...\n");
                RUN = 0;
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
                break;
        }
    }

    return 0;
}
