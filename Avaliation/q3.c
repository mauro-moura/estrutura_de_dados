#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int startPos;
int findCommonSubstring(char *X, char *Y) {
    int i, j;
    int m = strlen(X);
    int n = strlen(Y);

    /*  int len[m + 1][n + 1]; */
    int **len;
    int result = 0;
    int row, col;

    len = (int **) malloc((m + 1) * sizeof(int *));
    for (i = 0; i <= m; i++) {
        len[i] = (int *) malloc((n + 1) * sizeof(int));
    }

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                len[i][j] = 0;
            } else {
                if (X[i - 1] == Y[j - 1]) {
                    len[i][j] = len[i - 1][j - 1] + 1;
                    if (len[i][j] > result) {
                        result = len[i][j];
                        row = i;
                        col = j;
                    }
                } else {
                    len[i][j] = 0;
                }
            }
        }
    }

    startPos = row - result;

    return result;
}

int main() {
    int commonLength;
    char X[] = "ASBASBDEASB", Y[] = "ASBASBAOOSB";
    /*
    char X[100], Y[100];
    printf("Digite a primeira string (X): ");
    fgets(X, sizeof(X), stdin);
    X[strcspn(X, "\n")] = '\0';

    printf("Digite a segunda string (Y): ");
    fgets(Y, sizeof(Y), stdin);
    Y[strcspn(Y, "\n")] = '\0';
    */
    commonLength = findCommonSubstring(X, Y);

    printf("Tamanho da maior substring comum: %d\n", commonLength);
    printf("Posição de início em X: %d\n", startPos);

    return 0;
}
