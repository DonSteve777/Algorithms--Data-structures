
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase
#include <stdexcept>

using namespace std;

#define MAX 50000
int k[MAX];

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int n, value, m;
	Set<int> conjunto = Set<int>();
	
	cin >> n;
	if ( n == 0)
		return false;
	for (int i = 0; i < n; i++) {
		cin >> value;
		conjunto.insert(value);
	}
	cin >> m;
	for (int i = 0; i < m; i++) 
		cin >> k[i];
	for (int i = 0; i < m; i++) {
		try {
			cout << conjunto.kesimo(k[i]) << "\n";
		}
		catch (const std::out_of_range& e) {
			cout << "??\n";
		}/*
		if (k[i] > conjunto.size() || k[i] < 1)
			cout << "??\n";
		else
			cout << conjunto.kesimo(k[i]) << "\n";*/
	}
	cout << "---" << "\n";
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
