#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "Matriz.h"



int comer(vector<int> const & comida, int i, int j, Matriz<int> & sol, bool devoradora) {
	int N = comida.size();
	int & ret = sol[i][j];

	if (ret == -1) {
		if (i == j)	ret += comida[i];
		if (devoradora == false)
			ret += max(comida[i], comida[j]);
		if (comida[i] > comida[j]) {
			if (i+1 > j)	ret = 0;
			else
				ret += comer(comida, i + 1, j, sol, !devoradora);
		}
		else {
			if (i  > j-1)	ret = 0;
			else
				ret += comer(comida, i, j - 1, sol, !devoradora);
		}
	}
	

	return ret;
}


bool resuelveCaso() {
	int n;

	cin >> n;
	if (n == 0)
		return false;

	vector<int> comida(n, 0);
	Matriz<int> sol(n, n, -1);
	for (int i = 0; i < n; i++)
		cin >> comida[i];

	cout << comer(comida,0, n-1,sol, false ) << "\n";
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

