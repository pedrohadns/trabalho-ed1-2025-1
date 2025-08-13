#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Pilha.h"

#define MAX 1000

typedef struct
{
    int x;
    int y;
} Posicao;

bool posicaoValida(int x, int y, int n, int m, char mapa[MAX][MAX], bool processado[MAX][MAX])
{
    if (x >= 0 && x < n && y >= 0 && y < m && mapa[x][y] == '.' && !processado[x][y])
        return true;
    else
        return false;
}

void visitarComodo(Pilha *pilha, int x0, int y0, int n, int m, char mapa[MAX][MAX], bool processado[MAX][MAX])
{
    Posicao *inicio = (Posicao *)malloc(sizeof(Posicao));
    if (inicio == NULL)
    {
        printf("Erro de alocacao. \n");
        exit(1);
    }
    inicio->x = x0;
    inicio->y = y0;
    empilha(pilha, inicio);
    processado[x0][y0] = true;

    while (!estaVazia(pilha))
    {
        Posicao *ultima = (Posicao *)desempilha(pilha);
        int dir_x[4] = {-1, 1, 0, 0};
        int dir_y[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            int vizinhoX = ultima->x + dir_x[i];
            int vizinhoY = ultima->y + dir_y[i];
            if (posicaoValida(vizinhoX, vizinhoY, n, m, mapa, processado))
            {
                Posicao *vizinho = (Posicao *)malloc(sizeof(Posicao));
                vizinho->x = vizinhoX;
                vizinho->y = vizinhoY;
                empilha(pilha, vizinho);
                processado[vizinhoX][vizinhoY] = true;
            }
        }
        free(ultima);
    }
}

int contaComodos(int n, int m, char mapa[MAX][MAX])
{
    bool processado[MAX][MAX] = {false};
    Pilha *pilha = criaPilha();
    int totalComodos = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mapa[i][j] == '.' && !processado[i][j])
            {
                totalComodos++;
                visitarComodo(pilha, i, j, n, m, mapa, processado);
            }
        }
    }
    esvaziaPilha(pilha);
    free(pilha);
    return totalComodos;
}

int main()
{
    int n, m;
    char mapa[MAX][MAX];
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
    {
        scanf("%s", mapa[i]);
    }
    int totalComodos = contaComodos(n, m, mapa);
    printf("%d\n", totalComodos);
    return 0;
}