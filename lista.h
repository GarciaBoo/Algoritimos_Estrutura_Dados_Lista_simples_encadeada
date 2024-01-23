#ifndef LISTA_H
#define LISTA_H

#define TRUE 1 /* define valor booleano a nao existe na linguagem C */
#define FALSE 0
#define boolean int /* define um tipo booleano */
#define inicial 0
#define ERRO -404

#include "item.h"
                       
typedef struct lista_ LISTA;

LISTA *lista_criar(void);
void lista_apagar(LISTA **ptr);

int lista_tamanho(LISTA *lista);
boolean lista_vazia(LISTA *lista);
boolean lista_cheia(LISTA *lista);

int lista_inserir(LISTA *lista, ITEM *item);
boolean lista_remover(LISTA *lista, int chave);
ITEM *lista_busca(LISTA *lista, int chave);
void lista_imprimir(LISTA *lista);

boolean inserir_palavra_chave(LISTA *lista, char *chave, int codigo);
boolean atualizar_relevancia(LISTA *lista, int chave,  int codigo);

LISTA *lista_ordenada_relevancia(LISTA **l);

LISTA *buscar_palavra_chave(LISTA *lista, char *palavra_chave);
void lista_imprimir_busca_palavra(LISTA *lista);

void sugestao_de_sites(LISTA *lista, char *palavra);

#endif