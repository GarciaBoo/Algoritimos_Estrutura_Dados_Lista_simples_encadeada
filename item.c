#include "item.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct item_{
  short int codigo;
  char nome[51];
  int relevancia;
  char link[101];
  char palavra_chave[10][51];
  int tamanho_palavra_chave;
};

/* aloca espaco na memoria e adiocona os itens na struct */
ITEM *item_criar(int codigo, char *nome, int relevancia, char *link, char **palavra_chave, int tam){
  
  ITEM *item;
  item = (ITEM*)malloc(sizeof(ITEM));

  if(item != NULL){
    item->codigo = codigo;
    strcpy(item->nome,nome);
    item->relevancia = relevancia;
    strcpy(item->link,link);
    item->tamanho_palavra_chave = tam;
    for(int i = 0; i < tam; i++){
      strcpy(item->palavra_chave[i],palavra_chave[i]);
		}
  }

  if(item == NULL) printf("Item nulo\n");

  return item;
}

/* apaga um item da memoria */
boolean item_apagar(ITEM **item){
  if(item != NULL){
    free(*item);
    *item = NULL;
    return(TRUE);
  }
  return(FALSE);
}

/* imprime todos os dados do item */
void item_imprimir(ITEM *item){
	int tam =  (item->tamanho_palavra_chave);
  if(item != NULL){
    printf("%d,", item->codigo);
    printf("%s,", item->nome);
    printf("%d,", item->relevancia);
    printf("%s,", item->link);
    for(int i = 0; i < tam; i++){
      if((i+1) != tam)
				printf("%s,",item->palavra_chave[i]);
			else
				printf("%s",item->palavra_chave[i]);
		}
  }
}

/* pega o codigo */
int item_get_codigo(ITEM *item){
  if(item!=NULL)
    return item->codigo;
    else{
      printf("\nERRO: item_get_codigo\n");
      exit(1);
    }
}

/* pega o dado no nome */
char *item_get_nome(ITEM *item){
  if(item!=NULL)
    return item->nome;
    else{
      printf("\nERRO: tem_get_chave_nome\n");
      exit(1);
    }
}

/* pega o dado na relevancia */
int item_get_relevancia(ITEM *item){
  if(item!=NULL)
    return item->relevancia;
    else{
      printf("\nERRO: item_get_relevancia\n");
      exit(1);
    }
}

/* pega o dado no link */
char *item_get_link(ITEM *item){
  if(item!=NULL)
    return item->link;
    else{
      printf("\nERRO: item_get_link\n");
      exit(1);
    }
}

/* pega o dado na palavra chave */
char **item_get_palavra_chave(ITEM *item){
	char **aux;
  
	aux = (char **)malloc(10 * sizeof(char*));
	for(int i=0; i<10; ++i)
		aux[i]= (char *)malloc(51*sizeof(char));

	for(int i=0; i<10; ++i)
		aux[i]=item->palavra_chave[i];

	return (aux);
}

/* pega o tamanho da palavra chave */
int item_get_tamanho_palavra_chave(ITEM *item){
  if(item!=NULL)
    return item->tamanho_palavra_chave;
    else {
      printf("\nERRO: item_get_tamanho_palavra_chave\n");
      exit(1);
    }
}

/* adiciona um dado no codigo */
boolean item_set_codigo(ITEM *item, int codigo){
  if(item!=NULL){
    item->codigo = codigo;
    return(TRUE);
  }else{
    return(FALSE);
  }
}

/* adiciona um dado na palavra chave */
boolean item_set_chave(ITEM *item, char chave[50]){
  if(item!=NULL){
		strcpy(item->palavra_chave[item->tamanho_palavra_chave],chave);
		item->tamanho_palavra_chave++;
		return(TRUE);
  }else{
    return(FALSE);
  }
}

/* muda a relevancia */
boolean item_set_relevancia(ITEM *item, int chave){
  if(item!=NULL){
      item->relevancia = chave;
      return(TRUE);
  }else{
    return(FALSE);
  }
}