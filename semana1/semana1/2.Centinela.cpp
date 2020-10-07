// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "TreeSet_AVL.h"

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
string resolver(const Set<int> set, const int & k) {
	string ret;
	try
	{
		ret = set.kesimo(k);
	}
	catch (const std::exception&)
	{
		return "??";
	}
	return ret;
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	Set<int> miconjunto = Set<int>();
	int x, y, z, k;
	// leer los datos de la entrada
	cin >> x;
	if (x == 0)
		return false;
	else {

		for (int i = 0; i < x; ++i) {
			cin >> y;
			miconjunto.insert(y);
		}
		cin >> z;
		for (int j = 0; j < z; ++j) {
			cin >> k;
			cout << resolver(miconjunto, k) << " ";
			cout << "---\n";
		}
		cout << endl;
		return true;
	}
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
