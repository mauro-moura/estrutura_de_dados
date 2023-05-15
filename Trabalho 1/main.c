
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
    for (int i = 0; i < mlin_len; i++) {
        printf("| ");
        for (int j = 0; j < mcol_len; j++) {
            printf("%3d ", m[i][j]);
        }
        printf("|\n");
    }
}

void print_matrix_float(float **m, int mlin_len, int mcol_len) {
    for (int i = 0; i < mlin_len; i++) {
        printf("| ");
        for (int j = 0; j < mcol_len; j++) {
            printf("%6.2f ", m[i][j]);
        }
        printf("|\n");
    }
}

float calculate_mean_neighbor(float **m, int i, int j, int mlin_len, int mcol_len) {
    /*
    Calculate the mean of 4 neighbors in a matrix considering corners of matrix.
    */
    float v1 = 0, v2 = 0, v3 = 0, v4 = 0;

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
    
    float average = (v1 + v2 + v3 + v4) / 4.0;

    return average;
}

float ** allocate_matrix(int rows, int cols) {
    float **matrix = (float **) malloc(rows * sizeof(float*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float *) malloc(cols * sizeof(float));
    }

    return matrix;
}

void fill_matrix(float ** matrix, int ** m, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0.0;
            if (m[i][j] == 2) {
                matrix[i][j] = 100;
            }
        }
    }
}

void copy_matrix(float ** dst, float ** src, int mlin_len, int mcol_len) {
    for (int i = 0; i < mlin_len; i++) {
        for (int j = 0; j < mcol_len; j++) {
            dst[i][j] = src[i][j];
    }
  }
}

float ** calculate_polution(int **m, int rows, int cols, float error) {
    /* Calculate polution given a matrix */
    float **m_base, **m_out, **m_aux;
    float p, diff, max_diff = 25;
    
    m_base = allocate_matrix(rows, cols);
    fill_matrix(m_base, m, rows, cols);
    m_out = allocate_matrix(rows, cols);
    fill_matrix(m_out, m, rows, cols);

    while (max_diff > error) {
        /* Old version, copying matrix
        copy_matrix(m_base, m_out, rows, cols);
        fill_matrix(m_out, m, rows, cols);
        */
        m_aux = m_base;
        m_base = m_out;
        m_out = m_aux;

        max_diff = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
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
    int j = 0;

    for (int i = 0; i < len; i++) {
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

    int rows, cols;
    char c_error[256];
    /* float error = 1; */

    char path[256] = "./matrices/";
    char filename[256];
    /* char filename[256] = "matriz.txt"; */

    int **matrix;
    float **out_m;

    printf("Digite o nome do arquivo (Dentro da pasta ./matrices/): ");
    scanf("%s", filename);
    strcat(path, filename);

    printf("Digite o valor do erro: ");
    scanf("%s", c_error);
    float error = atof(c_error);

    printf("Arquivo selecionado: %s, Erro Selecionado: %f\n", path, error);

    FILE *file_in;
    file_in = fopen(path, "r");

    if (file_in == NULL) {
        printf("Arquivo não existe");
        exit(1);
    }

    char temp[256];
    fgets(temp, sizeof(temp), file_in);
    rows = atoi(temp);

    fgets(temp, sizeof(temp), file_in);
    cols = atoi(temp);

    printf("Lines: %i Cols: %i\n", rows, cols);
    matrix = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        fgets(temp, sizeof(temp), file_in);
        split_str(temp);
        for (int j = 0; j < cols; j++) {
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
