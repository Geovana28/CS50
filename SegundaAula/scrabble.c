#include <stdio.h>    
#include <ctype.h>    
#include <string.h>   

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; // números correspondente as letras

int compute_score(const char *word) {  // Função para calcular a pontuação

    int score = 0; 
    for (int i = 0; word[i] != '\0'; i++) {  // Verifica se o caractere é uma letra
        if (isalpha(word[i])) {  //Verifica se o caractere atual (word[i]) é uma letra. 
        //Se for uma letra, o código dentro do bloco é executado.
            score = score + POINTS[toupper(word[i]) - 'A']; //Converte a letra para maiúscula, encontra seu valor no array POINTS
            // e adiciona esse valor à pontuação acumulada
        }  
    }  
    return score;  
}  

int main(void) {  
    char word1[50], word2[50];  

    printf("Player 1: ");  
    scanf("%49s", word1);  
    printf("Player 2: ");  
    scanf("%49s", word2);  

    int score1 = compute_score(word1);  
    int score2 = compute_score(word2);  

    if (score1 > score2) {  
        printf("Player 1 wins!\n"); 
    } else if (score2 > score1) { 
        printf("Player 2 wins!\n"); 
    } else {  
        printf("Tie!\n"); 
    }  // 28

    return 0;  
}  // 30
