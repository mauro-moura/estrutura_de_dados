
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void print_matrix(int **m, int mlin_len, int mcol_len) {
    int i, j;
    for (i = 0; i < mlin_len; i++) {
        printf("| ");
        for (j = 0; j < mcol_len; j++) {
            printf("%3d ", m[i][j]);
        }
        printf("|\n");
    }
}

void print_matrix_float(float **m, int mlin_len, int mcol_len) {
    int i, j;
    for (i = 0; i < mlin_len; i++) {
        printf("| ");
        for (j = 0; j < mcol_len; j++) {
            printf("%6.2f ", m[i][j]);
        }
        printf("|\n");
    }
}

float calculate_mean_neighbor(float **m, int i, int j, int mlin_len, int mcol_len) {
    /*
    Calculate the mean of 4 neighbors in a matrix considering corners of matrix.
    */
    float v1 = 0, v2 = 0, v3 = 0, v4 = 0, average = 0;

    if (i != (mlin_len - 1)) {
        v1 = m[i + 1][j];
    }
    if (i != 0) {
        v2 = m[i - 1][j];
    }
    if (j != (mcol_len - 1)) {
        v3 = m[i][j + 1];
    }
    if (j != 0) {
        v4 = m[i][j - 1];
    }
    
    average = (v1 + v2 + v3 + v4) / 4.0;

    return average;
}

float ** allocate_matrix(int rows, int cols) {
    int i;
    float **matrix = (float **) malloc(rows * sizeof(float*));
    for (i = 0; i < rows; i++) {
        matrix[i] = (float *) malloc(cols * sizeof(float));
    }

    return matrix;
}

void fill_matrix(float ** matrix, int ** m, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = 0.0;
            if (m[i][j] == 2) {
                matrix[i][j] = 100;
            }
        }
    }
}

float ** calculate_polution(int **m, int rows, int cols, float error) {
    /* Calculate polution given a matrix */
    int i, j;
    float **m_base, **m_out, **m_aux;
    float p, diff, max_diff = 25;
    
    m_base = allocate_matrix(rows, cols);
    fill_matrix(m_base, m, rows, cols);
    m_out = allocate_matrix(rows, cols);
    fill_matrix(m_out, m, rows, cols);

    while (max_diff > error) {
        m_aux = m_base;
        m_base = m_out;
        m_out = m_aux;

        max_diff = 0;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                if (m[i][j] != 0 && m[i][j] != 2) {
                    p = calculate_mean_neighbor(m_base, i, j, rows, cols);
                    m_out[i][j] = p;
                    diff = m_out[i][j] - m_base[i][j];
                    if (diff > max_diff) {
                        max_diff = diff;
                    }
                }
            }
        }
        printf("\nMax Diff: %f\n", max_diff);
        print_matrix_float(m_out, rows, cols);
        sleep(1);
    }
    return m_out;
}

void split_str(char *str) {
    /* Remove spaces between string */
    int len = strlen(str);
    int i, j = 0;

    for (i = 0; i < len; i++) {
        if (!isspace(str[i])) {
            str[j++] = str[i];
        } 
    }

    str[j] = '\0';
}

int main() {
    /*
    Dada uma matriz onde 0: Água, 1: Terra, 2: Gerador
    Calcular a taxa de espalhamento de óleo
    O gerador sempre estará em 100
    A água sempre estará em 0
    */

    int i, j, rows, cols;
    char c_error[256];
    float error;

    char path[256];
    char temp[256];

    int **matrix;
    float **out_m;

    FILE *file_in;

    printf("Digite o nome do arquivo que contém uma martiz: ");
    scanf("%s", path);

    printf("Digite o valor do erro: ");
    scanf("%s", c_error);
    error = atof(c_error);

    printf("Arquivo selecionado: %s, Erro Selecionado: %f\n", path, error);

    file_in = fopen(path, "r");

    if (file_in == NULL) {
        printf("Arquivo não existe");
        exit(1);
    }

    fgets(temp, sizeof(temp), file_in);
    rows = atoi(temp);

    fgets(temp, sizeof(temp), file_in);
    cols = atoi(temp);

    printf("Lines: %i Cols: %i\n", rows, cols);
    matrix = (int **) malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    for (i = 0; i < rows; i++) {
        fgets(temp, sizeof(temp), file_in);
        split_str(temp);
        for (j = 0; j < cols; j++) {
            switch (temp[j]) {
                case '0':
                    matrix[i][j] = 0;
                    break;
                case '1':
                    matrix[i][j] = 1;
                    break;
                case '2':
                    matrix[i][j] = 2;
                    break;
            }
        }
    }

    fclose(file_in);

    printf("Initial Island\n");
    print_matrix(matrix, rows, cols);

    out_m = calculate_polution(matrix, rows, cols, error);

    printf("Final Island\n");
    print_matrix_float(out_m, rows, cols);

    free(matrix);
    free(out_m);

    return 0;
}
