#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>

#define QTDE_LINHAS 20
#define QTDE_COLUNAS 20
#define TAM_VETOR 20

// Ax = b
int Matriz[QTDE_LINHAS][QTDE_COLUNAS]; // nao precisa ser matriz quadrada
int Vetor_x[TAM_VETOR];  // tamanho do vetor x deve ser igual ao numero de colunas da matriz A
int Vetor_b[QTDE_LINHAS]; // vetor resultado (B) deve ter o mesmo numero de linha da matriz A
int Matriz_Temporaria[QTDE_LINHAS][QTDE_COLUNAS];

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

	gettimeofday(&tv2,NULL);
	t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/1000000.00;

	printf("O tempo de execucao sequencial foi: %lf\n", (t2 - t1));
	return 0;
}

// Multiplicacao paralela (OpenMP) do vetor pela matriz.
//Implementa a funcao Ax=b e coleta o tempo paralelo em OpenMP.

int matvecHost() {
	int tid, i, j;
	struct timeval tv1, tv2;
	double t1, t2;

	printf("\nExecutando MatvecHost: \n");

	for (int i = 0 ; i < QTDE_LINHAS;i++) {
		Vetor_b[i] = 0;
	}
	//Marcação do tempo Inicial.
	gettimeofday(&tv1, NULL);
	t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/1000000.00;

	#pragma omp parallel for shared(i) num_threads(QTDE_LINHAS) private(tid)
  	for (i = 0; i < QTDE_LINHAS; i++)
	 {
	   for (int j = 0; j < QTDE_COLUNAS; j++)
	   {
	     //tid = omp_get_thread_num();
	     //printf("\nTHREAD: %d LINHA: %d COLUNA: %d",tid,i,j);
	     Vetor_b[i] += Vetor_x[j] * Matriz[i][j];
	   }
  }

	gettimeofday(&tv2, NULL);
	t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/1000000.00;

	printf("O tempo de execucao OpenMP foi: %lf\n", (t2 - t1));
	
	return 0;
}

int matvecDevice() {
}


int main() {
	Gera_Matriz_Vetor();
	matvecSequencial();
	matvecHost();

	printf("\n");
}
