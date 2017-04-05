#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct tipoElemento {
	char c;
	tipoElemento *acima, *abaixo;
}TElemento;

typedef struct tipoPilha {
	TElemento *topo, *fundo;
}TPilha;

void entrada(char *string);
int validaParentese(char *string, TPilha *pParenteses);
void zerarFrase(char *string);
void inicializa(TPilha *p);
int pilhaVazia(TPilha *p);
void empilha(TPilha *p, char string);
int desempilha(TPilha *p);
int validaOperacao(char *string);
int ehValor(char *string);
int ehNumero(char *string);
int ehOperador(char caractere);

int main(int argc, char** argv) {
	TPilha pParenteses;
	TPilha pGeral;
	int a = 1;
	char *string = (char *)malloc(sizeof(char));
	
	do {
		zerarFrase(string);
		entrada(string);
		inicializa(&pParenteses);
		inicializa(&pGeral);
		a = validaParentese(string, &pParenteses);
		
	} while (a == 1);
	
	validaOperacao(string);




	system("PAUSE");
	return 0;
}

void entrada(char *string) {
	printf("\n\t\tInsira a expressao de entrada: ");
	gets(string);
}

void zerarFrase(char *string) {
	string[0] = '\0';
}

void inicializa(TPilha *p) {
	p->topo = NULL;
	p->fundo = NULL;
}

int pilhaVazia(TPilha *p) {
	if (p->topo == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int validaParentese(char *string, TPilha *pParenteses) {
	int tam = strlen(string);

	for (int i = 0; i < tam; i++) {
		if ((string[i] == '(')) {
			empilha(pParenteses, string[i]);
		}
		else if (string[i] == ')') {
			if (pilhaVazia(pParenteses) == 1) {
				printf("\n\t\t PARENTESES VALIDADOS!");
				return 1;
				printf("\n\n\t\t\t %s \n\n", string);
				system("PAUSE");
			}
			else {
				desempilha(pParenteses);
			}
		}
	}

	if (pilhaVazia(pParenteses) == 1) {
		printf("\n\t\t PARENTESES VALIDADOS!");
		printf("\n\n\t\t\t %s \n\n", string);
	}
	else {
		printf("\n\t\t PARENTESES INVALIDOS!");
		printf("\n\n\t\t\t %s \n\n", string);
		return 1;
	}
	return 0;
}

int validaOperacao(char *string) {
	int tam = strlen(string);
	int i = 3;
	int j = 0;
	char *aux = (char*)malloc(sizeof(char*));
	zerarFrase(aux);

	if ((string[0] == '(') && (ehOperador(string[1]) == 0)) {
		if (string[2] == ' ') {
			if (string[i] == '(') {//separa a substring no caso de haver um P dentro do P
				while (string[i] != ')') {
					aux[j] = string[i];
					aux[j + 1] = ')';
					aux[j + 2] = '\0';
					j++;
					i++;
				}				
			}
			else {//separa a subtring caso seja um número
				while (string[i] != ' ') {
					int k = 0;
					aux[k] = string[i];
					aux[k + 1] = '\0';
					k++;
					i++;
				}
			}
			if (ehValor(aux) == 0){//se o primeiro V for um valor
				int h = 0;
				zerarFrase(aux);
				i++;
				while (string[i] != ')') {
					aux[h] = string[i];
					aux[h + 1] = '\0';
					h++;
					i++;
				}//end while
				
				if (ehValor(aux) == 0) {
					printf("\n\n\tPrograma validado!\n\n");
					return 0;
				}
				else {
					printf("\n\n\tSegundo valor invalido!\n\n");
					return 1;
				}
			}		
			else {
				printf("\n\n\tPrimeiro valor invalido!\n\n");
				return 1;
			}
		}
		else {
			printf(" \n\n\t Erro de sintaxe! falta espacamento.\n\n");
			return 1;
		}
	}
	else {
		printf("\n\n\t Erro de sintaxe!\n\n");
		//return 1;
	}
	
}

int ehValor(char *string) {
	if (validaOperacao(string) == 0) {
		return 0;
	}
	else if (ehNumero(string) == 0) {
		return 0;
	}
	else {
		printf("\n\n\t\t --- Valor invalido");
		return 1;
	}
}

int ehNumero(char *string) {
	int tam = strlen(string);
	int cont = 0;
	for (int i = 0; i < tam; i++) {
		
		if(string[i] == ' '){	
			cont++;
		} else{
			if ((string[i] >= 48) && (string[i] <= 57)) {
				cont++;
			
			}else {
				printf("\n\n\t\t --- Caractere %c nao numerico \n\n",string[i]);
				i = tam;
				return 1;
			}
		}
	}
	
	if (cont == tam) {
		return 0;
	}
}

int ehOperador(char caractere) {
	if ((caractere == '+') || (caractere == '-') || (caractere == '*') || (caractere == '/')) {
		return 0;
	}
	else {
		return 1;
	}
}

void empilha(TPilha *p, char string) {
	TElemento *novo = (TElemento *)malloc(sizeof(TElemento));
	novo->c = string;
	novo->acima = NULL;
	novo->abaixo = NULL;

	if (pilhaVazia(p)) {
		p->topo = novo;
		p->fundo = novo;
	}
	else {
		p->topo->acima = novo;
		novo->abaixo = p->topo;
		p->topo = novo;
	}
}

int desempilha(TPilha *p) {
	TElemento *atual = p->topo;
	int resultado = -1;
	if (!pilhaVazia(p)) {
		resultado = atual->c;
		p->topo = atual->abaixo;
		if (p->topo != NULL) {
			p->topo->acima = NULL;
		}
		else {
			p->fundo = NULL;
		}
		free(atual);
	}
	return resultado;
}
