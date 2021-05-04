
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

using namespace std;

struct tarea {
	int comienzo;
	int fin;
	int periodo;
};

bool operator<(tarea const& a, tarea const& b) {
	return a.comienzo < b.comienzo;
}
// función que resuelve el problema
// comentario sobre el coste, O(N log N)), donde N es el número de tareas, teniendo en cuenta
// que una periódica resulta ser tantas tareas como veces aparece periódicamente dentro de t minutos
// log de N es el coste del push, por lo de la altura del árbol que implementa la cola
// y la operación se hace N veces)
bool conflicto(PriorityQueue<tarea> cola, int t)
{
	int i = 1;
	tarea tax = cola.top();
	cola.pop();

	while (i <= t && !cola.empty()) {
		if (tax.fin >= cola.top().comienzo && tax.fin <= t)
			return true;
		else {
			if (tax.periodo > 0) {
				tax.comienzo += tax.periodo;
				tax.fin += tax.periodo;
				cola.push(tax);
			}
			tax = cola.top();
			i = tax.comienzo;
			cola.pop();
		}
	}
	return false;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int n, m, t;	//únicas, periódicas, y tiempo
	tarea reader;
	// leer los datos de la entrada
	cin >> n;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> m >> t;
	PriorityQueue<tarea> cola;

	//unicas
	for (int i = 0; i < n; ++i) {
		cin >> reader.comienzo >> reader.fin;
		reader.periodo = 0;
		cola.push(reader);
	}

	for (int i = 0; i < m; ++i) {
		cin >> reader.comienzo >> reader.fin >> reader.periodo;
		cola.push(reader);
	}

	if (conflicto(cola, t))
		cout << "SI" << "\n";
	else
		cout << "NO" << "\n";

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
