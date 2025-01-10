#include <stdio.h>
#include <math.h>

int main(void)
{
    float reais;
    
    // Obter o valor do troco
    do
    {
        printf("Troca devida: ");
        scanf("%f", &reais);
    } while (reais < 0);

    // Converter o valor para centavos
    int centavos = round(reais * 100);

    // Definir as moedas disponíveis (25, 10, 5 e 1 centavo)
    int moedas[] = {25, 10, 5, 1};
    int num_moedas = 0;

    // Calcular o número mínimo de moedas
    for (int i = 0; i < 4; i++)
    {
        // Verificar quantas vezes podemos usar a moeda i
        while (centavos >= moedas[i])
        {
            centavos -= moedas[i];
            num_moedas++;
        }
    }

    // Imprimir o número mínimo de moedas
    printf("%d\n", num_moedas);

    return 0;
}
