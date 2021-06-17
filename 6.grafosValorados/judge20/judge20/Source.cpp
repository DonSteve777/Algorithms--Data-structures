#include "ConjuntosDisjuntos.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Manchas.h"
using namespace std;


bool resuelveCaso() {
	int F, C;
	int i, j;
	long int N;
	
	cin >> F >> C;
	if (!std::cin)
		return false;
	cin.ignore();
	
	Mapa mapa(F);
	for (string & linea : mapa) {
		getline(cin, linea);
	}
	Manchas manchas(mapa, F, C);
	cout << manchas.getMaxim();
	cin >> N;
	for (long int x = 0; x < N; x++) {
		cin >> i >> j;
		manchas.nuevaMancha(i-1, j-1, mapa);
		cout << " " << manchas.getMaxim();

	}
	cout << '\n';
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
