#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Pilha.h"

#define MAX_EXPRESSAO 100

// Verifica se um caractere é operador
int ehOperador(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Define a precedência dos operadores
int precedencia(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

// Converte expressão infixa para posfixa
void infixaParaPosfixa(char *infixa, char *posfixa)
{
    Pilha *operadores = criaPilha();
    int j = 0;

    for (int i = 0; infixa[i] != '\0'; i++)
    {
        char c = infixa[i];

        if (c == ' ')
            continue;

        if (c >= 'A' && c <= 'J')
        {
            posfixa[j++] = c;
        }
        else if (c == '(')
        {
            char *abre = malloc(sizeof(char));
            *abre = c;
            empilha(operadores, abre);
        }
        else if (c == ')')
        {
            while (!estaVazia(operadores) && *((char *)topoPilha(operadores)) != '(')
            {
                char *op = (char *)desempilha(operadores);
                posfixa[j++] = *op;
                free(op);
            }
            if (estaVazia(operadores))
            {
                // Erro: Parêntese de fechamento sem um par de abertura correspondente
                exit(1);
            }
            free(desempilha(operadores));
        }
        else if (ehOperador(c))
        {
            while (!estaVazia(operadores) &&
                   precedencia(*((char *)topoPilha(operadores))) >= precedencia(c))
            {
                char *op = (char *)desempilha(operadores);
                posfixa[j++] = *op;
                free(op);
            }
            char *op = malloc(sizeof(char));
            *op = c;
            empilha(operadores, op);
        }
        else
        {
            // Erro: Caractere inválido
            exit(1);
        }
    }

    while (!estaVazia(operadores))
    {
        if (*((char *)topoPilha(operadores)) == '(')
        {
            // Erro: Parêntese de abertura sem um par de fechamento correspondente
            exit(1);
        }
        char *op = (char *)desempilha(operadores);
        posfixa[j++] = *op;
        free(op);
    }

    posfixa[j] = '\0';
    free(operadores);
}

// Avalia expressão posfixa com base nos valores das variáveis
float avaliarPosfixa(char *posfixa, float valores[])
{
    Pilha *pilha = criaPilha();

    for (int i = 0; posfixa[i] != '\0'; i++)
    {
        char c = posfixa[i];

        if (c == ' ')
            continue;

        if (c >= 'A' && c <= 'J')
        {
            float *val = malloc(sizeof(float));
            *val = valores[c - 'A'];
            empilha(pilha, val);
        }
        else if (ehOperador(c))
        {
            if (estaVazia(pilha))
            {
                // Erro: Falta operandos para o operador
                exit(1);
            }
            float *op2 = (float *)desempilha(pilha);

            if (estaVazia(pilha))
            {
                // Erro: Falta operandos para o operador
                exit(1);
            }
            float *op1 = (float *)desempilha(pilha);

            float *resultado = malloc(sizeof(float));

            switch (c)
            {
            case '+':
                *resultado = *op1 + *op2;
                break;
            case '-':
                *resultado = *op1 - *op2;
                break;
            case '*':
                *resultado = *op1 * *op2;
                break;
            case '/':
                if (*op2 == 0.0f)
                {
                    // Erro: Divisão por zero
		    printf("Divisão por zero.\n");
                    exit(1);
                }
                *resultado = *op1 / *op2;
                break;
            case '^':
                *resultado = pow(*op1, *op2);
                break;
            }

            free(op1);
            free(op2);
            empilha(pilha, resultado);
        }
        else
        {
            // Erro: Caractere inválido
            exit(1);
        }
    }

    if (estaVazia(pilha))
    {
        // Erro: Expressão vazia ou inválida
        exit(1);
    }
    float resultadoFinal = *((float *)desempilha(pilha));

    if (!estaVazia(pilha))
    {
        // Erro: Expressão possui operandos no final
        exit(1);
    }

    free(pilha);
    return resultadoFinal;
}

// Marca quais letras (A-J) aparecem na expressão
void marcarLetrasUsadas(char *expr, int usadas[])
{
    for (int i = 0; expr[i] != '\0'; i++)
    {
        char c = expr[i];
        if (c >= 'A' && c <= 'J')
        {
            usadas[c - 'A'] = 1;
        }
    }
}

int main()
{
    char tipo;
    char infixa[MAX_EXPRESSAO], posfixa[MAX_EXPRESSAO];
    float valores[10];
    int usadas[10] = {0};

    // Tipo da expressão (infixa e pósfixa)
    printf("Digite o tipo da entrada, a-infixa/b-posfixa: ");
    scanf("%c", &tipo);

    if (tipo == 'a' || tipo == 'A')
    {
        // Expressão infixa
	printf("Digite a expressão: ");
        scanf(" %99[^\n]", infixa);
        infixaParaPosfixa(infixa, posfixa);
        printf("%s\n", posfixa); // Expressão pósfixa convertida
    }
    else if (tipo == 'b' || tipo == 'B')
    {
        // Expressão pósfixa
	printf("Digite a expressão: ");
        scanf(" %99[^\n]", posfixa);
    }
    else
    {
        // Erro: Tipo inválido
	printf("Erro, tipo inválido.\n");
        return 1;
    }

    marcarLetrasUsadas(posfixa, usadas);

    // Valores das variáveis usadas
    for (char c = 'A'; c <= 'J'; c++)
    {
        if (usadas[c - 'A'])
        {
	    printf("Digite o valor de %c: ", c);
	    while(scanf("%f", &valores[c - 'A']) != 1){
		while (getchar() != '\n');
		printf("Digite o valor de %c: ", c);
	    }
//            {
//                // Erro: Entrada inválida
//            }
        }
    }

    float resultado = avaliarPosfixa(posfixa, valores);
    printf("Resultado: %.2f\n", resultado); // Resultado da expressão

    return 0;
}
