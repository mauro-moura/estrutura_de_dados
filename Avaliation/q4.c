#include <stdio.h>
#include <stdlib.h>

// Definição de um nó da árvore
typedef struct Node {
    int data;
    int iAE;
    int iAD;
    struct Node* left;
    struct Node* right;
} Node;

// Função auxiliar para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para calcular a altura de uma árvore
int height(Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Função para verificar se uma árvore está equilibrada
int isTreeBalanced(Node* root) {
    if (root == NULL)
        return 1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (abs(leftHeight - rightHeight) <= 1 &&
        isTreeBalanced(root->left) &&
        isTreeBalanced(root->right)) {
        return 1;
    }

    return 0;
}

int main() {
    // Exemplo de árvore equilibrada
    Node* root1 = createNode(1);
    root1->left = createNode(2);
    root1->right = createNode(3);
    root1->left->left = createNode(4);
    root1->left->right = createNode(5);

    printf("Árvore 1 está equilibrada? %s\n", isTreeBalanced(root1) ? "Sim" : "Não");

    // Exemplo de árvore não equilibrada
    Node* root2 = createNode(1);
    root2->left = createNode(2);
    root2->right = createNode(3);
    root2->left->left = createNode(4);
    root2->left->right = createNode(5);
    root2->left->left->left = createNode(6);

    printf("Árvore 2 está equilibrada? %s\n", isTreeBalanced(root2) ? "Sim" : "Não");

    return 0;
}