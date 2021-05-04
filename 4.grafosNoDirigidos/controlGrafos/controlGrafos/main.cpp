
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Red.h"


bool resuelveCaso() {
	int N, C, s, k, ttl;
	// leer los datos de la entrada
	cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> C;
	Grafo grafo(N);
	int a, b; //vértices entre aristas
	for (int i = 0; i < C; ++i) {
		cin >> a >> b;
		grafo.ponArista(a -1, b-1 );	//-1 para que coincida con la implementación de un grafo de V vértices
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> s >> ttl;
		Red configuracion = Red(grafo, s, ttl);
		cout << configuracion.getInalcanzables() << "\n";
	}
	cout << "---\n";
	return true;
}

int main() {/*
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
*/
	while (resuelveCaso());
	/*
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif*/
	return 0;
}
