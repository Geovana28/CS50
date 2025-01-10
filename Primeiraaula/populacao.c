#include <stdio.h>

int main(void)
{
    int tamanho_inicial, tamanho_final, anos = 0;

    // Solicitar o valor inicial da população
    do
    {
        printf("Tamanho inicial: ");
        scanf("%d", &tamanho_inicial);
    } while (tamanho_inicial < 9); // Verifica se o tamanho inicial é maior ou igual a 9

    // Solicitar o valor final da população
    do
    {
        printf("Tamanho final: ");
        scanf("%d", &tamanho_final);
    } while (tamanho_final < tamanho_inicial); // Verifica se o tamanho final é maior ou igual ao tamanho inicial

    // Calcular o número de anos até que a população atinja o tamanho final
    while (tamanho_inicial < tamanho_final)
    {
        // A cada ano, a população cresce de acordo com as regras dadas
        tamanho_inicial = tamanho_inicial + tamanho_inicial / 3 - tamanho_inicial / 4;
        anos++; // Incrementa o número de anos
    }

    // Imprimir o número de anos necessários
    printf("Anos: %d\n", anos);

    return 0;
}
