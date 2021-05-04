
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include "PriorityQueue.h"  // de máximos, top devuelve máx

using namespace std;

struct paciente {
	std::string nombre;
	int gravedad;
	int llegada;
};

struct comp_paciente {
	bool operator()(paciente const& a, paciente const& b) {
		return b.gravedad < a.gravedad || (a.gravedad == b.gravedad && a.llegada < b.llegada);
	}
};

class ColaUrgencias {
public:
	/*ColaUrgencias();
	void ingresarPaciente(std::string nombre, int gravedad);
	std::string nombrePrimero() const;
	void atenderPaciente();*/

	ColaUrgencias() {
		//PriorityQueue<paciente, comp_paciente> cola;
	}
	//O(log N)
	void ingresarPaciente(std::string nombre, int gravedad, int llegada) {
		cola.push({ nombre, gravedad, llegada });
	}

	std::string nombrePrimero() const {
		return cola.top().nombre;
	}
	//O(log N)
	void atenderPaciente() {
		cola.pop();
	}
private:
	PriorityQueue<paciente, comp_paciente> cola;
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
	int eventos; char Nombgravedad; string nombre; int gravedad;
	cin >> eventos;

	if (eventos == 0) return false;

	ColaUrgencias cola = ColaUrgencias();

	/*
		// coste O(N log N) siendo n el número de eventos 
	*/
	for (int i = 0; i < eventos; i++) {
		cin >> Nombgravedad;

		if (Nombgravedad == 'I') {
			cin >> nombre >> gravedad;
			cola.ingresarPaciente(nombre, gravedad, i);
		}
		else if (Nombgravedad == 'A') {
			cout << cola.nombrePrimero() << "\n";
			cola.atenderPaciente();
		}
	}
	cout << "---\n";

	return true;
}


int main() {
   // ajustes para que cin extraiga directamente de un fichero
/*#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif*/
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
/*#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif*/
   return 0;
}
