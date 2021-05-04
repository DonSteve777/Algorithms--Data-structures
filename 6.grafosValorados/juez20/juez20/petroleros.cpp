
// �lvaro Abad de Donesteve

//Recorrido en profundidad: O(V+A) para listas de adyacentes y O(n^2) para matrices de adyaciencia
//�rbol libre: 
//		conexo: se recorren todos los v�rtices en un recorrido en profundidad
//		y ac�clico => tiene v-1 aristas para los v v�rtices
//
#include <iostream>
#include <fstream>
#include "Manchas.h"

using namespace std;

bool resuelveCaso() {
	int rows, columns, N;
	int fila, columna;
	cin >> rows;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> columns;

	Mapa mapa(rows);

	for (string & linea : mapa)
		getline(cin, linea);
	Manchas manchas(mapa);
	cout << manchas.maximo() << '\n';

	cin >> N;
	for (int j = 0; j < N; j++) {
		cin >> fila >> columna;
		manchas.nuevaImagen(mapa, fila-1, columna-1);
		cout << manchas.maximo() << '\n';
	}
	
	
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
