#include <iostream>
#include <vector>


/**
*	D: dimensiones de matrices. D0 filas de la matriz 1, D1, filas de M2 y columnas de M1
*	P: info para reconstruir sol. Contiene las Ks elegidas en cada subproblema
*	caso básico: i = j -> diagonal principal -> 0s
*	(d, i)-> elemento i, de la diagonal d
*	matrices contiene las soluciones (número de multiplicaciones)
*/
#define INF 1000000000000

//Coste en tiempo: O(n^3)
//Coste en espacio: O(n^2)
int multiplica_marices(vector<int> const& D, Matriz<int> & P) {

	int n = D.size() - 1;	//n matrices
	Matriz<int> matrices(n + 1, n + 1, 0);	//aunque sólo usa de la 1 a la n
	P = Matriz<int>(n + 1, n + 1, 0);

	for(int d = 1; d <= n-1; ++d)	//recorrido en diagonales, no habitual
		for (int i = 1; i <= n - d; ++i) {	//elementos en la diagonal
			int j = i + d;
			matrices[i][j] = INF;	//no va a ser un valor de la tabla, ergo vale con una cte
			//cálculo del mínimo
			for (int k = i; k <= j - 1; ++k) {	//probar en los 
				int temp = matrices[i][k] + matrices[k + 1][j] + D[i - 1] * D[k] * D[j];
				if (temp < matrices[i][j]) {
					matrices[i][j] = temp; 
					P[i][j] = k;
				}
			}
		}
}

//lineal respecto j-i que es n en la llamada inicial (número de matrices)
void escribir_paren(int i, int k, Matriz<int> const& P) {
	if (i == j)
		cout << "M" << i;
	else {
		int k = P[i][j];	//última matriz en la mitad izquierda
		if (k > i) {	//hemos dejado al menos 2 matrices en la izquierda?
			cout << "("; 
			escribir_paren(i, k, P);
			cout << ")";
		}
		else cout << "M" << i;
		cout << "*";
		if (k + 1 < j) {
			cout << "(";
			escribir_paren(k+1, j, P);
			cout << ")";
		}else
		else cout << "M" << jj;
	}
}
