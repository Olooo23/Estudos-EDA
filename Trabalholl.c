#include <stdlib.h>
#include <stdio.h>

#define QTDE_LINHAS 5
#define QTDE_COLUNAS 5
#define TAM_VETOR 80

// Ax = b
int Matriz[QTDE_LINHAS][QTDE_COLUNAS]; // nao precisa ser matriz quadrada
int Vetor_x[TAM_VETOR];  // tamanho do vetor x (unknowns) deve ser igual ao numero de colunas da matriz A
int Vetor_b[QTDE_LINHAS]; // vetor resultado (B) deve ter o mesmo numero de linha da matriz A


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
}

// Multiplicação sequencial do vetor pela matriz.
// Implementa a função Ax=b e pega o tempo sequencial.
double matvecSequencial(){

}




int main() {

	Gera_Matriz_Vetor();

	for (int i = 0;i < TAM_VETOR;i++) {
	printf("%d ", Vetor_b[i]);
	}
	printf("\n");
}