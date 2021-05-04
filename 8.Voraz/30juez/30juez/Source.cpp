using namespace std;
// Álvaro Abad de Donesteve

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
/*
El algoritmo considera personas y esquís por orden creciente de longitud, de forma que quedan emparejados para minimizar las diferencias
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


//Coste: bucle for-> O(n). Ordenación-> std::sort es parecido a quicksort, y quicksort se implementa con una recursión que va diviendo los datos, 
//por la mitad concretamente (b = 2), con 2 recursiones, y con un coste lineal en la parte no recursiva: a = b^k   2 = 2^1 => =(n log n)
// Por tanto, el coste del algoritmo voraz es O(n log n)
int minSumaDif(vector<int> alturas, vector<int> longitudes, int N) {
	sort(alturas.begin(), alturas.end());
	sort(longitudes.begin(), longitudes.end());
	int sumatorio=0;
	for (int i = 0; i < N; i++) {
		sumatorio += abs(alturas[i]-longitudes[i]);
	}
	return sumatorio;
}

bool resuelveCaso() {
	int N;
	// leer los datos de la entrada
	cin >> N;
	if (N == 0)
		return false;
	vector<int> alturas(N);
	vector<int> longitudes(N);
	for (int i = 0; i < N; i++)
		cin >> alturas[i];
	for (int j = 0; j < N; j++)
		cin >> longitudes[j];

	cout << minSumaDif(alturas, longitudes, N) << "\n";

	// escribir sol

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
