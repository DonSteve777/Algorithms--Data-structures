#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;


struct Caja {
	int numero;
	int seconds;
};

struct mi_comparador {
	bool operator()(Caja const& a, Caja const& b) {
		return a.seconds < b.seconds || (a.seconds == b.seconds
			&& a.numero < b.numero);
	}
};

bool resuelveCaso() {
	int n, c, seconds;	//cajas abiertas, clientes esperando
	Caja caja;

	cin >> n >> c;
	if ( n == 0 && c == 0)
		return false;

	PriorityQueue<Caja, mi_comparador> cola;
	int cajaNo = 1;

	for (int i = 0; i < c; ++i) {	//cada cliente a una caja
		cin >> caja.seconds;
		if (c >= n) {
			if (cajaNo > n)	//todas las cajas ocupadas
			{
				Caja libre = cola.top();
				cola.pop();
				libre.seconds += caja.seconds;
				cola.push(libre);
			}
			else {
				caja.numero = cajaNo;
				cajaNo++;
				cola.push(caja);
			}
		}
	}
	if (c >= n)
		cout << cola.top().numero << '\n';
	else
		cout << c + 1 << '\n';

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
