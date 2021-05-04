#include "Digrafo.h"
#include <iostream>
#include <fstream>
using namespace std;

#define MAX_V 10000
#define MAX_A 100000

class Sumidero {
	int sumidero;

public:
	
	Sumidero(const Digrafo & g) : sumidero(-1) {
		Digrafo inv = g.inverso();
		for (int v = 0; v < g.V(); v++) {
			if (g.ady(v).size() == 0) //grado de salida
				if (inv.ady(v).size() == g.V() - 1) {	//grado de entrada
					sumidero = v;
					break;
				}
		}
	}

	int tieneSumidero() {
		return sumidero;
	}
};

bool resuelveCaso() {
	int V, A, v, w;
	cin >> V >> A;

	if (!std::cin)
		return false;
	Digrafo g(V);
	for (int i = 0; i < A; i++) {
		cin >> v >> w;
		g.ponArista(v, w);
	}
	Sumidero su(g);
	if (su.tieneSumidero() == -1)
		cout << "NO\n";
	else
		cout << "SI " << su.tieneSumidero() << '\n';


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
