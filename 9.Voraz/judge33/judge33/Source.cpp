
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//maximizar coches con pilas
int voraz(vector<int> v, int V){
	int ret = 0;
	unsigned int j = v.size() - 1;
	unsigned int i = 0;
	while (i < j) {
		if (v[i] + v[j] >= V) {
			j--;
			ret++;
		}
		i++;
	}
	return ret;
}
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	int N, V;

	cin >> N >> V;
	vector<int> pilas(N);
	for (int i = 0; i < N; i++) {
		cin >> pilas[i];
	}
	sort(pilas.begin(), pilas.end());
	cout << voraz(pilas, V) << '\n'; 
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
