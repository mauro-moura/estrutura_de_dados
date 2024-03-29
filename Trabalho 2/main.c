
#include <stdio.h>
#include <stdlib.h>

#include "stack.c"

int counter = 0;

void imprime_hanoi(struct no *source, struct no *aux, struct no *dest) {
  printf("\nNúmero de Iterações: %d\n", counter);
  imprime(source);
  imprime(aux);
  imprime(dest);
}

void move_tower(struct no **source, struct no **dest) {
  int iVal;
  counter++;
  desempilha(&iVal, *source, source);
  empilha(iVal, dest);
}

void hanoi_tower(int disk_numbers, struct no **source, struct no **aux, struct no **dest) {
    if (disk_numbers == 1) {
        move_tower(source, dest);
        imprime_hanoi(*source, *aux, *dest);
        return;
    }
    hanoi_tower(disk_numbers - 1, source, dest, aux);
    move_tower(source, dest);
    imprime_hanoi(*source, *aux, *dest);
    hanoi_tower(disk_numbers - 1, aux, source, dest);
    return;
}

int main() {
  struct no *source, *aux, *dest;
  int i, disk_numbers;
  char cdisk_numbers[10];

  printf("Bem vindo ao código que resolve a torre de Hanoi.\nDigite o número de discos: ");
  fgets(cdisk_numbers, sizeof(char) * 10, stdin);
  disk_numbers = atoi(cdisk_numbers);

  for (i = disk_numbers; i > 0; i--) {
    empilha(i, &source);
  }

  printf("\nTorre Inicial\n");
  imprime_hanoi(source, aux, dest);

  hanoi_tower(disk_numbers, &source, &aux, &dest);
  printf("\nTorre Final\n");
  imprime_hanoi(source, aux, dest);

  /*
  struct no *raiz;
  int iVal;
  imprime(raiz);

  empilha(10, &raiz);
  imprime(raiz);

  empilha(20, &raiz);
  imprime(raiz);

  empilha(30, &raiz);
  imprime(raiz);

  desempilha(&iVal, raiz, &raiz);
  imprime(raiz);

  desempilha(&iVal, raiz, &raiz);
  imprime(raiz);
  */
}

