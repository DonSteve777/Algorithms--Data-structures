#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "profundidad.h"
using namespace std;


bool esLibre(const Grafo & g) {
	CaminosDFS caminos(g, 0);
	bool conexo = true;
	int i = 0;
	while (i < g.V() && conexo) {
		conexo = caminos.hayCamino(i) ? true : false;
		i++;
	}
	return conexo && (caminos.getAristas() == g.A());
}

bool resuelveCaso() {
	int v, a, x, y;
	cin >> v;

	if (!std::cin)
		return false;
	cin >> a;
	Grafo g(v);
	for (int i = 0; i < a; i++) {
		cin >> x >> y;
		g.ponArista(x, y);	
	}
	if (esLibre(g))
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
