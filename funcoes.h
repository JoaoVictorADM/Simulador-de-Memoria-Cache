typedef struct cache{
	
	char *tag;
	char **palavras;
	
}Cache;

void inicializarCache(Cache *cache, int numLinhas, int numPalavras, int tamTag, int tamPalavra);
int numLinhasArquivo(const char *nomeArquivo, int tamPalavra);
char **lerArquivo(const char *nomeArquivo, int tam, int tamPalavra);
void mapeamento(Cache *cache, char **instrucoes, char **memPrincipal, int numLinhas, int numPalavras, int numInstrucoes, int tamMemPrincipal, int tamTag, int tamPalavra, int bitsNumBloco, int mapeamentoT, int op);
void imprimirCache(Cache *cache, int numLinhas, int tamTag, int tamPalavra, int numPalavras);
void adicionarBloco(Cache *cache, Cache linha, int indice);
