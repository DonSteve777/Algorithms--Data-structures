#include <iostream>
#include <fstream>
#include <string>
#include "PriorityQueue.h"
using namespace std;

#define MAX_EVENTOS 200000

struct Ingreso {
	string nombre;
	int gravedad;
	int tiempo;
};

struct comp_paciente {
	bool operator()(Ingreso const & a, Ingreso const & b) {
		return b.gravedad < a.gravedad ||
			(a.gravedad == b.gravedad && b.tiempo > a.tiempo);
	}
};

bool resuelveCaso() {
	int n;	//eventos
	char tipoEvento;
	string nombre;
	PriorityQueue<Ingreso, comp_paciente> cola;

	cin >> n;
	if (n == 0)
		return false;
	for (int i = 0; i < n; i++) {
		cin >> tipoEvento;
		if (tipoEvento == 'I') {
			Ingreso ing;
			cin >> ing.nombre;
			cin >> ing.gravedad;
			ing.tiempo = i;
			cola.push(ing);
		}
		else {
			cout << cola.top().nombre << '\n';
			cola.pop();
		}
	}
	cout << "---\n";

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
