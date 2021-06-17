#include<algorithm>
#include "Matriz.h"
#include<vector>
#include <iostream>
#include <fstream>
using namespace std;

/*

posicion 
ascenso p segundos
descenso p segundos
oro 
aire T segundos

Recursion:

oro(i, j) = 
		oro(i-1,j)	if 3p > T
		max (  oro(i-1, j),  oro(i, j-3pi + valori ) )
*/

struct Cofre { int deep; int valor; };

int cazatesoros_rec(vector<Cofre> const & c, int i, int j, Matriz<int> & tesoro) {
	if (tesoro[i][j] != -1)
		return tesoro[i][j];
	if (i == 0 || j == 0) tesoro[i][j] = 0;
	else if (c[i - 1].deep * 3 > j)
		tesoro[i][j] = cazatesoros_rec(c, i - 1, j, tesoro);
	else
		tesoro[i][j] = max(cazatesoros_rec(c, i - 1, j, tesoro), cazatesoros_rec(c, i-1, j - c[i-1].deep*3, tesoro) + c[i-1].valor);
	return tesoro[i][j];
}


int ascendente(vector<Cofre> cofres, int T, vector<bool> & sol, int & numCofres) {
	int N = cofres.size();
	Matriz<int> tesoro(N + 1, T + 1, -1);
	int numCofres = 0;

	for (int i = 0; i <= T; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == 0 || j == 0) tesoro[i][j] = 0;
			else if (cofres[i - 1].deep * 3 > j)
				tesoro[i][j] = tesoro[i - 1][j];
			else
				tesoro[i][j] = max(tesoro[ i - 1][ j], tesoro[ i - 1][j - cofres[i - 1].deep * 3] + cofres[i - 1].valor);
		}
	}
	int i = N, j = T;
	sol = vector<bool>(N, false);
	while (i > 0 && j > 0) {
		if (tesoro[i][j] != tesoro[i - 1][j]) {
			sol[i - 1] = true;
			numCofres++;
			j = j - cofres[i - 1].deep * 3;
		}
		--i;
	}
	return tesoro[i][j];
}




int dinamica(vector<Cofre> cofres, int T, vector<bool> & sol, int & numCofres) {
	int N = cofres.size();
	Matriz<int> tesoro(N+1, T+1, -1);
	int valor = cazatesoros_rec(cofres, N, T, tesoro);
	numCofres = 0;

	int i = N, j = T;
	sol = vector<bool>(N, false);
	while (i > 0 && j > 0) {
		if (tesoro[i][j] != tesoro[i - 1][j]) {
			sol[i - 1] = true;
			numCofres++;
			j = j - cofres[i - 1].deep * 3;
		}
		--i;
	}
	return valor;
}

bool resuelveCaso() {
	int T, N;

	cin >> T >> N;
	if (!std::cin)
		return false;
	vector<Cofre> cofres(N);
	int numCofres;
	vector<bool> sol(N);
	for (int i = 0; i < N; i++) {
		//produndidad oro
		cin >> cofres[i].deep >> cofres[i].valor;
	}
	int max = ascendente(cofres, T, sol, numCofres);
	cout << max << '\n';
	cout << numCofres << '\n';

	for (int i = 0; i < sol.size(); i++)
		if ( sol[i] ) cout << cofres[i].deep << " " << cofres[i].valor << '\n';
	cout << "---\n";

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
