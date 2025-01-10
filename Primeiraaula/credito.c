#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_digit_sum(int number);
int is_valid_card(long card_number);
int get_card_length(long card_number);

int main(void)
{
    // Solicitar o número do cartão de crédito
    char card_str[20];
    printf("Número do cartão: ");
    fgets(card_str, 20, stdin);

    // Remover o caractere de nova linha
    card_str[strcspn(card_str, "\n")] = '\0';

    // Verificar se a entrada é válida (somente números)
    for (int i = 0; i < strlen(card_str); i++)
    {
        if (card_str[i] < '0' || card_str[i] > '9')
        {
            printf("INVALID\n");
            return 1;
        }
    }

    // Converter o número de cartão de string para long
    long card_number = atol(card_str);

    // Verificar se o número do cartão é válido usando o algoritmo de Luhn
    if (!is_valid_card(card_number))
    {
        printf("INVALID\n");
        return 1;
    }

    // Identificar o tipo de cartão
    int length = get_card_length(card_number);
    int first_two_digits = card_number / (long)pow(10, length - 2);
    int first_digit = card_number / (long)pow(10, length - 1);

    // Verificar o tipo de cartão
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// Função para verificar se o cartão é válido de acordo com o algoritmo de Luhn
int is_valid_card(long card_number)
{
    int sum = 0;
    int is_second_digit = 0;
    while (card_number > 0)
    {
        int digit = card_number % 10;
        card_number /= 10;

        // Se for um dígito na posição ímpar (contando da direita para a esquerda)
        if (is_second_digit)
        {
            digit *= 2;
            sum += get_digit_sum(digit);
        }
        else
        {
            sum += digit;
        }

        // Alternar a posição dos dígitos
        is_second_digit = !is_second_digit;
    }

    // Se a soma total for divisível por 10, o número do cartão é válido
    return sum % 10 == 0;
}

// Função para retornar a soma dos dígitos de um número
int get_digit_sum(int number)
{
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

// Função para obter o comprimento do número do cartão
int get_card_length(long card_number)
{
    int length = 0;
    while (card_number > 0)
    {
        card_number /= 10;
        length++;
    }
    return length;
}
