#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define N 1000 // Número de depósitos na tabela de hash
#define TAMANHO_MAX 45 // Tamanho máximo de uma palavra

// Estrutura que representa um nó da tabela hash
typedef struct nodo {
    char palavra[TAMANHO_MAX + 1]; // Palavra armazenada no nó
    struct nodo *proximo; // Ponteiro para o próximo nó
} nodo;

// Tabela hash global
nodo *tabela[N];

// Função de hash (simples)
unsigned int funcao_hash(const char *palavra) {
    unsigned int valor_hash = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        valor_hash = (valor_hash * 31 + tolower(palavra[i])) % N;
    }
    return valor_hash;
}

// Função para carregar o dicionário na tabela hash
bool carregar(const char *dicionario) {
    FILE *arquivo = fopen(dicionario, "r");
    if (arquivo == NULL) {
        return false;
    }

    char palavra[TAMANHO_MAX + 1];
    while (fscanf(arquivo, "%s", palavra) != EOF) {
        // Aloca um novo nó
        nodo *novo_nodo = malloc(sizeof(nodo));
        if (novo_nodo == NULL) {
            fclose(arquivo);
            return false;
        }
        strcpy(novo_nodo->palavra, palavra);
        novo_nodo->proximo = NULL;

        // Calcula o valor hash para a palavra
        unsigned int indice = funcao_hash(palavra);

        // Insere o novo nó na tabela hash
        if (tabela[indice] == NULL) {
            tabela[indice] = novo_nodo;
        } else {
            novo_nodo->proximo = tabela[indice];
            tabela[indice] = novo_nodo;
        }
    }

    fclose(arquivo);
    return true;
}

// Função para verificar se uma palavra está no dicionário
bool verificar(const char *palavra) {
    unsigned int indice = funcao_hash(palavra);
    nodo *atual = tabela[indice];

    while (atual != NULL) {
        if (strcasecmp(atual->palavra, palavra) == 0) {
            return true;
        }
        atual = atual->proximo;
    }

    return false;
}

// Função para liberar a memória usada pela tabela hash
void descarregar(void) {
    for (int i = 0; i < N; i++) {
        nodo *atual = tabela[i];
        while (atual != NULL) {
            nodo *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        tabela[i] = NULL;
    }
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <dicionario>\n", argv[0]);
        return 1;
    }

    // Carrega o dicionário
    if (!carregar(argv[1])) {
        printf("Falha ao carregar o dicionário.\n");
        return 1;
    }

    // Exemplo de palavras para verificar
    char *palavras_para_verificar[] = {
        "casa", "carro", "livro", "palavra_inexistente", "felicidade", NULL
    };

    // Verifica cada palavra
    for (int i = 0; palavras_para_verificar[i] != NULL; i++) {
        if (verificar(palavras_para_verificar[i])) {
            printf("'%s' está correta.\n", palavras_para_verificar[i]);
        } else {
            printf("'%s' está incorreta.\n", palavras_para_verificar[i]);
        }
    }

    // Descarrega a tabela hash
    descarregar();

    return 0;
}
