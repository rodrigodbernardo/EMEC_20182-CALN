/*
	##### FIRST EXERCISE-PROGRAM NUMERICAL CALCULATION #####
	
	STUDENTS:	Diego da Silva Cassiano - 20162015010100;
				Marcus Vinícius Freitas Veras - 20162015010223;
				Renatson Freitas Germano - 20161015010241;
				Rodrigo Douglas Bernardo de Araújo - 20162015010231.
	
	INSTRUCTOR:	Glauber Cintra.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define epsilon 0.000001
#define maximumError 0.00000001

void mainMenu();

// ##### START TOPIC 01 - CONVERSION #####
void convertDecimalNumberTo(double number, int numericalBase) {
	/*
		This function receives a number, and a numerical base;
		With this data, the function will convert this number to the given numerical base;
		For the integer part of the number, the function will perform successive divisions for the given numerical base. The function will perform infinite interactions so that the integer part of the number is no longer divisible by the given numerical base;
		For the fractional part, if it exists, the function will perform successive multiplications by the given numerical base. The function will perform '20' iterations, or until the fractional part of the number equals to '0'.	
	*/
	
	// ##### FUNCTION'S VARIABLES #####
    // Vector for conversion from integer to hexadecimal;
	char alphabeticalHexadecimalBase[6] = {'A', 'B', 'C', 'D', 'E', 'F'};						
		
	int integerDecimalBase[32];			// Vector to store integer bits positions;
	int fractionalDecimalBase[32];		// Vector to store fractional bits positions;
	
	int auxiliaryVariable;				// Auxiliary Variable;
	
	int endIntegerVector = 0;			// Variable to define the end of the integer part vector;
	int endFractionalVector = 0;		// Variable to define the end of the fractional part vector;
	
	int integerPart = abs((int)number); // Variable to store the absolute value of the integer part;
	
    // Variable to store the absolute value of the fractional part;
	double fractionalPart = fabs(number) - integerPart;											
	
	// ##### FUNCTION'S BODY #####
    // The function stores the last number of the integer part, from the division of the given number with the numeric base desired;
	integerDecimalBase[endIntegerVector] = integerPart % numericalBase;							
	endIntegerVector++;
	
    // The function will hold a loop of successive divisions, while the integer part of the given number is greater than or equal to the desired numeric base;
	while(integerPart >= numericalBase) {														
		integerPart /= numericalBase;
		integerDecimalBase[endIntegerVector] = integerPart % numericalBase;
		endIntegerVector++;
	}
	// The function will hold a loop of successive multiplications, while the fractional part of the given number, if it exists, is different from '0' or when '20' iterative multiplications are perform;
	while(!(fractionalPart == 0.0) && endFractionalVector < 20) {								
		fractionalPart *= numericalBase;
		fractionalDecimalBase[endFractionalVector] = (int)fractionalPart;
		fractionalPart -= (int)fractionalPart;
		endFractionalVector++;
	}
	
	if(number < 0) {					// The function will analyze whether the given number is positive or negative;
		printf("[1]");					// If true, the function will print '[1]' before the converted number;
	}
	
    // The function will scan from (endIntegerVector - 1) to 0;
	for(auxiliaryVariable = endIntegerVector - 1; auxiliaryVariable >= 0; auxiliaryVariable--) {
        // The function will analyze whether, in the conversion process, there are numbers greater than '9';
		if(integerDecimalBase[auxiliaryVariable] > 9) {
            // If true, the function it will convert to the hexadecimal base;											
			printf("%c", alphabeticalHexadecimalBase[integerDecimalBase[auxiliaryVariable] - 10]);
		} else {
            // Otherwise, the function it will convert to the binary and octal bases;
			printf("%d", integerDecimalBase[auxiliaryVariable]);								
		}
	}
	// The function will analyze whether the given number has a fractional part;
	if(number - (int)number != 0.0) {															
		printf(".");					// If the given number has a fractional part, the function will separate the integer part from the fractional part by a dot;
		
        // If there is a fractional part, the function will scan from 0 to (endFractionalVector - 1);
		for(auxiliaryVariable = 0; auxiliaryVariable <= endFractionalVector - 1; auxiliaryVariable++) {	
            // The function will analyze whether, in the conversion process, there are numbers greater than '9';
			if(fractionalDecimalBase[auxiliaryVariable] > 9) {			
                // If true, the function it will convert to the hexadecimal base;						
				printf("%c", alphabeticalHexadecimalBase[fractionalDecimalBase[auxiliaryVariable] - 10]); 
			} else {
                // Otherwise, the function it will convert to the binary and octal bases.
				printf("%d", fractionalDecimalBase[auxiliaryVariable]);							
			}
		}
	}
	printf("\n");
}

void conversion() {
	/*
		This function receive a user's decimal number;
		This given number is converted to the binary, octal and hexadecimal bases;
		When the given number is negative, a digit will be placed at the beginning of the converted number, as a representation of the signal.
	*/
	
	// ##### FUNCTION'S VARIABLE #####
	double currentNumber;
	
	// ##### FUNCTION'S BODY #####
	system("CLS");
	
	printf("\n\t##### CONVERSION #####\n");
	printf("\n\tType a decimal number to convert.");
	printf("\n\t[if the number isn't integer, use a comma to separate the integer part from fractional part].");
	printf("\n\t>> ");
	
	scanf("%lf", &currentNumber);
	
	printf("\n\tThe digit inside the bracket represents the numeric signal.");
	printf("\n\t[The number '1' represents the negative signal].");
	printf("\n\t[The number '0' represents the positive signal, but this information will not be printed].\n");
	
	printf("\n");
	printf("\t# BINARY: ");
	convertDecimalNumberTo(currentNumber, 2);
	
	printf("\t# OCTAL: ");
	convertDecimalNumberTo(currentNumber, 8);
	
	printf("\t# HEXADECIMAL: ");
	convertDecimalNumberTo(currentNumber, 16);
	
	printf("\n\t");
	system("PAUSE");
	
	mainMenu();
}
// ##### ENDS TOPIC 01 - CONVERSION #####

// ##### STARTS TOPIC 02 = LINEAR SYSTEM #####
// Starts allocateMatrix.
double **allocateMatrix(int rows_L, int columns_C) {
	/*
		If memory is available, allocate a double array with 'L' rows and 'C' columns and returns a pointer to the array.
		Otherwise, it returns a null pointer.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int i_auxiliaryVariable;
	int j_auxiliaryVariable;
	
	double **m;
	
	// ##### FUNCTION'S BODY #####
	m = malloc(sizeof(double*) *rows_L);
	
	// Lack of memory.
	if(m == NULL) {
		return NULL;
	}
	
	for(i_auxiliaryVariable = 0; i_auxiliaryVariable < rows_L; i_auxiliaryVariable++) {
		m[i_auxiliaryVariable] = malloc(sizeof(double) *columns_C);
		
		// Lack of memory.
		if(m[i_auxiliaryVariable] == NULL) {
			for(j_auxiliaryVariable = 0; j_auxiliaryVariable < i_auxiliaryVariable; j_auxiliaryVariable++) {
				free(m[j_auxiliaryVariable]);
			}
			free(m);
			
			return NULL;
		}
	}
	return m;
}
// Ends allocateMatrix.

// Starts readMatrix.
void readMatrix(double **m, int rows_L, int columns_C, char* currentFile) {
	/*
		This function reads values for a dynamically allocated double matrix with 'L' rows and 'C' columns.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
    int i_auxiliaryVariable;
	int j_auxiliaryVariable;
	
	int auxiliaryVariable;
	
    FILE *file;
    
    // ##### FUNCTION'S BODY #####
    file = fopen(currentFile, "r");
    
    fscanf(file, "%d", &auxiliaryVariable);
    
	for(i_auxiliaryVariable = 0; i_auxiliaryVariable < rows_L; i_auxiliaryVariable++) {
		for(j_auxiliaryVariable = 0; j_auxiliaryVariable < columns_C; j_auxiliaryVariable++) {
      		fscanf(file, "%lf", &m[i_auxiliaryVariable][j_auxiliaryVariable]);
		}
	}
    fclose(file);
}
// Ends readMatrix.

// Starts printMatrix.
void printMatrix(double **m, int rows_L, int columns_C) {
	/*
		This function prints the contents of a dynamically allocated double matrix with 'L' rows and 'C' columns.
	*/
	
	// ##### FUNCTION'S VARIABLE #####
	int i_auxiliaryVariable;
	int j_auxiliaryVariable;
	
	// ##### FUNCTION'S BODY #####
	for(i_auxiliaryVariable = 0; i_auxiliaryVariable < rows_L; i_auxiliaryVariable++) {
		for(j_auxiliaryVariable = 0; j_auxiliaryVariable < columns_C; j_auxiliaryVariable++){
			printf("   %10.3lf", m[i_auxiliaryVariable][j_auxiliaryVariable]);
		}	
		printf("\n");
	}
}
// Ends printMatrix.
	
// Starts linearSystemBackSubstitution.
int linearSystemBackSubstitution(double **m, int n_variables, double x[]) {
	/*
		This function receives 'm', the increased matrix of a linear system with 'n' variables.
		If the linear system is determined, stores the linear system's solution in the variable 'x' and return '0'.
		If the linear system is indeterminate, stores the linear system's solution and returns '1'.
		If the linear system is incompatible, returns '2'.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int	i_auxiliaryVariable;
	int j_auxiliaryVariable;
	
	int solutionType = 0;
	
	double auxiliarySum;
	
	for(i_auxiliaryVariable = (n_variables - 1); i_auxiliaryVariable >= 0; i_auxiliaryVariable--) {
		auxiliarySum = 0;
		
		for(j_auxiliaryVariable = (i_auxiliaryVariable + 1); j_auxiliaryVariable < n_variables; j_auxiliaryVariable++) {
			auxiliarySum += (m[i_auxiliaryVariable][j_auxiliaryVariable] * x[j_auxiliaryVariable]);
		}
		
		if(m[i_auxiliaryVariable][i_auxiliaryVariable] == 0) {
			if(fabs(m[i_auxiliaryVariable][j_auxiliaryVariable] - auxiliarySum) < epsilon) {
				x[i_auxiliaryVariable] = 0;
				
				solutionType = 1;
			} else {
				return 2;
			}
		} else {
			x[i_auxiliaryVariable] = (m[i_auxiliaryVariable][n_variables] - auxiliarySum) / m[i_auxiliaryVariable][i_auxiliaryVariable];
		}
	}
	return solutionType;
}
// Ends linearSystemBackSubstitution.

// Starts calculateByJordanMethod.
int *calculateByJordanMethod(double **m, int n_variables) {
	/*
		This function receives 'm', the increased matrix of a linear system with 'n' variables.
		This function will transforms the increased matrix in an equivalent diagonal matrix by the Jordan Method.
		Then the function will returns the order of the variables in a vector of integers.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int i_auxiliaryVariable;
	int j_auxiliaryVariable;
	int k_auxiliaryVariable;
	
	int auxiliaryVariable;
	
	int *integerVector;
	
	double multiplier;
	
	double auxiliaryVariable_2;
	
	// ##### FUNCTION'S BODY #####
	integerVector = malloc(sizeof(int) *n_variables);
	
	for(i_auxiliaryVariable = 1; i_auxiliaryVariable < (n_variables + 1); i_auxiliaryVariable++) {
		integerVector[i_auxiliaryVariable - 1] = i_auxiliaryVariable;
	}
	
	for(i_auxiliaryVariable = 0; i_auxiliaryVariable <= (n_variables - 1); i_auxiliaryVariable++) {
    	if(m[i_auxiliaryVariable][i_auxiliaryVariable] == 0) {
			j_auxiliaryVariable = i_auxiliaryVariable + 1;
			
			while(j_auxiliaryVariable < n_variables && m[i_auxiliaryVariable][j_auxiliaryVariable] == 0) {
				j_auxiliaryVariable++;
			}
			
			if(j_auxiliaryVariable < n_variables) {
				auxiliaryVariable = integerVector[i_auxiliaryVariable];
				
				integerVector[i_auxiliaryVariable] = integerVector[j_auxiliaryVariable];
				integerVector[j_auxiliaryVariable] = auxiliaryVariable;
				
				for(k_auxiliaryVariable = 0; k_auxiliaryVariable < n_variables; k_auxiliaryVariable++) {
					auxiliaryVariable_2 = m[k_auxiliaryVariable][i_auxiliaryVariable];
					
					m[k_auxiliaryVariable][i_auxiliaryVariable] = m[k_auxiliaryVariable][j_auxiliaryVariable];
					m[k_auxiliaryVariable][j_auxiliaryVariable] = auxiliaryVariable_2;
				}
			} else {
				for(k_auxiliaryVariable = 0; k_auxiliaryVariable < n_variables; k_auxiliaryVariable++) {
					m[k_auxiliaryVariable][i_auxiliaryVariable] = 0;
				}
			}
		}
		
		if(m[i_auxiliaryVariable][i_auxiliaryVariable] != 0) {
			for(j_auxiliaryVariable = 0; j_auxiliaryVariable <= (n_variables - 1); j_auxiliaryVariable++) {
				if(i_auxiliaryVariable == j_auxiliaryVariable) {
					j_auxiliaryVariable++;
				}
				
				if(j_auxiliaryVariable <= (n_variables - 1)) {
					multiplier = (-m[j_auxiliaryVariable][i_auxiliaryVariable] / m[i_auxiliaryVariable][i_auxiliaryVariable]);
				
					m[j_auxiliaryVariable][i_auxiliaryVariable] = 0;
				
					for(k_auxiliaryVariable = (i_auxiliaryVariable + 1); k_auxiliaryVariable < (n_variables + 1); k_auxiliaryVariable++) {
						m[j_auxiliaryVariable][k_auxiliaryVariable] += (multiplier * m[i_auxiliaryVariable][k_auxiliaryVariable]);
					}
				}
			}
		}
	}
	return integerVector;
}
// Ends calculateByJordanMethod.

// Starts linearSystem.
int linearSystem() {
	/*
		This function receives the name of a file containing the matrix.
		Then, the function reads it by the function: readMatrix, and with the function: printMatrix, prints it.
		After that, the function receives the matrix transformed by the function: calculateByJordanMethod,
		and prints it according to the function: printMatrix.
		Finally, the function receives the position of the variables, organizes it, and classifies the system,
		according to the results of the function: linearSystemBackSubstitution.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	char file[255];
	char fileContent[255];
	
	int n_variables;
	int solutionType;
	int i_auxiliaryVariable;
	
	int auxiliaryVariable;
	
	int *integerVector;
	
	double *x;
	double **m;
	
	double auxiliaryVariable_2;
	
	FILE *currentFile;
	
	// ##### FUNCTION'S BODY #####
	system("CLS");
	
	printf("\n\t##### LINEAR SYSTEM #####\n");
	printf("\n\tType the file's name:");
	printf("\n\t[Remember that the file must have the extension '.txt'].");
	printf("\n\t[However, it is not necessary to write it for the purposes of this application].");
	printf("\n\t[Just type the name of the file you want].");
	printf("\n\t>> ");
	
	scanf("%s", file);
	
	strcat(file, ".txt");
	
	currentFile = fopen(file, "r");
	
	fscanf(currentFile, "%s", fileContent);
	
	fclose(currentFile);
	
	n_variables = atoi(fileContent);
	
	m = allocateMatrix(n_variables, (n_variables + 1));
	x = malloc(sizeof(double) *n_variables);
	
	// Lack of memory.
	if(m == NULL || x == NULL) {
		printf("\n\tERROR");
		printf("\n\tLack of memory.\n");
		
		return 1;
	}
	
	readMatrix(m, n_variables, (n_variables + 1), file);
	
	printf("\n");
	
	printMatrix(m, n_variables, (n_variables + 1));
	
	integerVector = calculateByJordanMethod(m, n_variables);
	
	printf("\n\tDiagonal matrix:\n");
	printf("\n");
	
	printMatrix(m, n_variables, (n_variables + 1));
	
	solutionType = linearSystemBackSubstitution(m, n_variables, x);
	
	for(i_auxiliaryVariable = 1; i_auxiliaryVariable < n_variables; i_auxiliaryVariable++) {
		if(i_auxiliaryVariable != integerVector[i_auxiliaryVariable - 1]) {
			auxiliaryVariable_2 = x[i_auxiliaryVariable];
			
			x[i_auxiliaryVariable] = x[i_auxiliaryVariable - 1];
			x[i_auxiliaryVariable - 1] = auxiliaryVariable_2;
			
			auxiliaryVariable = integerVector[i_auxiliaryVariable - 1];
			
			integerVector[i_auxiliaryVariable - 1] = integerVector[i_auxiliaryVariable];
			integerVector[i_auxiliaryVariable] = auxiliaryVariable;
		}
	}
	
	if(solutionType == 2) {
		printf("\n\tLinear system incompatible.\n");
	} else {
		printf("\n\tLinear system %sdetermined.\n", solutionType ? "un" : "");
		
		for(i_auxiliaryVariable = 0; i_auxiliaryVariable < n_variables; i_auxiliaryVariable++) {
			printf("\n\t[ x%d = %10.3lf ]", (i_auxiliaryVariable + 1), x[i_auxiliaryVariable]);
		}
	}
  printf("\n");
	printf("\n\tType: %d", solutionType);
	printf("\n");
	printf("\n\t");
	
	system("PAUSE");
	
	mainMenu();
}
// Ends linearSystem.
// ##### ENDS TOPIC 02 - LINEAR SYSTEM #####

// ##### STARTS TOPIC 03 - ALGEBRAIC EQUATION #####
typedef struct polynomial {
	/*
		Struct to store and group data from polynomials.
	*/
	
	// ##### STRUCT'S VARIABLES #####
	int length;
	
	double *polynomial;
} Polynomial;

Polynomial readPolynomialData() {
	/*
		This function receives the length of the equation and the coefficients a(n), a(n-1), ..., a(0), in that order.
		This function returns a structure by reading the data from the polynomial.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int currentLength;
	
	Polynomial currentPolynomial;
	
	// ##### FUNCTION'S BODY #####
	printf("\n\t##### ALGEBRAIC EQUATION #####\n");
	printf("\n\tType the length of the desired polynomial: ");
	
	scanf("%d", &currentPolynomial.length);
	
	while(currentPolynomial.length <= 0) {
		printf("\n\tERROR - INVALID VALUE");
		printf("\n\t[The value of polynomial's length must be greater than '0'].");
		printf("\n");
		printf("\n\tType again the length of the desired polynomial: ");
		
		scanf("%d", &currentPolynomial.length);
	}
	
	printf("\n");
	
	currentPolynomial.polynomial = malloc(currentPolynomial.length * sizeof(double));
	
	for(currentLength = currentPolynomial.length; currentLength >= 0; currentLength--) {
		printf("\tType the value of coefficient a%d: ", currentLength);
		
		scanf("%lf", &currentPolynomial.polynomial[currentLength]);
		
		if(currentLength == currentPolynomial.length) {
			while(currentPolynomial.polynomial[currentLength] <= 0) {
				printf("\n\tERROR - INVALID VALUE");
				printf("\n\t[The value of coefficient a%d must be greater than '0'].", currentLength);
				printf("\n");
				printf("\n\tType again the value of coefficient a%d: ", currentLength);
				
				scanf("%lf", &currentPolynomial.polynomial[currentLength]);
				
				printf("\n");
			}
		} else if(currentLength == 0) {
			while(currentPolynomial.polynomial[currentLength] == 0) {
				printf("\n\tERROR - INVALID VALUE");
				printf("\n\t[The value of coefficient a%d must be other than '0'].", currentLength);
				printf("\n");
				printf("\n\tType again the value of coefficient a%d: ", currentLength);
				
				scanf("%lf", &currentPolynomial.polynomial[currentLength]);
				
				printf("\n");
			}
		}
	}
	return currentPolynomial;
}

Polynomial calculatePolynomialP1(Polynomial currentPolynomial) {
	/*
		This function receives a struct with the data of the base polynomial and inverts its coefficients, based on the equation: p1(x).
		This function returns a new struct with inverted vector's data.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int auxiliaryVariable;
	
	Polynomial polynomialP1;
	
	// ##### FUNCTION'S BODY #####
	polynomialP1.length = currentPolynomial.length;
	
	polynomialP1.polynomial = malloc(polynomialP1.length * sizeof(double));
	
	for(auxiliaryVariable = currentPolynomial.length; auxiliaryVariable >= 0; auxiliaryVariable--) {
		if(currentPolynomial.polynomial[currentPolynomial.length - currentPolynomial.length] < 0) {
			polynomialP1.polynomial[currentPolynomial.length - auxiliaryVariable] = currentPolynomial.polynomial[auxiliaryVariable] * (-1);
		} else {
			polynomialP1.polynomial[currentPolynomial.length - auxiliaryVariable] = currentPolynomial.polynomial[auxiliaryVariable];
		}
	}
	
	return polynomialP1;
}

Polynomial calculatePolynomialP2(Polynomial currentPolynomial) {
	/*
		This function receives a struct with the data of the polynomial that must be changed.
		Based on the equation p2(x), the function will multiply the values of odd length by (-1).
		This function returns a new struct with new vector's data.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int auxiliaryVariable;
	
	Polynomial polynomialP2;
	
	// ##### FUNCTION'S BODY #####
	polynomialP2.length = currentPolynomial.length;
	
	polynomialP2.polynomial = malloc(currentPolynomial.length * sizeof(double));
	
	for(auxiliaryVariable = 0; auxiliaryVariable <= currentPolynomial.length; auxiliaryVariable++) {
		if((auxiliaryVariable % 2) != 0) {
			polynomialP2.polynomial[auxiliaryVariable] = currentPolynomial.polynomial[auxiliaryVariable] * (-1);
		} else {
			polynomialP2.polynomial[auxiliaryVariable] = currentPolynomial.polynomial[auxiliaryVariable];
		}
	}
	return polynomialP2;
}

Polynomial calculatePolynomialP3(Polynomial currentPolynomial) {
	/*
		This function receives a struct with the data of the polynomial that must be changed.
		Based on the equation p3(x), first, the function will invert the coefficients of the base polynomial, finally,
		will multiply by (-1) the values of the odd lengths of the base polynomial.
		This function returns a new structure with new vector's data. 
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int auxiliaryVariable;
	
	Polynomial polynomialP3;
	
	// ##### FUNCTION'S BODY #####
	polynomialP3.length = currentPolynomial.length;
	
	polynomialP3.polynomial = malloc(polynomialP3.length * sizeof(double));
	
	for(auxiliaryVariable = currentPolynomial.length; auxiliaryVariable >= 0; auxiliaryVariable--) {
		if(currentPolynomial.polynomial[currentPolynomial.length - currentPolynomial.length] < 0) {
			polynomialP3.polynomial[currentPolynomial.length - auxiliaryVariable] = currentPolynomial.polynomial[auxiliaryVariable] * (-1);
		} else {
			polynomialP3.polynomial[currentPolynomial.length - auxiliaryVariable] = currentPolynomial.polynomial[auxiliaryVariable];
		}
	}
	
	for(auxiliaryVariable = 0; auxiliaryVariable <= currentPolynomial.length; auxiliaryVariable++) {
		if((auxiliaryVariable % 2) != 0) {
			polynomialP3.polynomial[auxiliaryVariable] *= (-1);
		} else {
			polynomialP3.polynomial[auxiliaryVariable] *= 1;
		}
	}
	return polynomialP3;
}

double calculateByLagrangeMethod(Polynomial currentPolynomial) {
	/*
		This function receives a struct with the polynomial data and calculates the value of the desired limit.
		For the base polynomial, calculates the limit 'L'.
		For the polynomial p1(x), calculates the limit 'L1'.
		For the polynomial p2(x), calculates the limit 'L2'.
		And, finally, for the polynomial p3(x), calculates the limit 'L3'.
		This function will returns the value of the desired limit.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int auxiliaryVariable;
	
	int k = 0;
	int n = currentPolynomial.length;
	
	double B;
	double L;
	double rootDivision;
	double rootCoefficient;
	double an = currentPolynomial.polynomial[currentPolynomial.length];
	
	// ##### FUNCTION'S BODY #####
	for(auxiliaryVariable = n; auxiliaryVariable >= 0; auxiliaryVariable--) {
		if(currentPolynomial.polynomial[auxiliaryVariable] < 0 && k == 0) {
			k = auxiliaryVariable;
		}
		
		if(currentPolynomial.polynomial[auxiliaryVariable] < B) {
			B = currentPolynomial.polynomial[auxiliaryVariable];
		}
	}
	
	B = fabs(B);
	rootCoefficient = n - k;
	rootDivision = B / an;
	L = 1 + (pow(rootDivision, (1 / rootCoefficient)));
	
	return L;
}

void calculatePolynomialLimits(double currentL, double currentL1, double currentL2, double currentL3) {
	/*
		This function receives the values of the calculated limits in the function: calculateByLagrangeMethod.
		With these values, the function returns the ranges of positive roots and negative roots of the desired base polynomial.
	*/
	
	// ##### FUNCTION'S BODY #####
	currentL1 = (1 / currentL1);
	currentL2 *= (-1);
	currentL3 = (1 / currentL3) * (-1);
	
	printf("\n\tUPPER LIMIT: [ %lf <= x+ <= %lf ].", currentL1, currentL);
	printf("\n\tLOWER LIMIT: [ %lf <= x- <= %lf ].", currentL2, currentL3);
}

double calculateByBisectionMethod(Polynomial currentPolynomial, double *currentRange) {
	/*
		This function applies the bisection method to the desired base polynomial.
		When an interval is given, an approximate root is returned to the base polynomial.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int iterationNumber = 0;
	int auxiliaryVariable;
	
	double m;
	
	double a_polynomialSolution = 0;
	double m_polynomialSolution = 0;
	
	double a = currentRange[0];
	double b = currentRange[1];
	
	// ##### FUNCTION'S BODY #####
	while(iterationNumber < 1000) {
		m = a + b;
		m /= 2;
		
		if((m - a) < maximumError) {
			return m;
		}
		a_polynomialSolution = 0;
		m_polynomialSolution = 0;
		
		for(auxiliaryVariable = currentPolynomial.length; auxiliaryVariable >= 0; auxiliaryVariable--) {
			a_polynomialSolution += (currentPolynomial.polynomial[auxiliaryVariable] * pow(a, auxiliaryVariable));
			m_polynomialSolution += (currentPolynomial.polynomial[auxiliaryVariable] * pow(m, auxiliaryVariable));
		}
		
		if(m_polynomialSolution == 0) {
			return m;
		}
		
		if((a_polynomialSolution * m_polynomialSolution) > 0) {
			a = m;
		} else {
			b = m;
		}
		iterationNumber++;
	}
	return m;
}

void calculateByBolzanoTheorem(Polynomial currentPolynomial, double *currentRange) {
	/*
		This function receives a range passed by the user.
		From this function, it is analyzed whether f(a) * f(b) < 0.
		If true, it will be reported that between the range provided has an odd number of roots,
		and from the function: calculateByBisectionMethod, the approximate value of the root present in that range will be calculated.
		Otherwise, it will be informed that between the provided range has an even number of roots, and the user will return to the main menu.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	int auxiliaryVariable;
	
	double approximateSolution;
	
	double a_polynomialSolution = 0;
	double b_polynomialSolution = 0;
	
	double a = currentRange[0];
	double b = currentRange[1];
	
	// ##### FUNCTION'S BODY #####
	for(auxiliaryVariable = currentPolynomial.length; auxiliaryVariable >= 0; auxiliaryVariable--) {
		a_polynomialSolution += (currentPolynomial.polynomial[auxiliaryVariable] * pow(a, auxiliaryVariable));
		b_polynomialSolution += (currentPolynomial.polynomial[auxiliaryVariable] * pow(b, auxiliaryVariable));
	}
	
	if((a_polynomialSolution * b_polynomialSolution) < 0) {
		approximateSolution = calculateByBisectionMethod(currentPolynomial, currentRange);
		
		printf("\n\tIn this interval, there exists an odd number of roots for this polynomial.");
		printf("\n\tThe aproximate polynomial root, in this interval, is: %lf\n", approximateSolution);
		printf("\n\t");
		
		system("PAUSE");
		
		mainMenu();
	} else {		
		printf("\n\tIn this interval, there exists an even number of roots for this polynomial.\n");
		printf("\n\t");
		
		system("PAUSE");
		
		mainMenu();
	}
}

void chooseRange(Polynomial currentPolynomial) {
	/*
		In this function, the user will pass the values referring to the desired interval so that a root is calculated,
		approximately, of the desired base polynomial.
	*/
	
	// ##### FUNCTION'S VARIABLE #####
	double *currentRange;
	
	// ##### FUNCTION'S BODY #####
	currentRange = malloc(2 * sizeof(double));
	
	printf("\n\n");
	printf("\n\t##### CHOOSE RANGE #####\n");
	printf("\n\tType the value of the lower limit of the desired range: ");
	
	scanf("%lf", &currentRange[0]);
	
	printf("\n\tType the value of the upper limit of the desired range: ");
	
	scanf("%lf", &currentRange[1]);
	
	calculateByBolzanoTheorem(currentPolynomial, currentRange);
}

void algebraicEquation() {
	/*
		This function receives a base polynomial.
		From this polynomial, the polynomials are calculated: p1(x), p2(x) and p3(x).
		Afterwards, the limits are calculated using the function: calculateByLagrangeMethod.
		Finally, with all these data, the user will pass a range, so that from the function: calculateByBisectionMethod,
		an approximate root is calculated for the desired base polynomial.
	*/
	
	// ##### FUNCTION'S VARIABLES #####
	double L;
	double L1;
	double L2;
	double L3;
	
	double* upperLimitRange;
	double* lowerLimitRange;
	
	Polynomial polynomial;
	Polynomial polynomialP1;
	Polynomial polynomialP2;
	Polynomial polynomialP3;
	
	// ##### FUNCTION'S BODY #####
	system("CLS");
	
	polynomial = readPolynomialData();
	polynomialP1 = calculatePolynomialP1(polynomial);
	polynomialP2 = calculatePolynomialP2(polynomial);
	polynomialP3 = calculatePolynomialP3(polynomial);
	
	L = calculateByLagrangeMethod(polynomial);
	L1 = calculateByLagrangeMethod(polynomialP1);
	L2 = calculateByLagrangeMethod(polynomialP2);
	L3 = calculateByLagrangeMethod(polynomialP3);
	
	calculatePolynomialLimits(L, L1, L2, L3);
	
	chooseRange(polynomial);
}
// ##### ENDS TOPIC 03 - ALGEBRAIC EQUATION #####

// ##### STARTS UTILS #####
void mainMenu() {
	/*
		This function calls the menu of the application, request the desired option,
		read the option chosen by the user and directs to that option through the method:
		
		switch(desiredVariable) {
			case 'option':
				break;
			
			default:
				break;
		}
	*/
	
	// ##### FUNCTION'S VARIABLE #####
	char chooseOption;
	
	// ##### FUNCTION'S BODY #####
	system("CLS");
		
	printf("\n\t##### MAIN MENU #####\n");
	printf("\n\tType one of the following options:");
	printf("\n");
	printf("\n\t[C] - CONVERSION");
	printf("\n\t[S] - LINEAR SYSTEM");
	printf("\n\t[E] - ALGEBRAIC EQUATION");
	printf("\n\t[F] - FINALIZE PROGRAM");
	printf("\n\t>> ");
		
	scanf("%c", &chooseOption);
		
	switch(chooseOption) {
		case 'C':
			conversion();
			break;
				
		case 'S':
			linearSystem();
			break;
			
		case 'E':
			algebraicEquation();
			break;
			
		case 'F':
			printf("\n\tSee you later...\n");
			break;
		
		default:
			mainMenu();
			break;
	}
}
// ##### ENDS UTILS #####

// ##### STARTS INT MAIN #####
int main() {	
	setlocale(LC_ALL, "Portuguese");
	
	mainMenu();
	
	return 0;
}
// ##### ENDS INT MAIN #####