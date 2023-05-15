
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float a, b, c, delta, x1, x2;

    printf("Digite a: ");
    scanf("%f", &a);

    printf("Digite b: ");
    scanf("%f", &b);
    
    printf("Digite c: ");
    scanf("%f", &c);

    delta = b*b - 4*a*c;

    if (delta > 0) {
        x1 = (-b + sqrt(delta)) / (2*a);
        x2 = (-b - sqrt(delta)) / (2*a);
        printf("As raízes são %f e %f\n", x1, x2);
    } else {
        if (delta == 0) {
            x1 = -b/(2*a);
            printf("A raiz é %f\n", x1);
        } else {
            printf("Raízes imaginárias\n");
        }
    }

    return 0;
}
