#include "lista.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct no_ NO; 

struct no_{
  ITEM *item;
  NO *proximo;
};

struct lista_{ 
  NO *inicio;
  NO *fim;    
  int tamanho; // armazena a quantidade de sites
};

/* funcao para criar no */
NO *no_criar(ITEM *item){
  NO *n = (NO *) malloc(sizeof(NO));
    
  if ((n != NULL) && (item != NULL)){
    n->item = item;
    n->proximo = NULL;
    return(n);
  }
  else
    return(NULL);
}


/* funcao para criar a lista e inicializar como vazia */
LISTA *lista_criar(void){
        
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  if(lista != NULL) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
  }

  return (lista);
}

/* funcao para apagar a lista*/
void lista_apagar(LISTA **ptr){
  NO *aux;
	// apaga os elementos da lista
	while ((*ptr)->inicio != NULL) {
		aux = (*ptr)->inicio;
		(*ptr)->inicio = (*ptr)->inicio->proximo;
		free(aux);
	}
	// apaga a lista
	free(*ptr);
	*ptr = NULL;
	return;
}
 
/* funcao para retornar o tamanho da lista */
int lista_tamanho(LISTA *lista){
  return(lista->tamanho);
}

// verifica se a lista esta vazia. Retorna TRUE em caso positivo e FALSE caso contrario   
boolean lista_vazia(LISTA *lista){
  if((lista != NULL) && lista->inicio == NULL)
      return(TRUE);
  return(FALSE);
}

// verifica se a lista esta cheia. Retorna TRUE em caso positivo e FALSE caso contrario
boolean lista_cheia(LISTA *lista){
  NO *no = (NO *) malloc(sizeof(NO));
  if (no != NULL){
    free(no);
    no = NULL;
    return (FALSE);
  }
  return(TRUE);
}

/* funcao para realizar a busca interna nos codigos da lista */
void lista_busca_interna(LISTA *l, ITEM *x, NO **p, NO **ant){   
  *p = l->inicio; // primeiro da lista
  *ant = NULL; // anterior do primeiro eh nulo
  while (*p != NULL && item_get_codigo((*p)->item) < item_get_codigo(x)) {
    *ant = *p; // guarda anterior
    *p = (*p)->proximo; // atualiza no corrente
  }
  return;
}

/* funcao para realizar a insercao ordanada na lista */
int lista_inserir(LISTA *l, ITEM *x) {
  NO *p, *ant, *nova;
  
  lista_busca_interna(l, x, &p, &ant); // busca posicao para insercao
  
  if (p != NULL && p->item == x) return 1; // erro, elemento ja existe

  // cria caixa e copia informacao
  nova = malloc(sizeof(NO));
  nova->item = x;
  // atualiza encadeamento
  nova->proximo = p;
  if (ant == NULL){
      l->inicio = nova; // caso 1
	}else
      ant->proximo = nova; // caso 2

  l->tamanho++; //atualiza o tamanho
  
  return 0; // sucesso
}

/* funcao para realizar a insercao de forma nao ordanada na lista */
boolean lista_inserir_nao_ordenada(LISTA *lista, ITEM *item){
  if ( (!lista_cheia(lista)) && (lista != NULL)) {
            
    NO *pnovo = (NO *) malloc(sizeof (NO));
    
    if (lista->inicio == NULL) 
        lista->inicio = pnovo;  
    else 
        lista->fim->proximo = pnovo;
        
    pnovo->item = item;
    pnovo->proximo = NULL;
    lista->fim = pnovo;
    lista->tamanho++;
    
    return (TRUE);
  } else 
    return (FALSE);
}

/* funcao para remover um site da lista */
boolean lista_remover(LISTA *lista, int chave){
  NO *aux = NULL;
  NO *p = NULL;

  if(lista != NULL){
    p = lista->inicio;
    
    //procura o item a ser removido
    while(p != NULL && item_get_codigo(p->item) != chave){
      aux = p;
      p = p->proximo;
    }
    //seta ele nulo
    if(p!=NULL){
      if(p == lista->inicio)
        lista->inicio = p->proximo;
      else
        aux->proximo = p->proximo;
      
      p->proximo = NULL;
      
      if(p == lista->fim)
        lista->fim = aux;

      //apaga o item da memoria
      item_apagar(&(p->item));
      free(p);
      lista->tamanho--;
      return(TRUE);
    }
  }

  return(FALSE);
}

/* funcao para busca sequencial adaptada para lista */
ITEM *lista_busca(LISTA *lista, int chave){
  NO	*p;

  if(lista	!=	NULL){			
    p	=	lista->inicio;  
    while(p	!=	NULL)	{		
        if(item_get_codigo(p->item)	==	chave)  
          return(p->item);
        p	=	p->proximo;
    }
  }

  return(NULL);
}

/* funcao para imprimir os dados da lista */
void lista_imprimir(LISTA *lista){
  NO *p;

  if (lista != NULL){
    p = lista->inicio; // p eh utilizado como auxiliar para nao alterar a lista
    while(p != NULL){
			item_imprimir(p->item);
			p = p->proximo; // passa para o proximo site
    } 
  } else {
    printf("Lista vazia.\n");
  }
  
  return;
}

/* funcao para inserir uma nova palavra chave num determinado site da lista */
boolean inserir_palavra_chave(LISTA *lista, char *chave,  int codigo){
  ITEM* item;
  if(lista != NULL) {
		item = lista_busca(lista,codigo); //verifica se o codigo existe
		if(item != NULL){
			if(item_get_tamanho_palavra_chave(item) < 10){ //se sim verifica se tem espaco para uma nova palavra chave
				item_set_chave(item,chave); //adiciona a nova palavra
				return (TRUE);
			} else {
				printf("Numero maximo de palavras chave atingido.\n");
				return(FALSE);
			}
		} else
			printf("Codigo nao existe.\n");
  }
  return(FALSE);
}

/* funcao para atualizar a relevancia de um determinado site da lista */ 
boolean atualizar_relevancia(LISTA *lista, int chave, int codigo){
  ITEM* item;

  if(lista != NULL) {
    item = lista_busca(lista,codigo);  //verifica se a relevancia existe
    if(item != NULL){
          item_set_relevancia(item,chave); //altera o dado pelo desejado
          return(TRUE);
    } else
      printf("Codigo nao existe.\n");
  }
  return(FALSE);
}

/* funcao para realizar a busca interna da relevancia da lista */
void lista_busca_interna2(LISTA *l, ITEM *x, NO **p, NO **ant){   
  *p = l->inicio; // primeiro da lista
  *ant = NULL; // anterior do primeiro eh nulo
  while (*p != NULL && item_get_relevancia((*p)->item) > item_get_relevancia(x)) {
      *ant = *p; // guarda anterior
      *p = (*p)->proximo; // atualiza no corrente
  }
  return;
}

/* funcao para realizar a insercao ordanada por relevancia na lista */
int lista_inserir2(LISTA *l, ITEM *x){
  NO *p, *ant, *nova;
  
  lista_busca_interna2(l, x, &p, &ant); // busca posicao para insercao
  if (p != NULL && p->item == x)
      return 1; // erro, elemento ja existe
  
  // cria caixa e copia informacao
  nova = malloc(sizeof(NO));
  nova->item = x;
  // atualiza encadeamento
  nova->proximo = p;
  if (ant == NULL){
      l->inicio = nova; // caso 1
	}else
      ant->proximo = nova; // caso 2

  l->tamanho++; //atualiza o tamanho
  
  return 0; // sucesso
}

/* funcao para ordernar a lista por relevancia de forma decrescente */
LISTA *lista_ordenada_relevancia(LISTA **l){
	LISTA *ordena, *anda;

	ordena = lista_criar(); // lista que ira guardar os itens ordenados
	anda = *l; // lista a ser corrida para não quebrar a original

	while(anda->inicio!= NULL){
		lista_inserir2(ordena,anda->inicio->item); // insere ordenado
		anda->inicio = anda->inicio->proximo; // passa para o proximo item
	}

	lista_apagar(&anda); // apaga auxiliar e retorna
	return(ordena);
}

/* funcao de busca para as palavras chaves */
int busca(char **palavra_chave, char *chave, int n){
	for(int i = 0; i <n; i++){	
    // procura a palavra chave dentro das palavras chaves de um determinado site
		if(0 == strcmp(palavra_chave[i],chave)){ 
      // caso encontre, retorna a posicao
			return i;
		}
	}
	return ERRO; // palavra chave nao encontrada
}

/* funcao para realizar a busca por palavras chaves e ordernar por relevancia as encontradas */
LISTA *buscar_palavra_chave(LISTA *lista, char *palavra_chave){
	NO *p; // no para percorrer as posicoes da lista
  int encontrou, verifica = 0; // caso encontre a palavra chave
	LISTA *aux; // lista auxiliar onde serao armazenadas os sites relevantes
	aux = lista_criar();

  if (lista != NULL){
    p = (lista)->inicio; // comeca pela primeiro site
    while(p != NULL){
      // realiza a busca das palavras chaves
      encontrou = busca(item_get_palavra_chave(p->item), palavra_chave,item_get_tamanho_palavra_chave(p->item));
      if(encontrou >= 0) { 
        // caso encontre, inseri na nova lista
        lista_inserir(aux,p->item);
			  verifica++;
      }
			p = p->proximo; // passa para o proximo site
    }
		if(verifica == 0){
			printf("Palavra-chave não encontrada.\n");
			return NULL;
		}
  } else {
    printf("Lista vazia.\n");
		return NULL;
  }

  // ordena a lista pela relevancia de forma crescente
 	aux = lista_ordenada_relevancia(&aux);
	
  return aux; // retorna a nova lista
}

/* funcao para imprimir nome e link dos sites */
void lista_imprimir_busca_palavra(LISTA *lista){
  NO *p;

  if (lista != NULL){
    p = lista->inicio; // p eh utilizado como auxiliar para nao alterar a lista
    while(p != NULL){
			printf("%s,", item_get_nome(p->item));
			printf("%s", item_get_link(p->item));
      printf("\n");
			p = p->proximo;
    } 
  } else {
    printf("Lista vazia.\n");
  }
  
  return;
}

/* funcao para contar a quantidade total de palavras chaves */
int conta_palavras(LISTA *l){
	int cont = 0;	
	NO *anda;
	anda = l->inicio;
	
	while(anda != NULL){
		cont += item_get_tamanho_palavra_chave(anda->item); // pega o total de palavras e soma ao que ja tem
		anda = anda->proximo; // passa para o proximo
	}
	
	return cont;
}

/* funcao para coletar todas as palavras chaves da lista */
void coletar_palavras(LISTA *lista, char **palavras_chave, int n){
	if(lista == NULL) return;

  NO *p;
	int i = 0 , verificador;
  char **palavra; // armazena as palavras chaves de cada site

  if (lista != NULL){
		p = (lista)->inicio; // no p recebe o primeiro site
		while(p != NULL && i < n){ // n eh a quatidade total de palavras chaves
			for(int j = 0; j < item_get_tamanho_palavra_chave(p->item); ++j){

				palavra = item_get_palavra_chave(p->item); // copia as palavras chaves de determinado site
				verificador = 0;
				
				for(int k = 0; k < i; ++k){
					if(0 == strcmp(palavra[j],palavras_chave[k])){
						verificador++;
					}
				}

				if(verificador == 0)
					strcpy(palavras_chave[i],palavra[j]); // copia palavra por palavra de determinado site
				else
					strcpy(palavras_chave[i],"\0");
				i++; // atualiza a o posicao da matriz palavras chave

			}
			p = p->proximo; // passa para o proximo site
		}
	}

  return;
}

/* Funcao para buscar os sites que contêm alguma das palavras-chave identificadas no passo b*/
LISTA *seleciona_sites(LISTA *l, char **palavra_chave, int total_palavras){

  LISTA *indica = lista_criar();
  
	NO *p; // no para percorrer as posicoes da lista
	int pos;

  if (l != NULL){
    p = (l)->inicio; // comeca pela primeiro site

    while(p != NULL){
			for(int i = 0; i<total_palavras; ++i){
				pos = busca(item_get_palavra_chave(p->item),palavra_chave[i],item_get_tamanho_palavra_chave(p->item));
			
				if(pos >= 0) // caso encontre, insere na nova lista
					lista_inserir(indica,p->item);
			}
			
			p = p->proximo;
		}
  } else {
    printf("Lista vazia.\n");
  }
	
	return indica;
}

/* Funcao para mostrar o nome e o link dos cinco (5) sites mais relevantes ordenados por relevância(decrescente) */
void listar_sites(LISTA *l){
  NO *p;
  int cont = 0;
  char **aux;
  aux = (char**)calloc(10,sizeof(char*));
	for(int i = 0; i < 10; ++i)
		aux[i]= (char*)calloc(50,sizeof(char));

  // ordena por relevancia de modo decrescente
  l = lista_ordenada_relevancia(&l);
  
  // imprimir os cinco primeiros sites
  if (l != NULL){
    p = l->inicio;
    while(p != NULL && cont != 4){
      printf("%s,", item_get_nome(p->item));
      printf("%s", item_get_link(p->item));
      printf("\n");
      cont++;
      p = p->proximo;
    } 
  } else {
    printf("Lista vazia.\n");
  }
  
  // libera memoria
	for(int i = 0; i < 10; ++i)
		free(aux[i]);
	free(aux);
}

/* funcao base para cada funcao de sugestao de sites */
void sugestao_de_sites(LISTA *lista, char *palavra){
	int total_palavras;
	char **palavras_chave;
	
	/* Passo A */
  // lista dos sites filtrados pela palavra chave escolhida
	LISTA *lista_s;
  LISTA *lista_tmp;

	lista_s = buscar_palavra_chave(lista,palavra);
	
	if(lista_s != NULL){

		/* Passo B */
		total_palavras = conta_palavras(lista_s);

		// aloca matriz de palavras chave
		palavras_chave = (char**)calloc(total_palavras,sizeof(char*));
		for(int i = 0; i < total_palavras; ++i)
			palavras_chave[i]= (char*)calloc(50,sizeof(char));

		// coleta as palavras chaves dos sites encontrados
		coletar_palavras(lista_s, palavras_chave, total_palavras);

		printf("\nPalavras-Chaves coletadas: \n");
		for(int i = 0; i < total_palavras; ++i){
			if(0 != strcmp(palavras_chave[i],"\0"))
				printf("%s ", palavras_chave[i]);
		}
		printf("\n");

		/* Passo C */
    // coleta sites que contem as palavras chaves encontradas
		lista_tmp = seleciona_sites(lista, palavras_chave,(total_palavras));

		/* Passo D */
    // imprimi os cinco sites com maior relevancia encontrados
    printf("\nSites selecionados: \n");
		listar_sites(lista_tmp);

		// libera memoria
		for(int i = 0; i < total_palavras; ++i)
			free(palavras_chave[i]);
		free(palavras_chave);
	}

  return;
}