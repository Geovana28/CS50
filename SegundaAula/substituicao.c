#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int main(int argc, char *argv[]) {
    // Verifica se a quantidade de argumentos está correta
    if (argc != 2) {
        printf("Uso: ./substitution chave de substituição\n");
        return 1;
    }

    char *key = argv[1];

    // Verifica se a chave tem 26 caracteres
    if (strlen(key) != ALPHABET_SIZE) {
        printf("A chave deve conter 26 caracteres.\n");
        return 1;
    }

    // Verifica se todos os caracteres da chave são alfabéticos
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (!isalpha(key[i])) {
            printf("A chave deve conter apenas caracteres alfabéticos.\n");
            return 1;
        }
    }

    // Solicita o texto simples
    printf("texto simples: ");
    char text[1000];
    fgets(text, sizeof(text), stdin);

    // Criptografa o texto simples
    printf("texto cifrado: ");
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            // Substitui a letra maiúscula
            printf("%c", toupper(key[text[i] - 'A']));
        } else if (islower(text[i])) {
            // Substitui a letra minúscula
            printf("%c", tolower(key[text[i] - 'a']));
        } else {
            // Se não for letra, mantém o caractere original
            printf("%c", text[i]);
        }
    }

    printf("\n");
    return 0;
}
