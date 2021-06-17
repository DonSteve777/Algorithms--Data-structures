#include <iostream>
#include <fstream>
#include "Dijkstra.h"
using namespace std;

bool resuelveCaso() {
	int N, C;
	int v, w, valor;

	cin >> N;
	if (!std::cin)
		return false;
	cin >> C;
	DigrafoValorado<long int> g(N);
	for (int i = 0; i < C; i++) {
		cin >> v >> w >> valor;
		AristaDirigida<long int> ab(v-1, w-1, valor);
		AristaDirigida<long int> ba(w-1, v-1, valor);
		g.ponArista(ab);
		g.ponArista(ba);
	}
	

	Dijkstra<long int> dijk(g, 0);
	cout << dijk.getCole() << '\n';
	

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
