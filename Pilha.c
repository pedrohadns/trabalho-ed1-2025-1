/* Grupo 4
 * Davi Brandão de Souza
 * Silvio Eduardo Belinazzi de Andrade
 * Mauricio Zanetti Neto
 * Pedro Henrique Alves do Nascimento
 */

/**
 * @file Pilha.c
 * @brief Arquivo com a implementação das funções para a pilha.
 * @authors Davi Brandão de Souza
 * @authors Mauricio Zanetti Neto
 * @authors Pedro Henrique Alves do Nascimento
 * @authors Silvio Eduardo Belinazzi de Andrade
 * 
 * @showdate "%B %Y"
 */
#include <stdlib.h> 
#include <stdio.h>
#include "Pilha.h"

No *criaNo(void *valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL){
	perror("Erro ao alocar nó.\n");
	exit(1);
    }
    novoNo->chave = valor;
    novoNo->prox = NULL;
    return novoNo;
}

Pilha *criaPilha()
{
    Pilha *novaPilha = (Pilha *)malloc(sizeof(Pilha));
    if (novaPilha == NULL){
	perror("Erro ao alocar pilha.\n");
	exit(1);
    }
    novaPilha->topo = NULL;
    novaPilha->tamanho = 0;
    return novaPilha;
}

void empilha(Pilha *p, void *valor)
{
    if (p != NULL){
	No *noEmp = criaNo(valor); // Nó que vai ser empilhado na pilha.
	noEmp->prox = p->topo;
	p->topo = noEmp;
	p->tamanho++;
    }
}

void *desempilha(Pilha *p)
{
    if (p == NULL || p->topo == NULL){ return NULL; } // Verificando os casos em que a pilha está vazia
	No *aux = p->topo; // Nó auxiliar que armazena o endereço inicial de p.
	void *chave = aux->chave;
	p->topo = aux->prox;
	p->tamanho--;
	free(aux);
	return chave;
}

int estaVazia(Pilha *p)
{
    if (p == NULL){ return 1; }
    return (p->tamanho == 0);
}

void imprimePilha(No *p, void (*imprimeCB)(void*))
{
    if (p == NULL){ return; }
    No *aux = p;
    while (aux != NULL){
	imprimeCB(aux->chave);
	aux = aux->prox;
    }
    printf("\n");
}

void esvaziaPilha(Pilha *p)
{
    if (p == NULL){ return; }
    while (p->topo != NULL){ desempilha(p); }
}
