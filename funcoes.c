#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int numLinhasArquivo(const char *nomeArquivo, int tamPalavra){
	
	int cont = 0;
	
	char despejar[tamPalavra + 1];
	
	FILE *arq = fopen(nomeArquivo, "r");
	
	if(!arq) return 0;
	
	while(fscanf(arq, "%s\n", despejar) == 1)
		cont++;
	
	fclose(arq);
	
	return cont;
	
}

char **lerArquivo(const char *nomeArquivo, int tam, int tamPalavra){
	
	FILE *arq = fopen(nomeArquivo, "r");
	
	if(!arq) return NULL;
	
	int i;
	
	char **vetor = (char **)malloc(sizeof(char *) * tam);
	
	for(i=0; i<tam; i++){
		
		vetor[i] = (char *)malloc(sizeof(char) * (tamPalavra + 1));
		fscanf(arq, "%s\n", vetor[i]);
		vetor[i][tamPalavra] = '\0';
		
	}
		
		
	return vetor;
	
}

void imprimirCache(Cache *cache, int numLinhas, int tamTag, int tamPalavra, int numPalavras){
	
	int i, j, k;
	
	//+------+----------+----------+----------+----------+
	
	printf("+");
	for(i=0; i<tamTag + 2; i++)
		printf("-");
	printf("+");
	
	for(i=0; i<numPalavras; i++){
		for(j=0; j<tamPalavra + 2; j++)
			printf("-");
		printf("+");	
	}
	
	//| TAG  |    P3    |    P2    |    P1    |    P0    |
	
	printf("\n");
	printf("|");
	for(i=0; i<(tamTag - 1)/2; i++)
		printf(" ");
	printf("TAG");
	for(i=0; i<(tamTag - 1)/2; i++)
		printf(" ");
	if(tamTag % 2 == 0)
		printf(" ");
	printf("|");
	
	for(i=numPalavras-1; i>-1; i--){
	
		
		for(j=0; j<(tamPalavra - 0)/2; j++)
			printf(" ");
		printf("P%d", i);
		for(j=0; j<(tamPalavra - 0)/2; j++)
			printf(" ");
		printf("|");
		
	}
	
	//+------+----------+----------+----------+----------+
	
	printf("\n");
	printf("+");
	for(i=0; i<tamTag + 2; i++)
		printf("-");
	printf("+");
	
	for(i=0; i<numPalavras; i++){
		for(j=0; j<tamPalavra + 2; j++)
			printf("-");
		printf("+");	
	}
	  
	printf("\n");
	
	//
	
	for(i=0; i<numLinhas; i++){
		
		printf("|");
		
		printf(" %s |", (cache + i)->tag);
		
		for(j=numPalavras - 1; j>-1; j--)
			printf(" %s |", (cache + i)->palavras[j]);
		
		//+------+----------+----------+----------+----------+
		
		printf("\n");
		printf("+");
		for(j=0; j<tamTag + 2; j++)
			printf("-");
		printf("+");
		
		for(j=0; j<numPalavras; j++){
			for(k=0; k<tamPalavra + 2; k++)
				printf("-");
			printf("+");	
		}
			
		printf("\n");
		
	}
	
		
	
}

void inicializarCache(Cache *cache, int numLinhas, int numPalavras, int tamTag, int tamPalavra){
	
	int i, j, k;
	
	for(i=0; i<numLinhas; i++){
		
		(cache + i)->tag = (char *)malloc(sizeof(char) * (tamTag + 1));
		
		for(j=0; j<tamTag; j++)
			(cache + i)->tag[j] = '-';
		(cache + i)->tag[j] = '\0';	
		
		(cache + i)->palavras = (char **)malloc(sizeof(char *) * numPalavras);
		
		for(j=0; j<numPalavras; j++){
			
			(cache + i)->palavras[j] = (char *)malloc(sizeof(char) * (tamPalavra + 1));
			
			for(k=0; k<tamPalavra; k++)
				(cache + i)->palavras[j][k] = '-';
			(cache + i)->palavras[j][k] = '\0';
			
		}
		
	}
	
}

void mapeamento(Cache *cache, char **instrucoes, char **memPrincipal, int numLinhas, int numPalavras, int numInstrucoes, int tamMemPrincipal, int tamTag, int tamPalavra, int bitsNumBloco, int mapeamentoT, int op){
	
	int i, j, k, numBloco, indice = 0, cabeca = 0,/* base = 0,*/ hit = 0, miss = 0;
	int *vetorCont = (int *)calloc(numLinhas, sizeof(int));
	
	char *tag = (char *)malloc(sizeof(char) * (tamTag + 1));
	;
	tag[tamTag] = '\0';
	
	for(i=0; i<numInstrucoes; i++){
		
		strncpy(tag, instrucoes[i], tamTag);
		
		if(mapeamentoT == 1){
			char *stringNumBloco = (char *)malloc(sizeof(char) * (bitsNumBloco + 1));
			stringNumBloco[bitsNumBloco] = '\0';
			
			strncpy(stringNumBloco, instrucoes[i], bitsNumBloco);
		
			numBloco = strtol(stringNumBloco, NULL, 2);
			
			indice = numBloco % numLinhas;
			
			if(strcmp(tag, (cache + indice)->tag)){
				
				strcpy((cache + indice)->tag, tag);
				
				for(j=0; j<numPalavras; j++)
					strcpy((cache + indice)->palavras[j], memPrincipal[numBloco*numPalavras + j]);
					
				printf("Instrucao %d - Cache Miss - Linha %d - TAG: %s\n", i, indice, tag);
				miss++;
				
			} else{
				printf("Instrucao %d - Cache Hit - Linha %d - TAG: %s\n", i, indice, tag);
				hit++;
			}
				
				
		}
		
		int existe = 0;
		
		if(mapeamentoT == 2 && op == 1){
			
			for(j=0; j<numLinhas; j++){
				
				if(!strcmp(tag, (cache + j)->tag)){
					existe = 1;
					break;
				}
				
			}
			
			if(existe){
				printf("Instrucao %d - Cache Hit - Linha %d - TAG: %s\n", i, j, tag);
				hit++;
				
			} else{
				
				strcpy((cache + (cabeca%numLinhas))->tag, tag);
				
				numBloco = strtol(tag, NULL, 2);
				
				for(j=0; j<numPalavras; j++)
					strcpy((cache + (cabeca%numLinhas))->palavras[j], memPrincipal[numBloco*numPalavras + j]);
					
				printf("Instrucao %d - Cache Miss - Linha %d - TAG: %s\n", i, cabeca%numLinhas, tag);
				cabeca++;
				miss++;	
				
			}
			
		}
		
		if(mapeamentoT == 2 && op == 2){
			
			for(j=0; j<numLinhas; j++){
				
				if(!strcmp(tag, (cache + j)->tag)){
					existe = 1;
					break;
				}
				
			}
			
			if(existe == 1){
			
				printf("Instrucao %d - Cache Hit - Linha %d - TAG: %s\n", i, j, tag);
				hit++;
				

			} else{
				
				printf("Instrucao %d - Cache Miss - Linha 0 - TAG: %s\n", i, tag);
				miss++;
				j = numLinhas - 1;
				
				numBloco = strtol(tag, NULL, 2);

			}
			
			for( ; j > 0; j--){
		
				strcpy((cache + j)->tag, (cache + j - 1)->tag);
				
				for(k=0; k<numPalavras; k++)
					strcpy((cache + j)->palavras[k], (cache + j - 1)->palavras[k]);
		
			}
			
			strcpy(cache->tag, tag);
			for(j=0; j<numPalavras; j++)
				strcpy(cache->palavras[j], memPrincipal[numBloco*numPalavras + j]);
			
		}
		
	
		if(mapeamentoT == 2 && op == 3){
			
			int menor = *vetorCont, indiceMenor = 0;
			
			for(j=0; j<numLinhas; j++){
				
				if(*(vetorCont + j) < menor){
					menor = *(vetorCont + j);
					indiceMenor = j;
				}
					
				
				if(!strcmp(tag, (cache + j)->tag)){
					printf("Instrucao %d - Cache Hit - Linha %d - TAG: %s\n", i, j, tag);
					hit++;
					existe = 1;
					*(vetorCont + j) = *(vetorCont + j) + 1;
					break;
				}
				
			}
			
			if(existe == 0){
				
				numBloco = strtol(tag, NULL, 2);
				
				printf("Instrucao %d - Cache Miss - Linha %d - TAG: %s\n", i, indiceMenor, tag);
				miss++;
				
				strcpy((cache + indiceMenor)->tag, tag);
				for(j=0; j<numPalavras; j++)
					strcpy((cache + indiceMenor)->palavras[j], memPrincipal[numBloco*numPalavras + j]);
				*(vetorCont + indiceMenor) = 1;
				
			}
			
		}
		
		imprimirCache(cache, numLinhas, tamTag, tamPalavra, numPalavras);
		printf("\n");
	
	}
	
	printf("Cache Hit: %d\nCache Miss: %d\n\n", hit, miss);
	
}






  



