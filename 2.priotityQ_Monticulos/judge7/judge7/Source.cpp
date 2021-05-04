#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;
//http://tais.fdi.ucm.es/domjudge/team/problems/50/text
//multitarea

struct Tarea {
	int inicio;
	int fin;
	int periodo;
};

struct comparadorTarea {
	bool operator()(Tarea const& a, Tarea const& b) {
		return a.fin < b.fin || (a.inicio == b.inicio && a.fin < b.fin);
	}
};


bool resuelveCaso() {
	int n, m, t;
	bool conflicto = false, finPeriodo = false;
	Tarea tax;
	PriorityQueue<Tarea, comparadorTarea> cola;

	cin >> n >> m >> t;
	if (!std::cin)
		return false;

	for (int i = 0; i < n; i++) {
		cin >> tax.inicio >> tax.fin;
		tax.periodo = 0;
		if (tax.inicio < t)
			cola.push(tax);
	}
	for (int i = 0; i < m; i++) {
		cin >> tax.inicio >> tax.fin >> tax.periodo;
		if (tax.inicio < t)
			cola.push(tax);
	}
	while (!cola.empty() && !conflicto && !finPeriodo) {
		tax = cola.top(); cola.pop();
		if (!cola.empty()) {
			if (tax.fin > cola.top().inicio && tax.inicio <= cola.top().inicio)
				conflicto = true;
			else {
				if (tax.periodo > 0) {
					tax.inicio += tax.periodo;
					tax.fin += tax.periodo;
					if (tax.inicio < t)
						cola.push(tax);
					else
						finPeriodo = true;
				}
			}
		}
	}
	cout << (conflicto ? "SI" : "NO") << "\n";
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
