#include <iostream>
#include <fstream>
#include <string>
#include "Matriz.h"
#include <algorithm>
using namespace std;

/*
Subsecuencia(i, j) = 
	subsecuencia(i+1, j +1) + 1								if x[i] = y[j]	
	max ( subsecuencia(i+1, j), subsecuencia(i, j+1) )		if x[i] != y[j]

*/

int subsecuencia(string const& x, string const& y, int i, int j, Matriz<int> & comun) {
	if (i == x.length() || j == y.length())
		return 0;

	int & res = comun[i][j];
	if (res == -1) {
		if (x[i] == y[j])
			res = subsecuencia(x, y, i + 1, j + 1, comun) + 1;
		else
			res = max(subsecuencia(x, y, i + 1, j, comun), subsecuencia(x, y, i, j + 1, comun));	
	}
	return res;
}

string reconstruir(string const& x, string const& y, Matriz<int> const& comun, int i, int j) {
	if (i == x.length() || j == y.length())
		return{};
	if (x[i] == y[j])
		return x[i] + reconstruir(x, y, comun, i + 1, j + 1);
	else if (i < x.length()-1 && comun[i][j] == comun[i + 1][j])
		return reconstruir(x, y, comun, i+1, j);
	else
		return reconstruir(x, y, comun, i, j +1);
}


void reconstruirOptimo(string const& x, string const& y, Matriz<int> const& comun, int i, int j, string & sol) {
	if (i == x.length() || j == y.length())
		return;
	if (x[i] == y[j]) {
		sol.push_back(x[i]);
		reconstruirOptimo(x, y, comun, i + 1, j + 1, sol);
	}	 
	else if (i < x.length() - 1 && comun[i][j] == comun[i + 1][j])
		return reconstruirOptimo(x, y, comun, i + 1, j, sol);
	else
		return reconstruirOptimo(x, y, comun, i, j + 1, sol);
}




bool resuelveCaso() {
	string X, Y;
	cin >> X >> Y;

	if (!std::cin)
		return false;

	int N = X.length();
	int M = Y.length();
	Matriz<int> comun(N, M, -1);
	string sol;

	subsecuencia(X, Y, 0, 0, comun) ;	//O (x*Y)
	//cout << reconstruir(X, Y, comun, 0, 0) << '\n';	//O (Z) siendo Z la longitud de la sol.
	reconstruirOptimo(X, Y, comun, 0, 0, sol);
	cout << sol << '\n';
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
