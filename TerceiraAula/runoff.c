#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 100

// Estrutura para armazenar informações dos candidatos
typedef struct
{
    char name[100];
    int votes;
    bool eliminated;
}
candidate;

// Array global para armazenar os candidatos
candidate candidates[MAX_CANDIDATES];

// Matriz de preferências de voto dos eleitores
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Número de eleitores e candidatos
int voter_count, candidate_count;

// Função para registrar o voto de um eleitor
bool vote(int voter, int rank, char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Se o nome do candidato corresponder, registra a preferência
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Função para contar os votos para cada candidato
void tabulate(void)
{
    // Zera os votos de todos os candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    // Conta os votos para os candidatos que não foram eliminados
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;  // Para contar apenas o voto para o candidato não eliminado
            }
        }
    }
}

// Função para imprimir o vencedor, se houver
bool print_winner(void)
{
    // A maioria dos votos é mais da metade dos eleitores
    int majority = voter_count / 2;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Função para encontrar o número mínimo de votos
int find_min(void)
{
    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Função para verificar se todos os candidatos restantes têm o mesmo número de votos
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Função para eliminar os candidatos com o menor número de votos
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}

int main(int argc, char *argv[])
{
    // Verifica se há pelo menos dois candidatos
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;

    // Inicializa os candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // Solicita o número de eleitores
    printf("Número de eleitores: ");
    scanf("%d", &voter_count);

    // Solicita os votos de cada eleitor
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Rank %d: ", j + 1);
            char name[100];
            scanf("%s", name);

            if (!vote(i, j, name))
            {
                printf("Voto inválido.\n");
                return 1;
            }
        }
    }

    // Realiza a eleição em turnos
    while (true)
    {
        // Conta os votos para os candidatos não eliminados
        tabulate();

        // Verifica se há um vencedor
        if (print_winner())
        {
            break;
        }

        // Encontra o candidato com o menor número de votos
        int min = find_min();

        // Verifica se todos os candidatos restantes têm o mesmo número de votos
        if (is_tie(min))
        {
            printf("Empate.\n");
            break;
        }

        // Elimina os candidatos com o menor número de votos
        eliminate(min);
    }

    return 0;
}
