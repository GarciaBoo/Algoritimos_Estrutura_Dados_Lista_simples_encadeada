#ifndef ITEM_H
  #define ITEM_H

  #define TRUE 1
  #define FALSE 0
  #define boolean int

  typedef struct item_ ITEM;

  ITEM *item_criar(int codigo, char *nome, int relevancia, char *link, char **palavra_chave, int tam);
  boolean item_apagar(ITEM **item);
  void item_imprimir(ITEM *item);
  int item_get_codigo(ITEM *item);
  char *item_get_nome(ITEM *item);
  int item_get_relevancia(ITEM *item);
  char *item_get_link(ITEM *item);

  char **item_get_palavra_chave(ITEM *item);

  int item_get_tamanho_palavra_chave(ITEM *item);
  boolean item_set_codigo(ITEM *item, int codigo);
  boolean item_set_chave(ITEM *item, char chave[50]);
  boolean item_set_relevancia(ITEM *item, int chave);

#endif