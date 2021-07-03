#include <iostream>
#include <fstream>
#include <string>
#include "Matriz.h"
#include <algorithm>
using namespace std;

char tablaMul(char x, char y) {
	if (x == 'a') {
		switch (y) {
		case 'a':
			return 'b';
			break;
		case 'b':
			return 'b';
			break;
		case 'c':
			return 'a';
			break;
		}
	}
	else if (x == 'b'){
		switch (y) {
		case 'a':
			return 'c';
			break;
		case 'b':
			return 'b';
			break;
		case 'c':
			return 'a';
			break;
		}
	}
	else if (x == 'c') {
		switch (y) {
		case 'a':
			return 'a';
			break;
		case 'b':
			return 'c';
			break;
		case 'c':
			return 'c';
			break;
		}
	}
}
/*
Recurrencias: A, B y C
	A(i, j) = es posible insertar parentesis en xi...xj para obtener a

	k = posicion donde insertar el parentesis
		(x1 ... xk) (xk+1 ... xn)
		k >= i ^ k < j

	A(i,j) = OR (k = i; k < j-1)
					A(i, k) && C(k+1, j)
					|| B(i,k) && C(k+1, j)
					|| C(i,k) && A(k+1, j)

	B(i,j) = OR (k = i; k < j-1)
					A(i, k) && A(k+1, j)
					|| A(i,k) && B(k+1, j)
					|| B(i,k) && B(k+1, j)

	C(i,j) = OR (k = i; k < j-1)
					B(i, k) && A(k+1, j)
					|| C(i,k) && B(k+1, j)
					|| C(i,k) && C(k+1, j)
*/
struct Decision {
	int position;
	char resultado1, ressultado2;
};

bool parentesis(string input /*, Matriz<Decision> & pa, Matriz<Decision> & pb, Matriz<Decision> & pc */) {
	int N = input.length();
	Matriz<bool> A(N, N, false);	//ac | bc | ca
	Matriz<bool> B(N, N, false);	// aa | ab | bb
	Matriz<bool> C(N, N, false);	// ba | cb | cc

//	caso base -> i = j	un solo caracter (x)
	for (int i = 0; i < N; i++)
	{
		
		A[i][ i] = input[i] == 'a';
		B[i][ i] = input[i] == 'b';
		C[i][ i] = input[i] == 'c';
	}
//	recorrido de diagonales. i y j avanzan como el tiro al palindromo 
	for (int d = 0; d < N; d++)
	{
		for (int i = 0;  i < N-d;  i++)
		{
			int j = i + d;
			int k = i;
			//disyuncion para A
			while (!A[i][j] && k < j) {
				A[i][j] = A[i][k] && C[k + 1][j] || B[i][k] && C[k + 1][j] || C[i][k] && A[k + 1][j] || A[i][j];
				k++;
			}
			k = i;
			while (!B[i][j] && k < j) {
				B[i][j] = A[i][k] && A[k + 1][j] || A[i][k] && B[k + 1][j] || B[i][k] && B[k + 1][j] || B[i][j];
				k++;
			}
			k = i;
			while (!C[i][j] && k < j) {
				C[i][j] = B[i][k] && A[k + 1][j] || C[i][k] && B[k + 1][j] || C[i][k] && C[k + 1][j] || C[i][j];
				k++;
			}
		}
	}
	return A[0][N - 1];
}

bool resuelveCaso() {
	string X;
	cin >> X;

	if (!std::cin)
		return false;
	if (parentesis(X))
		cout << "SI\n";
	else
		cout << "NO\n";
	
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
