#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lista.h"
#include "item.h"

/* Funcao para ler as entradas do arquivo e inserir na lista */
void ler_entrada(LISTA **l) {
  /* variaveis de relevancia para o conteudo da lista */
  short int codigo;
	char nome[50];
	int relevancia;
	char link[100];
	char **palavra_chave, *token, *str, *str1;

  /* cria o arquivo e aloca as frases */
	FILE *arq = fopen("googlebot.txt", "r");
  str = (char*)malloc(200*sizeof(char));
  str1 = (char*)malloc(200*sizeof(char));

	int tam, cont, aux; /* variaveis auxiliares */

  while(!feof(arq)) { /* condicao para o arquivo ser lido até o final */
    /* aloca memoria da string que guarda as palavras chave */
    palavra_chave = (char**)calloc(10,sizeof(char*));
		for(int i = 0; i < 10; ++i)
			palavra_chave[i]= (char*)calloc(50,sizeof(char));
		
    /* le o arquivo */
    fgets(str1,200,arq);

    /* atribui os dados a uma variavel auxiliar */
    strcpy(str,str1);
    
    /* fragmenta as informaçoes da frase, separado-as na hora de inserir */
    /* armazena o codigo */
    token = strtok(str,",");
    codigo = strtol(token, NULL, 10);

    /* armazena o nome */
    token = strtok(NULL,",");
    strcpy(nome,token);

    /* armazena a relevancia */
    token = strtok(NULL,",");
    relevancia = strtol(token,NULL,10);

    /* armazena o link */
    token = strtok(NULL,",");
    strcpy(link,token);

    /* contabiliza tamanho da entrada do arquivo original */
	  tam = strlen(str1);
    cont = 0;
    
    /* procura o inicio das palavras chaves */
    for(int i = 0; i < tam; i++){
      if(str1[i] == ','){
        cont ++;
        if(cont == 4){
          aux = i+1; //guarda exatamente o inicio das palavras chaves 
				}
      }
    }
    
    cont = cont-3; //total de palavras chave a serem inseridas

    /* armazena palavra chave em colunas separadas da matriz*/
			int i = 0, k = 0; //auxliares da funcao
			
			for(int j = aux; j < tam; ++j){
				if(str1[j] != ','){
					palavra_chave[i][k]=str1[j];
					k++;
				} else {
					i++;
					k=0;
				}
			}

    /* insere na lista */
    if(lista_busca(*l,codigo) == NULL) { 
      lista_inserir(*l, item_criar(codigo,nome,relevancia,link,palavra_chave,cont));
    } else{
      printf("Codigo %hd ja existe, nao pode ser usado...\n", codigo); /* caso o codigo ja tenha sido inserido, nao insere novamente*/
    }

    /* esvazia a variavel */
    palavra_chave = NULL;
  }
  
  /* libera memoria */
  free(str);
  free(str1);
  free(palavra_chave);

  /* fecha o arquivo */
	fclose(arq);
	return;
}

/* Menu de escolha */
void menu(LISTA *l) {
  /* variaveis utilizadas nos casos */
  LISTA *lista2 = lista_criar(); /* cria segunda lista */
  char key_word[50];
  short int code;
  int relevance, opc;
  
  printf("\t\t** MENU **\n");
  printf("\t* OPÇAO 1: INSERIR UM SITE *\n");
  printf("\t* OPÇAO 2: REMOVER UM SITE *\n");
  printf("\t* OPÇAO 3: INSERIR UMA PALAVRA-CHAVE *\n");
  printf("\t* OPÇAO 4: ATUALIZAR RELEVANCIA *\n");
  printf("\t* OPÇAO 5: SAIR DO PROGRAMA *\n");
  printf("\t* OPÇAO 6: IMPRIMIR SITES *\n");
  printf("\t* OPÇAO 7: BUSCAR POR PALAVRA-CHAVE*\n");
  printf("\t* OPÇAO 8: SUGESTÃO DE SITES *\n");

  do {
    printf("\nQual funcao voce deseja realizar?\n");
	  scanf("%d", &opc);
    
		switch(opc) {
      /* inserir um site */
		  case 1:
        ler_entrada(&l);
      break;

      /* remover um site */
     case 2:
        printf("Digite um codigo: \n");
        scanf("%hd", &code);
        lista_remover(l,code);
      break;

      /* inserir palavra-chave */
      case 3:
        printf("Digite o codigo onde deseja inserir a palavra-chave: \n");
        scanf("%hd", &code);
        printf("Digite uma nova palavra-chave: \n");
        scanf("%s", key_word);
        inserir_palavra_chave(l,key_word,code);
      break;

      /* atualizar relevância */
      case 4:
        printf("Digite o codigo onde deseja atualizar relevancia: \n");
        scanf("%hd", &code);
        printf("Digite a nova relevancia: \n");
        scanf("%d", &relevance);
        atualizar_relevancia(l,relevance,code);
      break;

      /* imprimir a lista */
      case 6:
        lista_imprimir(l);
      break;

      /* buscar por palavra-chave */
      case 7:
        printf("Digite a palavra-chave que deseja buscar: \n");
        scanf("%s", key_word);
        lista2 = buscar_palavra_chave(l, key_word);
        printf("Sites que contem a palavra-chave buscada: \n");
        lista_imprimir_busca_palavra(lista2);
      break;

      /* sugestão de sites */
      case 8:
      	printf("Digite a palavra-chave que deseja procurar: \n");
	    	scanf("%s", key_word);
        sugestao_de_sites(l, key_word);
      break;
	 }
   
	} while(opc != 5); /* sai do programa */

  free(lista2);
  return;
}

/* Main */
int main(void) {
  /* cria a lista */
  LISTA *l = lista_criar();
  
  /* realiza as chamadas do usuario pelo menu de escolha */
  menu(l);

  /* apaga a lista */
  lista_apagar(&l);
  if(l == NULL) printf("Lista foi apagada com sucesso!\n");

  return 0;
}