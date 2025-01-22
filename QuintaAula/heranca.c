#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cada pessoa tem dois pais e dois alelos
typedef struct pessoa
{
    struct pessoa *pais[2];
    char alelos[2];
} pessoa;

// Protótipos das funções
pessoa *criar_familia(int geracoes);
void imprimir_familia(pessoa *p, int geracao);
void liberar_familia(pessoa *p);
char alelo_aleatorio();

int main(void)
{
    // Inicializar o gerador de números aleatórios
    srand(time(0));

    // Criar uma família com três gerações
    pessoa *p = criar_familia(3);

    // Imprimir árvore genealógica
    imprimir_familia(p, 0);

    // Liberar memória
    liberar_familia(p);

    return 0;
}

// Criar um novo indivíduo com `gerações`
pessoa *criar_familia(int geracoes)
{
    // Alocar memória para uma nova pessoa
    pessoa *p = malloc(sizeof(pessoa));
    if (p == NULL)
    {
        fprintf(stderr, "Falha na alocação de memória.\n");
        exit(1);
    }

    // Caso base: geração sem pais
    if (geracoes == 1)
    {
        p->pais[0] = NULL;
        p->pais[1] = NULL;
        p->alelos[0] = alelo_aleatorio();
        p->alelos[1] = alelo_aleatorio();
    }
    // Caso recursivo: geração com pais
    else
    {
        // Criar pais recursivamente
        p->pais[0] = criar_familia(geracoes - 1);
        p->pais[1] = criar_familia(geracoes - 1);

        // Atribuir alelos aleatoriamente com base nos pais
        p->alelos[0] = p->pais[0]->alelos[rand() % 2];
        p->alelos[1] = p->pais[1]->alelos[rand() % 2];
    }

    return p;
}

// Liberar `p` e todos os ancestrais de `p`
void liberar_familia(pessoa *p)
{
    // Caso base: se a pessoa for NULL, retorna
    if (p == NULL)
    {
        return;
    }

    // Liberar pais recursivamente
    liberar_familia(p->pais[0]);
    liberar_familia(p->pais[1]);

    // Liberar memória da pessoa atual
    free(p);
}

// Imprimir cada membro da família e seu tipo sanguíneo
void imprimir_familia(pessoa *p, int geracao)
{
    // Lidar com o caso base
    if (p == NULL)
    {
        return;
    }

    // Indentar a saída com base na geração
    for (int i = 0; i < geracao; i++)
    {
        printf("   ");
    }

    // Imprimir o tipo sanguíneo da pessoa
    printf("Geração %i, tipo sanguíneo %c%c\n", geracao, p->alelos[0], p->alelos[1]);

    // Imprimir pais da geração atual
    imprimir_familia(p->pais[0], geracao + 1);
    imprimir_familia(p->pais[1], geracao + 1);
}

// Escolher aleatoriamente um alelo do tipo sanguíneo
char alelo_aleatorio()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
