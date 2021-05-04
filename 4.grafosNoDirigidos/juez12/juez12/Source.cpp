#include <iostream>
#include <fstream>
#include <string>
#include "Manchas.h"

using namespace std;

bool resuelveCaso() {	//O(F*C)
	int rows, columns;

	cin >> rows;
	if (!std::cin)  // fin de la entrada
	return false;
	cin >> columns;

	Mapa mapa(rows);

	for (string & linea : mapa)
		cin >> linea;
	Manchas manchas(mapa);

	cout << manchas.getNum() << ' ' << manchas.getMaxim() << '\n';
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
