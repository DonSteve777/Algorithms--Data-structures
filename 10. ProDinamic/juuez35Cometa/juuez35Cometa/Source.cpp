#include <vector>
#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"
#include <algorithm>

using namespace std;


EntInf minInf(EntInf a, EntInf b) {
	if (a < b)
		return a;
	return b;
}

/*Recursión
si mi > j
	cuerdas(i - 1, j)
si mi <= j
	min(
		cuerdas(i - 1, j),
		cuerdas(i, j - mi) + 1)
	*/

//min ropes number
int cuerdas(vector<int> const& longitudes, int l, int i) {

	if (l == 0)
		return 1;

	int ret1 = 0, ret2 = 0;
	if (longitudes[i] < l) {
		ret1 += cuerdas(longitudes, l - longitudes[i], i+1);
	}
	                                     
	ret2 = cuerdas(longitudes, l, i+1);

	return min(ret1, ret2);
}

void cuerdaCometa(vector<int> const& longitudes, int l, vector<int> const& costes) {
	int n = longitudes.size();
	Matriz<EntInf> cuerdas(n + 1, l + 1, Infinito);	//primera línea inicializada a infinito
	cuerdas[0][0] = 0; // conjunto vacío de cuerdas disponibles

	for (int i = 1; i <= n; ++i) {
		cout << "\n";
		cuerdas[i][0] = 0;	//cuerda a conseguir de longitud 0
		for (int j = 1; j <= l; ++j) {
			if (longitudes[i - 1] > j)
				cuerdas[i][j] = cuerdas[i - 1][j];
			else {
				if (cuerdas[i - 1][j] < (cuerdas[i][j - longitudes[i - 1]] + 1)) {
					cuerdas[i][j] = cuerdas[i][j - longitudes[i - 1]] + 1;
				}
				else
					cuerdas[i][j] = cuerdas[i - 1][j];
			}
			cout << cuerdas[i][j] << " ";
		}
	}
}


bool resuelveCaso() {

	int n, l;
	cin >> n >> l;
	vector<int> longitudes(n);
	vector<int> costes(n);


	for (int i = 0; i < n; ++i) {
		cin >> longitudes[i] >> costes[i];
	}

	if (!std::cin)  // fin de la entrada
		return false;

	

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
