/* Grupo 4
 * Davi Brandão de Souza
 * Mauricio Zanetti Neto
 * Pedro Henrique Alves do Nascimento
 * Silvio Eduardo Bellinazzi de Andrade
 */

/**
 * @file programa2.c
 * @brief Algoritmo para Avaliação de Expressões em Notação Pós-Fixa.
 * @authors Davi Brandão de Souza
 * @authors Mauricio Zanetti Neto
 * @authors Pedro Henrique Alves do Nascimento
 * @authors Silvio Eduardo Bellinazzi de Andrade
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Pilha.h"

#define MAX_EXPRESSAO 100

/**
 * @brief Verifica o operador .
 * A função verifica se o caractere é um dos operadores aritméticos.
 * @param c Caractere a ser verificado.
 * @return 1 se for um operador, 0 caso contrário.
 */
int ehOperador(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

/**
 * @brief Define a prioridade dos operadores.
 * A função retorna um valor inteiro que representa a precedência do operador.
 * Operadores com maior precedência retornam valores maiores.
 * @param op Operador a ser verificado.
 * @return Precedência do operador.
*/
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

/**
 * @brief Converte uma expressão infixa para posfixa.
 * A função armazena os operandos diretamente na saída e usa uma pilha para gerenciar os operadores.
 * Os operadores são empilhados e desempilhados conforme a precedência, e os parênteses são tratados adequadamente.
 * @param infixa Expressão infixa a ser convertida.
 * @param posfixa Buffer onde a expressão posfixa será armazenada.
 */
void infixaParaPosfixa(char *infixa, char *posfixa)
{
    Pilha *operadores = criaPilha();
    int j = 0;

    for (int i = 0; infixa[i] != '\0'; i++) // percorre a expressão infixa
    {
        char c = infixa[i]; 

        if (c == ' ')
            continue;

        if (c >= 'A' && c <= 'J') 
        {
            posfixa[j++] = c; // adiciona operandos diretamente à saída
        }
        else if (c == '(') 
        {
            char *abre = malloc(sizeof(char)); // aloca memória para o caractere
            *abre = c; 
            empilha(operadores, abre); 
        }
        else if (c == ')')
        {
            while (!estaVazia(operadores) && *((char *)topoPilha(operadores)) != '(')
            {
                char *op = (char *)desempilha(operadores);
                posfixa[j++] = *op; // adiciona operadores à saída até encontrar o parêntese de abertura 
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
            while (!estaVazia(operadores) && precedencia(*((char *)topoPilha(operadores))) >= precedencia(c)) // desempilha operadores com maior ou igual precedência
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

/**
    * @brief Interpreta e avalia uma expressão aritmética em notação polonesa reversa 
    * A função armazena os valores das variáveis em uma pilha e realiza as operações conforme encontra operadores na expressão.
    * @param posfixa Expressão em notação polonesa reversa.
    * @param valores Array de valores das variáveis (A-J).
    * @return Resultado da avaliação da expressão.
*/
float avaliarPosfixa(char *posfixa, float valores[])
{
    Pilha *pilha = criaPilha(); 

    for (int i = 0; posfixa[i] != '\0'; i++) // percorre a expressão posfixa
    {
        char c = posfixa[i]; 

        if (c == ' ')
            continue;

        if (c >= 'A' && c <= 'J') // se for operando, empilha o valor correspondente
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
            float *op1 = (float *)desempilha(pilha); // desempilha os dois operandos

            float *resultado = malloc(sizeof(float)); 

            switch (c) // realiza a operação correspondente
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

/** @brief Marca as letras usadas.
    * Percorre a expressão e marca as letras usadas no array.
    * @param expr Expressão a ser analisada.
    * @param usadas Array de inteiros onde cada índice representa uma letra (0 para A, 1 para B, ..., 9 para J).
*/
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
/** @brief Função principal do programa.
 * Lê o tipo de expressão (infixa ou posfixa), converte se necessário, solicita os valores das variáveis usadas e avalia a expressão.
 * @return Código de saída do programa.
 */
int main()
{
    char tipo;
    char infixa[MAX_EXPRESSAO], posfixa[MAX_EXPRESSAO];
    float valores[10];
    int usadas[10] = {0};

    printf("Digite o tipo da entrada, a-infixa/b-posfixa: ");
    scanf("%c", &tipo);

    if (tipo == 'a' || tipo == 'A')
    {
        // Entrada infixa
	printf("Digite a expressão: ");
        scanf(" %99[^\n]", infixa);
        infixaParaPosfixa(infixa, posfixa);
        printf("%s\n", posfixa); // converte para pósfixa 
    }
    else if (tipo == 'b' || tipo == 'B')
    {
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

    // Percorre as letras de A a J
    for (char c = 'A'; c <= 'J'; c++)
    {
        if (usadas[c - 'A']) //se a letra for usada sera solicitado o valor
        {
	    printf("Digite o valor de %c: ", c);
	    while(scanf("%f", &valores[c - 'A']) != 1){
		while (getchar() != '\n');
		printf("Digite o valor de %c: ", c);
	    }
        }
    }

    float resultado = avaliarPosfixa(posfixa, valores);
    printf("Resultado: %.2f\n", resultado); 

    return 0;
}
