#include <stdio.h>

int main(void)
{
    char resposta[50]; // Buffer para armazenar a resposta do usuário
    printf("hello, world\n");
    printf("Qual o seu nome? ");
    fgets(resposta, sizeof(resposta), stdin); // Captura a entrada do usuário
    printf("Olá, %s!\n", resposta);
    return 0;
}
