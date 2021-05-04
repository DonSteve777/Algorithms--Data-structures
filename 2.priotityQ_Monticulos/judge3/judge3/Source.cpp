#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

//N log n
long long int calculin(PriorityQueue<long long int> & cola) {
	long long int a = cola.top();	//cte
	cola.pop();	//log n
	long long int b = 0;	
	long long int c = 0;

	if (!cola.empty()) {
		b = cola.top();
		cola.pop();
		c = a + b;
		if (!cola.empty()) {
			cola.push(c);
			return c + calculin(cola);
		}
	} 	
	return c;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int n, x;
	
	PriorityQueue<long long int> cola;

	cin >> n;
	if (n == 0)
		return false;
	for (int i = 0; i < n; i++) {
		cin >> x;
		cola.push(x);
	}
	cout << calculin(cola) << "\n";

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