#include <stdio.h>
#include <string.h>
#include <stdbool.h> // Adiciona suporte a bool, true, false

// Definições constantes
#define MAX 9

// Estrutura para armazenar os pares de candidatos
typedef struct
{
    int winner;
    int loser;
} pair;

// Variáveis globais
int preferences[MAX][MAX]; // preferences[i][j] é o número de eleitores que preferem o candidato i ao candidato j
bool locked[MAX][MAX]; // locked[i][j] indica se há uma aresta do candidato i para o candidato j
char* candidates[MAX]; // nomes dos candidatos
pair pairs[MAX * (MAX - 1) / 2]; // pares de candidatos
int candidate_count; // número de candidatos
int pair_count; // número de pares

// Funções declaradas
bool vote(int rank, char* name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool creates_cycle(int start, int candidate);

int main(int argc, char* argv[])
{
    // Verifica a quantidade de candidatos
    if (argc < 2)
    {
        printf("Uso: tideman [candidato...]\n");
        return 1;
    }

    // Inicializa candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Número máximo de candidatos é %i\n", MAX);
        return 2;
    }

    // Preenche os nomes dos candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Inicializa as matrizes de preferências e bloqueios
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
            locked[i][j] = false;
        }
    }

    // Solicita o número de eleitores
    int voter_count;
    printf("Número de eleitores: ");
    scanf("%d", &voter_count);

    // Processa os votos
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];

        // Solicita as classificações dos eleitores
        for (int j = 0; j < candidate_count; j++)
        {
            char name[100];  // Buffer para armazenar o nome do candidato
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            if (!vote(j, name, ranks))
            {
                printf("Voto inválido!\n");
                return 3;
            }
        }

        // Registra as preferências
        record_preferences(ranks);
    }

    // Adiciona os pares de candidatos
    add_pairs();

    // Classifica os pares de acordo com a força da vitória
    sort_pairs();

    // Bloqueia os pares sem criar ciclos
    lock_pairs();

    // Imprime o vencedor
    print_winner();
}

// Registra o voto de um eleitor
bool vote(int rank, char* name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Registra as preferências dos eleitores
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Adiciona os pares de candidatos
void add_pairs(void)
{
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Ordena os pares de candidatos pela força de vitória
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            int strength_i = preferences[pairs[i].winner][pairs[i].loser];
            int strength_j = preferences[pairs[j].winner][pairs[j].loser];

            if (strength_i < strength_j)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
}

// Bloqueia os pares no gráfico sem criar ciclos
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!creates_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}

// Verifica se a adição de uma aresta cria um ciclo
bool creates_cycle(int start, int candidate)
{
    if (start == candidate)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][start] && creates_cycle(i, candidate))
        {
            return true;
        }
    }

    return false;
}

// Imprime o vencedor da eleição
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_source = false;
                break;
            }
        }

        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
