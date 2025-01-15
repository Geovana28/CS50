#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Declarar variáveis
    char text[1000]; // Supondo que o texto tenha no máximo 999 caracteres
    int letters = 0, words = 1, sentences = 0;

    // Solicitar ao usuário o texto
    printf("Texto: ");
    fgets(text, sizeof(text), stdin); // Usamos fgets para ler a string

    // Percorrer o texto
    for (int i = 0; i < strlen(text); i++)
    {
        // Contar letras
        if (isalpha(text[i]))
        {
            letters++;
        }

        // Contar palavras (palavra é separada por espaço)
        if (text[i] == ' ')
        {
            words++;
        }

        // Contar sentenças (pode ser um ponto, exclamação ou interrogação)
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Calcular L e S para a fórmula de Coleman-Liau
    float L = (float)letters / words * 100; // Letras por 100 palavras
    float S = (float)sentences / words * 100; // Sentenças por 100 palavras

    // Calcular o índice de Coleman-Liau
    int index = (int)(0.0588 * L - 0.296 * S - 15.8);

    // Imprimir o nível de leitura
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }

    return 0;
}
