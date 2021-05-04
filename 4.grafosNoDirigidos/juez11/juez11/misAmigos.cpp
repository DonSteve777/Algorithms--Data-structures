
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Amigos.h"


bool resuelveCaso() {
	int V, A;
	// leer los datos de la entrada
	cin >> V;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> A;
	Grafo grafo(V);
	int a, b; //aristas
	for (int i = 0; i < A; ++i) {
		cin >> a >> b;
		grafo.ponArista(a - 1, b - 1);
	}
	Amigos grupos = Amigos(grafo);
	cout << grupos.getGrupoMasGrande() << "\n";
	return true;
}

int main() {/*
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif*/

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
/*
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif*/
	return 0;
}
