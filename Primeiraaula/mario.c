#include <stdio.h>

int main(void)
{
    int n;

    // Solicitar ao usuário o tamanho da pirâmide
    do
    {
        printf("Tamanho: ");
        scanf("%d", &n);
    }
    while (n < 1 || n > 8); // Enquanto o número for inválido (menor que 1 ou maior que 8)

    // Loop para cada linha da pirâmide
    for (int i = 1; i <= n; i++)
    {
        // Imprimir os espaços antes dos hashes
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");
        }

        // Imprimir os hashes
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // Pular para a próxima linha após terminar a linha atual
        printf("\n");
    }

    return 0;
}
