#include <stdio.h>
#include <string.h>
#include <stdbool.h>  // Inclua esse cabeçalho para usar bool

#define MAX 9 // Número máximo de candidatos

// Estrutura para armazenar os candidatos
typedef struct
{
    char nome[100];
    int votos;
}
candidato;

// Declara um array global de candidatos
candidato candidatos[MAX];

// Contador de candidatos
int contador_candidatos;

// Função para registrar um voto
bool votar(char nome[])
{
    // Itera sobre todos os candidatos
    for (int i = 0; i < contador_candidatos; i++)
    {
        if (strcmp(candidatos[i].nome, nome) == 0)
        {
            // Aumenta o número de votos se encontrar o candidato
            candidatos[i].votos++;
            return true;
        }
    }
    return false;
}

// Função para imprimir o vencedor(es)
void imprimir_vencedor(void)
{
    int max_votos = 0;
    
    // Encontra o maior número de votos
    for (int i = 0; i < contador_candidatos; i++)
    {
        if (candidatos[i].votos > max_votos)
        {
            max_votos = candidatos[i].votos;
        }
    }

    // Imprime todos os candidatos com o maior número de votos
    for (int i = 0; i < contador_candidatos; i++)
    {
        if (candidatos[i].votos == max_votos)
        {
            printf("%s\n", candidatos[i].nome);
        }
    }
}

int main(int argc, char *argv[])
{
    // Verifica se o número correto de argumentos foi passado
    if (argc < 2)
    {
        printf("Uso: plurality [candidato ...]\n");
        return 1;
    }

    // Define o número de candidatos
    contador_candidatos = argc - 1;

    // Se o número de candidatos for maior que o limite, exibe erro
    if (contador_candidatos > MAX)
    {
        printf("O número máximo de candidatos é %d\n", MAX);
        return 2;
    }

    // Copia os nomes dos candidatos
    for (int i = 0; i < contador_candidatos; i++)
    {
        strcpy(candidatos[i].nome, argv[i + 1]);
        candidatos[i].votos = 0;
    }

    // Solicita o número de eleitores
    int contador_eleitores;
    printf("Número de eleitores: ");
    scanf("%d", &contador_eleitores);

    // Coleta os votos dos eleitores
    for (int i = 0; i < contador_eleitores; i++)
    {
        char nome[100];
        printf("Voto: ");
        scanf("%s", nome);

        // Registra o voto ou exibe erro se o voto for inválido
        if (!votar(nome))
        {
            printf("Voto inválido.\n");
        }
    }

    // Imprime o(s) vencedor(es)
    imprimir_vencedor();
    return 0;
}
