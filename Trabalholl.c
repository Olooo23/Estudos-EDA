#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <sys/time.h>

#define QTDE_LINHAS 5
#define QTDE_COLUNAS 5
#define TAM_VETOR 5

// Ax = b
int Matriz[QTDE_LINHAS][QTDE_COLUNAS]; // Que necessariamente não é uma Matriz Quadrada.
int Vetor_x[TAM_VETOR];  // O tamanho do Vetor x deve ser igual ao numero de colunas da Matriz.
int Vetor_b[QTDE_LINHAS]; // O vetor resultado (B) deve ter o mesmo numero de linha da Matriz.
int Matriz_Temporaria[QTDE_LINHAS][QTDE_COLUNAS]; // Declarei como global pois estava dando falha de segmentação.


//Função para gerar a matriz e o vetor.
int Gera_Matriz_Vetor () {
	srandom(25);
	//Gera a Matriz.
	for (int i = 0; i < QTDE_LINHAS;i++) {
		for (int j = 0; j < QTDE_COLUNAS;j++) {
			Matriz[i][j] = random();
		}
	}
	//Gera o Vetor_x.
	for (int i = 0; i < TAM_VETOR;i++) {
		Vetor_x[i] = i+2;
	}
	//Gera o vetor b.
	for (int i = 0; i < QTDE_LINHAS;i++) {
		Vetor_b[i] = 0;
	}
	return 0;
}

// Multiplicação sequencial do vetor pela matriz.
// Implementa a função Ax=b e pega o tempo sequencial.
int matvecSequencial(){
	struct timeval tv1, tv2;
	double t1, t2;

	printf("Executando MatvecSequencial:\n");

	//Marcação do tempo Inicial.
	gettimeofday(&tv1, NULL);
	t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/1000000.00;

	//Faz a multiplicação e armazena em uma Matriz_Temporaria.
	for (int i = 0; i < QTDE_LINHAS;i++) {
		for (int j = 0; j < QTDE_COLUNAS;j++) {
			Matriz_Temporaria[i][j] = Matriz[i][j] * Vetor_x[j];
		}
	}
	//Gera o Vetor Resultante B
	for (int i = 0; i < QTDE_LINHAS;i++) {
		for (int j = 0; j < QTDE_COLUNAS;j++) {
			Vetor_b[i]+=Matriz_Temporaria[i][j];
		}
	}

	//Marcação do tempo após a função desejada.
	gettimeofday(&tv2,NULL);
	t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/1000000.00;

	printf("O tempo de execucao sequencial foi: %lf\n", (t2 - t1));
	return 0;
}


// Multiplicacao paralela (OpenMP) do vetor pela Matriz.
//Implementa a funcao Ax=b e coleta o tempo da execução em paralelo no OpenMP.

int matvecHost() {
	int Thread_ID, i, j;
	struct timeval tv1, tv2;
	double t1, t2;

	printf("\nExecutando MatvecHost: \n");

	//Zera o Vetor resultante (b) que já foi usado.
	for (int i = 0 ; i < QTDE_LINHAS;i++) {
		Vetor_b[i] = 0;
	}
	//Marcação do tempo Inicial.
	gettimeofday(&tv1, NULL);
	t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/1000000.00;

	#pragma omp parallel for shared(Vetor_b, Vetor_x, Matriz, Matriz_Temporaria, i) num_threads(QTDE_LINHAS) 
  	for (i = 0; i < QTDE_LINHAS; i++) {
    	for (int j = 0; j < QTDE_COLUNAS; j++) {
      		Matriz_Temporaria[i][j] = Vetor_x[j] * Matriz[i][j];
    	}
  	}
  	for (i = 0; i < QTDE_LINHAS;i++) {
  		for (j = 0; j < QTDE_COLUNAS; j++) {
  			Vetor_b[i]+=Matriz_Temporaria[i][j];
  		}
  	}

	gettimeofday(&tv2, NULL);
	t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/1000000.00;

	printf("O tempo de execucao OpenMP foi: %lf\n", (t2 - t1));
	
	return 0;
}

int matvecDevice() {
	printf("\nA função matvecDevice não está disponível\n");
}


int main() {
		matvecHost();
		for (int i = 0; i < QTDE_LINHAS;i++) {
			printf("%d ",Vetor_b[i]);
		}
}
