#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    // Verificar se a chave foi fornecida
    if (argc != 2)
    {
        printf("Uso: ./caesar chave\n");
        return 1;
    }

    // Verificar se a chave é um número
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]) && argv[1][i] != '-')
        {
            printf("Uso: ./caesar chave\n");
            return 1;
        }
    }

    int chave = atoi(argv[1]);  // Converter a chave para inteiro

    // Ler o texto simples
    char texto_plano[100];
    printf("Texto simples: ");
    fgets(texto_plano, sizeof(texto_plano), stdin);

    // Exibir o texto cifrado
    printf("Texto cifrado: ");

    // Processar cada caractere do texto
    for (int i = 0; texto_plano[i] != '\0'; i++)
    {
        char c = texto_plano[i];

        // Codificar letras maiúsculas
        if (isupper(c))
        {
            printf("%c", (c - 'A' + chave) % 26 + 'A');
        }
        // Codificar letras minúsculas
        else if (islower(c))
        {
            printf("%c", (c - 'a' + chave) % 26 + 'a');
        }
        else
        {
            // Caractere não alfabético (não altera)
            printf("%c", c);
        }
    }

    printf("\n");
    return 0;
}
