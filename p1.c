#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
		return 0;
	}
	return (NoAltura -> altura);
}

//Função para obter o balnaço.
int FatorBalanco (No* Noo) {
    if (Noo == NULL) {
        return 0;
    }
    return (Altura(Noo->Esq) - Altura(Noo->Dir));
}

//Função para criar um No.
No* CriarNo(int contedoNovo) {
	No* novo = (No*)malloc(sizeof(No));
	novo->conteudo = contedoNovo;
	novo->Dir = NULL;
	novo->Esq = NULL;
	novo->altura = 1;
	return novo;
}

//Função para criar uma ÁrvoreAVL.
ArvoreAVL* CriarArvoreAVL() {
	ArvoreAVL* nova = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
	nova -> Raiz = NULL;
	return nova;
}

//Função para rotação a Direita.
No* RotaDireita (No* x) {
	No* aux = x -> Esq;
	x -> Esq = aux -> Dir;
	aux -> Dir = x;

	x -> altura = (Max(Altura(x->Esq), Altura(x->Dir)) + 1);
	aux -> altura = (Max(Altura(x -> Esq), Altura(x -> Dir)) + 1);

	return aux;
}

//Função para rotação a Esquerda.
No* RotaEsquerda (No* x) {
	No* aux = x -> Dir;
	x -> Dir = aux -> Esq;
	aux -> Esq = x;

	x -> altura = (Max(Altura(x->Esq), Altura(x->Dir)) + 1);
	aux -> altura = (Max(Altura(x -> Esq), Altura(x -> Dir)) + 1);

	return aux;
}

//Função para Inserir No.
No* InserirAVL (No* Raiz, int Chave) {
    if (Raiz == NULL) {
        return CriarNo(Chave);
    }
    if (Chave < Raiz->conteudo) {
        Raiz -> Esq = InserirAVL(Raiz->Esq, Chave);
    }
    else if (Chave > Raiz->conteudo) {
        Raiz->Dir = InserirAVL(Raiz->Dir, Chave);
    }
    else {
        return Raiz;
    }

    Raiz->altura = (1 + (Max(Altura(Raiz->Esq), Altura(Raiz->Dir))));

    int Fb = FatorBalanco(Raiz);

    if (Fb > 1 && Chave < Raiz->Esq->conteudo) {
        return RotaDireita(Raiz);
    }
    if (Fb < -1 && Chave > Raiz -> Dir->conteudo) {
        return RotaEsquerda(Raiz);
    }
    if (Fb > 1 && Chave > Raiz->Esq->conteudo) {
        Raiz->Esq = RotaEsquerda(Raiz->Esq);
        return RotaDireita(Raiz);

    }
    if (Fb < -1 && Chave < Raiz->Dir->conteudo) {
        Raiz->Dir = RotaDireita (Raiz->Dir);
        return RotaEsquerda(Raiz);
    }
    return Raiz;

}

void PreOrdem (No* Raiz) {
    if (Raiz == NULL) {
        return;
    }
    printf("%d ", Raiz->conteudo);
    PreOrdem (Raiz->Esq);
    PreOrdem(Raiz->Dir);
}

void PosOrdem (No* Raiz) {
    if (Raiz == NULL) {
        return;
    }
    PosOrdem (Raiz->Esq);
    PosOrdem(Raiz->Dir);
    printf("%d ", Raiz->conteudo);
}

void EmOrdem (No* Raiz) {
    if (Raiz == NULL) {
        return;
    }
    EmOrdem (Raiz->Esq);
    printf("%d ", Raiz->conteudo);
    EmOrdem(Raiz->Dir);
}

No* ConsultaNo(No* Raiz, int Chave) {
    if (Raiz == NULL || Chave == Raiz->conteudo) {
        return Raiz;
    }
    if (Chave < Raiz->conteudo) {
        return ConsultaNo (Raiz->Esq, Chave);
    }
    else {
        return ConsultaNo(Raiz->Dir, Chave);
    }
}


int Distancia (No* Raiz, int x, int y) {
    int maior, menor;
    if (x > y) {
        maior = x;
        menor = y;
    }
    else {
        maior = y;
        menor = x;
    }
}
int main() {
	ArvoreAVL* Minha = CriarArvoreAVL();
	Minha -> Raiz = InserirAVL(Minha->Raiz, 10);
	Minha -> Raiz = InserirAVL(Minha->Raiz, 5);
	Minha -> Raiz = InserirAVL(Minha->Raiz, 30);
	Minha -> Raiz = InserirAVL(Minha->Raiz, 1);
	Minha -> Raiz = InserirAVL(Minha->Raiz, 6);
	Minha -> Raiz = InserirAVL(Minha->Raiz, 9);
    if (ConsultaNo(Minha->Raiz,99) != NULL) {
        printf("Acho\n");
    }
    else {
        printf("Taqui n\n");
    }
    EmOrdem(Minha->Raiz);
    printf("\n");
}