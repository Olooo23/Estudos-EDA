#include <iostream>
using namespace std;

void Min_Heapify (int Arranjo[], int index, int Tamanho_do_Heap) {
	int Esq = index*2 + 1;
	int Dir = index*2 + 2;
	int menor;
	if (Esq < Tamanho_do_Heap && Arranjo[Esq] < Arranjo[index]) {
		menor = Esq;
	}
	else {
		menor = index;
	}
	if (Dir < Tamanho_do_Heap && Arranjo[Dir] < Arranjo[menor]) {
		menor = Dir;
	}
	if (menor != index) {
		int aux = Arranjo[index];
		Arranjo[index] = Arranjo[menor];
		Arranjo[menor] = aux;
		Min_Heapify (Arranjo, menor, Tamanho_do_Heap);
	}
}

void ConstruirMinHeap(int Arranjo[], int Tamanho_do_Arranjo) {
	for (int i = (Tamanho_do_Arranjo/2) - 1; i >= 0;i--) {
		Min_Heapify (Arranjo, i, Tamanho_do_Arranjo);
	}
}

void HeapSort (int Arranjo[], int Tamanho_do_Arranjo) {
	for (int i = (Tamanho_do_Arranjo/2) - 1; i >= 0;i--) {
		Min_Heapify (Arranjo, i, Tamanho_do_Arranjo);
	}
	for (int i = Tamanho_do_Arranjo - 1; i >= 0;i--) {
		int aux = Arranjo[0];
		Arranjo[0] = Arranjo[i];
		Arranjo[i] = aux;
		Min_Heapify(Arranjo, 0, i);
	}
}

int main() {
	int A[28] = {1, 2, 3, 4 , 5, 6 , 7 ,8, 9, 10 ,11 ,12 ,13,14,15,16,17,18,19,20,30,40,50,60,70,80,90,100};
	HeapSort(A, 28);
	for (int i = 0; i < 28;i++) {
		cout << A[i]<<" ";
	}
	cout <<endl;
}
