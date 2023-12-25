/*

	João Victor Alves de Meira

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(void){
	
	int i, j, mapeamentoT, op=0, numLinhas = 4, numPalavras = 4, tamTag, tamPalavra = 8, bitsNumBloco = 6;
	int numInstrucoes = numLinhasArquivo("instrucoes.txt", tamPalavra), tamMemPrincipal = numLinhasArquivo("memPrincipal.txt", tamPalavra);
	
	Cache *cache = (Cache *)malloc(sizeof(Cache) * numLinhas);
	
    char **instrucoes = lerArquivo("instrucoes.txt", numInstrucoes, tamPalavra), **memPrincipal = lerArquivo("memPrincipal.txt", tamMemPrincipal, tamPalavra);
    
    printf("Simulador de Memoria Cache\n\n");
	
	do{
		
		printf("Escolha o tipo de mapeamento:\n1-Mapeamento Direto\n2-Mapeamento Associativo\nEscolha: ");
		scanf("%d", &mapeamentoT);
		printf("\n");
		
		if(mapeamentoT == 2){
			
			do{
				
				printf("1-Mapeamento FIFO \n2-Mapeamento LRU\n3-Mapeamento LFU\nEscolha: ");
				scanf("%d", &op);
				printf("\n");
				
			}while(op != 1 && op != 2 && op != 3);
			
		}
		
	}while(mapeamentoT != 1 && mapeamentoT != 2);
	
	if(mapeamentoT == 1)
		tamTag = 4;
	else
		tamTag = 6;

	
	inicializarCache(cache, numLinhas, numPalavras, tamTag, tamPalavra);
		
	mapeamento(cache, instrucoes, memPrincipal, numLinhas, numPalavras, numInstrucoes, tamMemPrincipal, tamTag, tamPalavra, bitsNumBloco, mapeamentoT, op);
	
	return 0;
}
