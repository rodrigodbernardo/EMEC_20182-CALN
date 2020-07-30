#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

# define epsilon 0.000001

double **alocaMatriz(int L, int C){
	
	double **m;
	int i,j;
	m = malloc(sizeof(double*)*L);
	
	if (m == NULL){return NULL;}
	
	for (i = 0; i < L; i++){
		m[i] = malloc(sizeof(double) *C);
		
		if(m[i] == NULL){
			for (j=0;j<i;j++){
				free(m[j]);}
			free(m);
			return NULL;
		}
	}
	return m;
}
	
void leMatriz (double **m, int L, int C){
    int i,j,aux;
    FILE *fp;
    fp = fopen("arquivo.txt", "r");
    fscanf(fp, "%d", &aux);
	  for(i = 0; i < L; i++){
		for(j = 0; j < C; j++){
      fscanf(fp, "%lf", &m[i][j]);
		}
	}
    fclose(fp);
}

void imprimeMatriz(double **m, int L, int C){
	int i,j;
	for(i=0;i<L;i++){
		for(j=0;j<C;j++)
		{printf("%10.3lf ", m[i][j]);}
		printf("\n");
	}
}
	
int sretro(double **m,int n, double x[]){
	int	i, j, tipo = 0;
	double soma;
	for( i= n-1;i>=0;i--){
		soma = 0;
		for (j = i+1; j<n; j++){soma += m[i][j] *x[j];}
		if (m[i][i] == 0){
		  if (fabs(m[i][j] - soma)< epsilon){
			  x[i] = 0;
			  tipo = 1;
		  }else {return 2;}
	  }
			else { x[i] = (m[i][n] - soma)/m[i][i];}
		}
	return tipo;
}

int *Jordan(double **m, int n){
  int i, j, k, aux2;
  double mult, aux;
  int *pos_var;
  pos_var = malloc(sizeof(int)*n);

  for(i = 1; i < n+1; i++){
    pos_var[i-1] = i;
  }
  for(i = 0; i <= n-1; i++){
    if(m[i][i] == 0){
      j = i+1;
      while(j < n && m[i][j] == 0){
        j++;  
      }  
      if(j < n){
        aux2 = pos_var[i];
        pos_var[i] = pos_var[j];
        pos_var[j] = aux2;
        for(k = 0; k < n; k++){
          aux = m[k][i];
          m[k][i] = m[k][j];
          m[k][j] = aux;
        }
      }else{
        for(k = 0; k < n; k++){
          m[k][i] = 0;
        }
      }
    }
    if(m[i][i] != 0){
      for(j = 0; j <= n-1; j++){
        if(i == j){
          j++;
        }
        if(j <= n-1){
          mult = -m[j][i]/m[i][i];
          m[j][i] = 0;
          for(k = i+1; k < n+1; k++){
            m[j][k] += mult*m[i][k];
          }
        }
      }
    }
  }
  return pos_var;
}

int finalmenteJordan(){

  
  printf("\n\nMetodo de Jordan\n\n");

  char  arquivo[255];
  printf("\nDigite o nome do arquivo:");
  scanf(" %s", arquivo);
  strcat(arquivo, ".txt");

  char string[255];
  int i, n, tipo, aux;
  int *pos_var;
  double **m, *x, aux2;

  FILE *fp;
  fp = fopen(arquivo, "r");
  fscanf(fp, "%s", string);
  fclose(fp);

  n = atoi(string);
  m = alocaMatriz(n,n+1);
  x = malloc(sizeof(double) *n);

  if (m == NULL || x == NULL){
	  printf("Deu Pau! \nFalta de memoria\n");
	  return 1;
  }

  leMatriz(m,n,n+1);
  
  printf("\n\n");
  imprimeMatriz(m,n,n+1);
  
  pos_var = Jordan(m,n);
  
  printf("\n\nMatriz diagonal:\n\n");
  imprimeMatriz(m,n,n+1);
  
  tipo = sretro(m,n,x);
  
  for(i = 1; i < n; i++){
    if(i != pos_var[i-1]){
      aux2 = x[i];
      x[i] = x[i-1];
      x[i-1] = aux2;
      aux = pos_var[i-1];
      pos_var[i-1] = pos_var[i];
      pos_var[i] = aux;
    }
  }

  
  if(tipo == 2){
	  printf("\nSL incompativel\n");
  }else{
    printf("\nSL %sdeterminado\n",tipo ? "in":"");	for (i = 0; i<n; i++){
	    printf("\nx [%d] = %10.3lf\n", i+1,x[i]);
    }
  }
  printf("\nTipo : %i", tipo);
  return 0;
}

int main(){
  finalmenteJordan();
  return 0;	
}