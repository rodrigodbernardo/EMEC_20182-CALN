#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef int bool;
#define true 1
#define false 0

/*
Equipe:
Elias Paulino Andrade
Francisco Juarez da Silva Junior
Gilmaicor Leandro
Messyo Sousa Brito
*/


typedef struct Equacao{
    float *coeficientes;
    int grau;
    int tamanho;
} Equacao;

#define EPSILON 0.00000001

double **alocaMatriz(int l, int c){
//	Se houver memoria disponivel, aloca dinamicamente uma matriz de double com l linhas e c colunas e devolve
//	um ponteiro para essa matriz. Caso contrario devolve um ponteiro nulo
	int i,j;
	double **m;
	m = malloc(sizeof(m)*l);
	if (m == NULL) //falta de memoria
		return NULL;
	for (i = 0; i < l; i++){
		m[i] = malloc(sizeof(double)*c);
		if(m[i] == NULL){ //falta de memoria
			for(j = 0; j < i; j++)
				free(m[j]);
			free(m);
			return NULL;
		}
	}
	return m;
}

void imprimeMatriz(double **m, int l, int c){
//	imprime o conteudo de uma matriz de double alocada dinamicamente, com l linhas e c
//	colunas
	int i,j;
	for(i = 0; i < l; i++){
		for (j = 0; j < c; j++){
			printf("%10.3lf ", m[i][j]);
		}
		printf("\n");
	}
}

void desalocaMatriz(double **m, int l, int c){
//	Desaloca o conteudo de uma matriz de double, com l linhas e c
//	colunas
	int i,j;
	for(i = 0; i < l; i++){
//		for (j = 0; j < c; j++){
//			free(m[i][j]);
//		}
		free(m[i]);
	}
    free(m);
}

void lerMatriz(double **m, int l, int c){
//	Le valores para uma matriz de double alocada dinamicamente com l linhas e c colunas
	int i,j;
    FILE *fp;
    int aux;
    fp = fopen("arquivo.txt", "r");
    fscanf(fp, "%d", &aux);
	for(i = 0; i < l; i++){
		for(j = 0; j < c; j++){
            fscanf(fp, "%lf", &m[i][j]);
		}
	}
    fclose(fp);
}

int sRetro(double **m, int n, double x[]){
	/*Recebe m, a matriz aumentada de SLTS com n variaveis.
	Se o SL for determinado, coloca em x a solucao de SL e devolve 0;
	Se for indetermiondo, coloca em x uma solucao do SL e devolve 1;
	Se for incopativel, devolve 2; */
	int i, j, tipo=0;
	double soma;

	for (i=n-1; i>=0; i--){
		soma=0;
		for (j=i+1; j<n; j++){
			soma=soma + m[i][j]*x[j];
        }
        if (m[i][i]==0){
            if (fabs(m[i][n]-soma)<EPSILON){
                x[i]=0; // Variavel livre;
                tipo=1;
            } else {
                return 2; // SL incompativel;
            }
        } else {
            x[i]=(m[i][n]-soma)/m[i][i];
        }

	}
	return tipo;
}
int *metodoDeJordan(double **m, int n){
    /*Essa funcao recebe uma matriz de double m, contendo a matriz aumentada de um sistema
    linear, e um inteiro n, com a ordem desse sistema, e transforma a matriz em uma matriz
    diagonal equivalente, seguindo o metodo de Jordan. Retorna um vetor de inteiros com a
    ordem das variaveis*/
    int i, j, k, aux2;
    double mult, aux;
    int *posicao_variaveis;
    posicao_variaveis = malloc(sizeof(int)*n);

    for(i = 1; i < n+1; i++){
        posicao_variaveis[i-1] = i;
    }

    for(i = 0; i <= n-1; i++){

        if(m[i][i] == 0){

            j = i+1;
            while(j < n && m[i][j] == 0)
                j++;
            if(j < n){

                aux2 = posicao_variaveis[i];
                posicao_variaveis[i] = posicao_variaveis[j];
                posicao_variaveis[j] = aux2;
                for(k = 0; k < n; k++){

                    aux = m[k][i];
                    m[k][i] = m[k][j];
                    m[k][j] = aux;

                }

            }
            else{

                for(k = 0; k < n; k++){

                    m[k][i] = 0;

                }

            }
        }
        if(m[i][i] != 0){

            for(j = 0; j <= n-1; j++){
                if(j == i)
                    j++;
                if(j <= n-1){

                    mult = (-1)*(m[j][i]/m[i][i]);
                    m[j][i] = 0;
                    for(k = i+1; k < n+1; k++){
                        m[j][k] = (m[i][k]*mult)+m[j][k];

                    }
                }
            }
        }
    }
    return posicao_variaveis;
}
void sistemaLinear(char* arquivo){
    /*Essa funcao recebe o nome de um arquivo com a ordem e a matriz aumentada de um sistema
    linear, transforma a matriz aumentada em uma matriz diagonal equivalente e resolve o
    sistema linear com o metodo da substituicao retroativa*/
    int n,f,tipo,aux,i;
    int *posicao_variaveis;
    char string[255];
    double **m, *x, aux2;
    FILE *fp;
    fp = fopen(arquivo, "r");
    fscanf(fp, "%s", string);
    fclose(fp);

    n = atoi(string);
    m = alocaMatriz(n, n+1);
    x = malloc(sizeof(double)*n);

    lerMatriz(m,n,n+1);

    printf("Matriz aumentada\n");
    imprimeMatriz(m,n,n+1);

    posicao_variaveis = metodoDeJordan(m,n);

    printf("Matriz diagonal\n");
    imprimeMatriz(m,n,n+1);

    tipo=sRetro(m, n, x);

    for(i = 1; i < n; i++){

        if(i != posicao_variaveis[i-1]){

            aux2 = x[i];
            x[i] = x[i-1];
            x[i-1] = aux2;
            aux = posicao_variaveis[i-1];
            posicao_variaveis[i-1] = posicao_variaveis[i];
            posicao_variaveis[i] = aux;

        }

    }

    printf("\n");
    if (tipo==2){
        printf("SL incompativel");
    }
    else {
        printf("SL %sdeterminado\n", tipo?"In":"");
        for (f=0; f<n; f++){
            printf("x[%d]=%10.3lf\n", f+1, x[f]);
        }
    }
    free(posicao_variaveis);
    free(x);
    desalocaMatriz(m,n,n+1);

}

int mostrarSecaoSistemaLinear(){
    char arquivo[255];
    printf("\nDigite o nome do arquivo:");
    scanf(" %s", arquivo);
    strcat(arquivo, ".txt");
    sistemaLinear(arquivo);
    return 0;
}
int main(){
    char entrada;
    bool continuarLaco = true;
    while(continuarLaco){
        printf("C - Conversao\n");
        printf("S - Sistema Linear\n");
        printf("E - Equacao Algebrica\n");
        printf("F - Finalizar\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &entrada);
        switch(entrada){
            case 'S':
                mostrarSecaoSistemaLinear();
                break;
        }

    }

}
