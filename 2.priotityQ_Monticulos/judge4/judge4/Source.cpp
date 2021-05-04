#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

struct tRegistro {
	int id;
	int periodo;
	int envio;
};

struct comp_registro {
	bool operator()(tRegistro const& a, tRegistro const& b) {
		return b.envio > a.envio ||
			(a.envio == b.envio && b.id > a.id);
	}
};

// coste: k log N, donde N es el numero de usuarios
void monitorizacion(PriorityQueue<tRegistro, comp_registro> & cola, int k) {
	for (int i = 0; i < k; i++) {
		cout << cola.top().id << '\n';	//cte
		tRegistro aux = cola.top(); 
		cola.pop();	//log n
		aux.envio += aux.periodo;
		cola.push(aux); //log n
	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int n, k;
	tRegistro r;
	PriorityQueue<tRegistro, comp_registro> cola;
	// leer los datos de la entrada
	cin >> n;
	if (n == 0)
		return false;
	for (int i = 0; i < n; i++) {
		cin >> r.id;
		cin >> r.periodo;
		r.envio = r.periodo;
		cola.push(r);
	}
	cin >> k;
	monitorizacion(cola, k);
	cout << "---\n";

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
