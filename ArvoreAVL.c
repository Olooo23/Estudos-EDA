#include <stdlib.h>
#include <stdio.h>

//Estrutura do No.
typedef struct s_no {
	int conteudo;
	int altura;
	struct s_no *Dir;
	struct s_no *Esq;
}No;

//Estrutura para ÁrvoreAVL.
typedef struct s_arvore {
	No* Raiz;
}ArvoreAVL;

//Função auxiliar MAX.
int Max (int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

//Função auxiliar Altura.
int Altura (No* NoAltura) {
	if (NoAltura == NULL) {
		return -1;
	}
	return NoAltura -> altura;
}

//Função para criar um No.
No* CriarNo(int contedoNovo) {
	No* novo = (No*)malloc(sizeof(No));
	novo->conteudo = contedoNovo;
	novo->Dir = NULL;
	novo->Esq = NULL;
	novo->altura = 0;
	return novo;
}

//Função para criar uma ÁrvoreAVL.
ArvoreAVL* CriarArvoreAVL() {
	ArvoreAVL* nova = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
	nova -> Raiz = NULL;
	return nova;
}

//Função para rotação a Direita.
No* RotaDireita (No* Desbalanciado) {
	No* aux = Desbalanciado -> Esq;
	Desbalanciado -> Esq = aux -> Dir;
	aux -> Dir = Desbalanciado;

	Desbalanciado -> altura = (Max(Altura(Desbalanciado -> Dir), Altura(Desbalanciado -> Esq)) + 1);
	aux -> altura = (Max(Altura(aux -> Dir), Altura(aux -> Esq)) + 1);

	return aux; 
}	

//Função para rotação a Esquerda.
No* RotaEsquerda (No* Desbalanciado) {
	No* aux = Desbalanciado -> Dir;
	Desbalanciado -> Dir = aux -> Esq;
	aux -> Esq = Desbalanciado;

	Desbalanciado -> altura = (Max(Altura(Desbalanciado -> Dir), Altura(Desbalanciado -> Esq)) + 1);
	aux -> altura = (Max(Altura(aux -> Dir), Altura(aux -> Esq)) + 1);

	return aux;
}

//Função para rotação EsquerdaDireita.
No* RotaEsquerdaDireita (No* Desbalanciado) {
	Desbalanciado -> Esq = RotaEsquerda(Desbalanciado -> Esq);
	return RotaDireita(Desbalanciado);
}

//Função para rotação DireitaEsquerda.
No* RotaDireitaEsquerda (No* Desbalanciado) {
	Desbalanciado -> Dir = RotaDireita(Desbalanciado -> Dir);
	return RotaEsquerda(Desbalanciado);
}

int main() {
	ArvoreAVL* Minha = CriarArvoreAVL();
}