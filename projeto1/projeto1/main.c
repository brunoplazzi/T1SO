#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


//dimensoes da matriz
#define LINHAS 90;
#define COLUNAS 90;

//tamanho dos macroblocos
#define MC_LINHA 30;
#define MC_COLUNA 30;

//tamanho maximo do numero
#define MAX_NUM_SIZE 32000;

//numero de threads
#define NUM_THREADS 4;


//cria matriz de inteiros
int** matriz_inteiros(int l, int c) {

	int** mat;
	int i;

	//verificando validade dos parametros
	if (l < 1 || c < 1) {
		
		printf("ERRO! Parametro inválido. (l ou c devem ser maiores que zero)\n");
		return NULL;
	}

	//aloca linhas da matriz e testa a alocacao
	mat = calloc(l, sizeof(int*));
	
	if (mat == NULL) {
		
		printf("ERRO! Na alocacao de memoria\n");
		return NULL;
	}

	//aloca as colunas das matrizes e testa a alocacao
	for (i = 0; i < l; i++) {
		
		mat[i] = calloc(c, sizeof(int));
		if (mat[i] == NULL) {
			
			printf("ERRO! Na alocacao de memoria\n");
			return NULL;
		}
	}

	return mat;
}


//libera memoria da matriz
int** liberar_matriz(int l, int c, int** mat) {

	int i;
	
	//verifica se parametros sao validos e se matriz recebida eh nula
	if (mat == NULL) { return NULL; }

	if (l < 1 || c < 1) {
		
		printf("ERRO! Parametro inválido. (l ou c devem ser maiores que zero)\n");
		return mat;
	}

	//libera a matriz
	for (i = 0; i < c; i++) { free(mat[i]); }
	free(mat);

	return NULL;
}


//recebe numero total de macroblocos, tamanho da linha da matriz e tamanhos (linha e coluna) do macrobloco
//retorna ponteiro para vetor com as duas coordenadas
int* mc_coordenada(int num_mc, int mat_linha, int mc_linhaSize, int mc_colunaSize) {

	//futura resposta
	int coordenadas[2];

	//linha e coluna do macrobloco
	int l, c;

	//numero de macroblocos por linha
	int mc_por_linha = mat_linha / mc_linhaSize;

	//descobrindo linha e coluna do macrobloco
	if (num_mc % mc_por_linha == 0) {
		
		l = num_mc / mc_por_linha;
		c = mc_por_linha;
	}
	else {
		l = (num_mc / mc_por_linha) + 1;
		c = num_mc % mc_por_linha;
	}
	
	
	//calculo da resposta final
	coordenadas[0] = (l-1) * mc_linhaSize;
	coordenadas[1] = (c-1) * mc_colunaSize;

	return coordenadas;
}

//recebe um numero, retorna 1 (caso positivo) ou 0 (caso negativo)
int ehPrimo(int num) {

	int i;
	
	if (num <= 1) { return 0; }

	double raizNum = sqrt(num); //raiz quadrada do numero

	for (i = 2; i <= raizNum; i++) {
		if (num % i == 0) { return 0; } //nao eh primo
	}

	return 1; //eh primo
}


//cria vetor de macroblocos com zero (lembrar que o vetor comeca em zero e o macrobloco em 1)
char* vetorMacroblocos(int num_macroblocos) {
	
	char* atv_mc = calloc(num_macroblocos, sizeof(char));

	//verificar alocacao
	if (atv_mc == NULL) {
		
		printf("ERRO! No vetor de macroblocos\n");
		return NULL;
	}
	
	return atv_mc;
}


int main(int argc, char *argv[]) {
	
	printf("Sistemas operacionais - Trabalho 1\n");

	int** mat; //matriz
	int i,j;   //variaveis de apoio
	
	//numero de linhas e colunas da matriz
	int l = LINHAS;
	int c = COLUNAS;
	
	//numero de linhas e colunas dos macroblocos
	int mc_l = MC_LINHA;
	int mc_c = MC_COLUNA;

	//int* v; //vetor para receber coordenadas

	//tamanho maximo do numero dentro da matriz
	int max_num_size = MAX_NUM_SIZE;

	int numThreads = NUM_THREADS; //numero de threads

	//contador de numeros primos
	int contadorPrimos = 0;

	//armazena tempo de execucao
	double tempo_serial = 0.0;
	double tempo_paralelo = 0.0;


	//calculo do numero de macroblocos
	int num_macroblocos = (l / mc_l) * (c / mc_c);

	
	
	
	
	
	
	//cria vetor de macroblocos
	char* atv_mc = vetorMacroblocos(num_macroblocos);


	//cria matriz
	mat = matriz_inteiros(l, c);

	
	//povoa com randons
	printf("Povoando matriz com numeros aleatorios...");
	
	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {
			
			mat[i][j] = rand() % max_num_size;
		}
	}
	printf("DONE\n");

	//execucao em modo serial
	printf("EXECUCAO SERIAL:\n");
	printf("Contando numeros primos...");
	clock_t inicio = clock(); //inicio da execucao serial

	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {
			
			if (ehPrimo(mat[i][j]) == 1) {
				
				contadorPrimos++;
			}
		}
	}

	clock_t fim = clock(); //fim da execucao serial
	printf("DONE\n");

	tempo_serial += (double)(fim - inicio) / CLOCKS_PER_SEC;  //calculo do tempo

	printf("Numeros primos: %d\n", contadorPrimos);
	printf("Tempo de execucao serial: %f segundos\n", tempo_serial);



	contadorPrimos = 0; //zerando contador

	printf("EXECUCAO PARALELIZADA:\n");

	//criacao dos mutexes

	pthread_mutex_t mutex_prime;
	pthread_mutex_t mutex_mc;

	pthread_mutex_init(&mutex_prime, NULL);
	pthread_mutex_init(&mutex_mc, NULL);




	printf("to implement...\n");






	//libera matriz
	liberar_matriz(l, c, mat);

	//libera vetor de macroblocos
	free(atv_mc);

	//destruir mutexes
	pthread_mutex_destroy(&mutex_prime, NULL);
	pthread_mutex_destroy(&mutex_mc, NULL);

	printf("FIM :)\n");
	return 0;
}