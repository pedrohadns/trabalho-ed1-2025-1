/* Grupo 4
 * Davi Brandão de Souza
 * Mauricio Zanetti Neto
 * Pedro Henrique Alves do Nascimento
 * Silvio Eduardo Bellinazzi de Andrade
 */

/**
 * @file programa1.c
 * @brief Arquivo com a implementação do programa 1 para validação de expressões matemáticas.
 * @authors Davi Brandão de Souza
 * @authors Mauricio Zanetti Neto
 * @authors Pedro Henrique Alves do Nascimento
 * @authors Silvio Eduardo Bellinazzi de Andrade
 *
 * @showdate "%B %Y"
 */
#include "Pilha.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Função que valida expressões matemáticas conforme seus delimitadores.
 * Lê a expressão caractere a caractere e empilha somente os delimitadores de
 * abertura, se o próximo caractere delimitador for de fechamento e for o 
 * correspondente, desempilha o elemento do topo e continua. Leva em consideração a
 * hierarquia dos delimitadores, não pode haver chaves ou colchetes dentro de parênteses, 
 * nem chaves dentro de colchetes.
 * @param exp Expressão que deve ser validada (*string*).
 * @return Retorna 0 para uma expressão inválida e 1 para uma expressão válida.
 */
int validarExpressao(char *exp)
{
    if (exp == NULL){ return 0; }
    Pilha *p = criaPilha();
    int i = 0;
    while (exp[i] != '\0'){
	char caractere = exp[i];
	if (caractere == '(' || caractere == '[' || caractere == '{'){ // Insere na pilha somente os caracteres de abertura
	    /* Para tratar a opção b, foi feito uso dos valores dos caracteres de delimitação
	     * na tabela ASCII, onde os delimitadores com maior precedência sempre têm valores
	     * númericos menores que os de menor precedência.
	     *
	     * Exemplo: (A{B-C}*E), com '(' estando no topo da pilha, tenta-se empilhar '{',
	     * os respectivos valores desses caracteres em decimal são 40 e 123, então a comparação
	     * feita abaixo fica: 40 - 123 < 0 -> verdadeiro, ou seja, a expressão é inválida pela
	     * opção b, pois o '{' está numa posição mais interna que '('.
	     */
	    if (!estaVazia(p) && (*(char *)p->topo->chave - caractere < 0)){
		esvaziaPilha(p);
		free(p);
		return 0;
	    }
	    char *dadoEmpilhar = (char *)malloc(sizeof(char));
	    if (dadoEmpilhar == NULL){
		perror("Erro ao alocar dado.\n");
		exit(1);
	    }
	    *dadoEmpilhar = caractere;
	    empilha(p, dadoEmpilhar);
	}
	else if (caractere == ')' || caractere == ']' || caractere == '}'){
	    if (estaVazia(p)){
		esvaziaPilha(p);
		free(p);
		return 0;
	    }
	    char topo = *(char *)desempilha(p);

	    if ((caractere == ')' && topo != '(') ||
		(caractere == ']' && topo != '[') ||
		(caractere == '}' && topo != '{')){
		esvaziaPilha(p);
		free(p);
		return 0;
	    }
	}
	i++;
    }
    int valida = estaVazia(p); // A pilha deve estar vazia para garantir que não há delimitadores de abertura sem fechamento
    esvaziaPilha(p);
    free(p);

    return valida;
}

/**
 * @brief Função para utilizar o programa, aceita como entrada a expressão que deseja que seja validada e imprime na tela se é válida ou não.
 */
int main() {
    int execucao = 1;
    char expressao[512];
    while (execucao != 0){
	printf("Digite a expressão: ");
	getchar();
	fgets(expressao, 512, stdin);
	if (validarExpressao(expressao)){ printf("VALIDA\n"); }
	else{ printf("INVALIDA\n"); }
	printf("Deseja validar outra expressão? (0-Não/1-Sim) ");
	scanf(" %d", &execucao);
    }
    return EXIT_SUCCESS;
}
