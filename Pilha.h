/* Grupo 4
 * Davi Brandão de Souza
 * Silvio Eduardo Belinazzi de Andrade
 * Mauricio Zanetti Neto
 * Pedro Henrique Alves do Nascimento
 */

/**
 * @file Pilha.h
 * @brief Arquivo header com a declaração de structs e funções para implementação da pilha utilizando lista simplesmente encadeada com nó cabeça.
 * @authors Davi Brandão de Souza
 * @authors Mauricio Zanetti Neto
 * @authors Pedro Henrique Alves do Nascimento
 * @authors Silvio Eduardo Belinazzi de Andrade
 *
 * @showdate "%B %Y"
 */
#ifndef PILHA_H
#define PILHA_H

/**
 * @struct Nó
 * @brief Estrutura para o nó de uma pilha que armazena tipo genérico de dado em seu campo chave. 
 */
typedef struct no{
    void *chave; ///< Campo para armazenar os dados
    struct no *prox;    ///< Ponteiro para o próximo nó da pilha
} No;

/**
 * @struct Pilha
 * @brief Estrutura que armazena o topo de uma pilha.
 */
typedef struct{
    No *topo;
    int tamanho;
} Pilha;

/**
 * @brief Cria um novo nó para a pilha com o valor passado como argumento, por padrão o campo `prox` aponta para `NULL`.
 * @param valor Ponteiro para o valor que será inserido no nó criado.
 * @return Retorna o ponteiro para o nó criado com o valor dado.
 */
No *criaNo(void *valor);

/**
 * @brief Cria uma pilha vazia com tamanho 0.
 * @return Pilha criada.
 */
Pilha *criaPilha();

/**
 * @brief Empilha um nó com chave `valor` na pilha `p`.
 * @param p Pilha na qual o elemento será empilhado.
 * @param valor Ponteiro para o valor que será empilhado na pilha.
 * @return void.
 */
void empilha(Pilha *p, void *valor);

/**
 * @brief Desempilha um elemento da pilha `p`, liberando a memória que ele ocupa e retornando o valor que estava no topo.
 * @param p Pilha que terá um elemnento desempilhado.
 * @return Valor que estava armazenado no topo da pilha.
 */
void *desempilha(Pilha *p);

/**
 * @brief Verifica se a pilha está vazia ou não.
 * @param p A pilha a ser verificada.
 * @return Retorna 1 se a pilha está vazia ou se não está inicializada, e 0 se não.
 */
int estaVazia(Pilha *p);

/**
 * @brief Função *callback* para impressão de tipo genérico de dado.
 * @param valor Ponteiro para o dado a ser impresso.
 * @return void.
 */
void imprimeCB(void *valor);

/**
 * @brief Imprime todos elementos da pilha.
 * @param p Pilha a ser impressa.
 * @param imprimeCB Função *callback* para imprimir cada elemento da pilha.
 * @return void.
 */
void imprimePilha(No *p, void (*imprimeCB)(void*));

/**
 * @brief Esvazia uma dada pilha, liberando a memória de cada nó (sem liberar o ponteiro da pilha em si).
 * @param p Pilha a ser esvaziada.
 * @return void.
 */
void esvaziaPilha(Pilha *p);

#endif
