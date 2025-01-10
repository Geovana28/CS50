#include <stdio.h>

int main(void)
{
    int n;

    // Solicita ao usuário um número entre 1 e 8
    do {
        printf("Tamanho: ");
        scanf("%d", &n);
    } while (n < 1 || n > 8);  // Verifica se o número está entre 1 e 8

    // Loop para cada linha da pirâmide
    for (int i = 1; i <= n; i++)
    {
        // Primeiro loop: imprime os espaços à esquerda para a parte da pirâmide crescente
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");  // Imprime os espaços
        }

        // Segundo loop: imprime os hashes à esquerda
        for (int j = 0; j < i; j++)
        {
            printf("#");  // Imprime o hash
        }

        // Imprime o espaço entre a pirâmide esquerda e direita
        printf("  ");

        // Terceiro loop: imprime os hashes à direita
        for (int j = 0; j < i; j++)
        {
            printf("#");  // Imprime o hash à direita
        }

        // Vai para a próxima linha
        printf("\n");
    }

    return 0;
}
