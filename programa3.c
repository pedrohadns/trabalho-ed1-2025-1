/** Grupo 4
 * Davi Brandão de Souza
 * Silvio Eduardo Belinazzi de Andrade
 * Mauricio Zanetti Neto
 * Pedro Henrique Alves do Nascimento
 */

/**
 * @file programa3.c
 * @brief Implementação das funções para contagem de cômodos em uma planta de casa.
 * @authors Davi Brandão de Souza
 * @authors Mauricio Zanetti Neto
 * @authors Pedro Henrique Alves do Nascimento
 * @authors Silvio Eduardo Belinazzi de Andrade
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Pilha.h"

#define MAX 1000

/**
 * @struct Posicao
 * @brief Representa uma posição no mapa com coordenadas (x, y).
 */

typedef struct
{
    int x; /**< Coordenada x (linha) */
    int y; /**< Coordenada y (coluna) */
} Posicao;

/**
 * @brief Verifica se uma posição (x,y) é válida para visitar no mapa.
 *
 * Uma posição é válida se estiver dentro dos limites, for um espaço livre ('.')
 * e ainda não foi processada.
 *
 * @param x Coordenada x (linha) da posição.
 * @param y Coordenada y (coluna) da posição.
 * @param n Número de linhas do mapa.
 * @param m Número de colunas do mapa.
 * @param mapa Matriz que representa o mapa, com '.' para espaço livre.
 * @param processado Matriz booleana que indica posições já processadas (agendadas para visitação).
 * @return true se a posição for válida para visitar, false caso contrário.
 */

bool posicaoValida(int x, int y, int n, int m, char mapa[MAX][MAX], bool processado[MAX][MAX])
{
    if (x >= 0 && x < n && y >= 0 && y < m && mapa[x][y] == '.' && !processado[x][y])
        return true;
    else
        return false;
}

/**
 * @brief Explora um cômodo do mapa a partir da posição inicial usando busca em profundidade.
 *
 * Utilizando uma pilha, a função empilha posições válidas conectadas, e desempilha para explorar seus vizinhos, 
 * marcando posições como processadas para evitar visitas repetidas.
 *
 * @param pilha Ponteiro para a pilha usada para controle da exploração.
 * @param x0 Coordenada x (linha) inicial para começar a visita.
 * @param y0 Coordenada y (coluna) inicial para começar a visita.
 * @param n Número de linhas do mapa.
 * @param m Número de colunas do mapa.
 * @param mapa Matriz do mapa com '.' indicando espaços livres.
 * @param processado Matriz booleana que indica posições já processadas.
 */

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

/**
 * @brief Conta o número de cômodos (áreas conectadas de '.') no mapa.
 *
 * Percorre o mapa, e para cada ponto não processado que seja '.' chama a função visitarComodo,
 * que marca todo o cômodo como processado.
 *
 * @param n Número de linhas do mapa.
 * @param m Número de colunas do mapa.
 * @param mapa Matriz do mapa.
 * @return O total de cômodos encontrados no mapa.
 */

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

/**
 * @brief Função principal do programa.
 *
 * Lê as dimensões do mapa, lê o mapa da entrada,
 * calcula o número de cômodos e imprime o resultado.
 *
 * @return 0 se a execução ocorreu com sucesso.
 */

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
