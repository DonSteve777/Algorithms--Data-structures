using namespace std;
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include "Dijkstra.h"  // propios o los de las estructuras de datos de clase


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, C;
	int v, w, valor;
	std::vector<int> paginas(1000);

	// leer los datos de la entrada
	cin >> N;
	if (!cin)
		return false;
	cin >> C;
	DigrafoValorado<int> digrafo(N);

	for (int i = 0; i < C; i++) {
		cin >> v >> w >> valor;
		digrafo.ponArista({ v-1, w-1, valor});
		digrafo.ponArista({ w - 1, v - 1, valor });
	}
	Dijkstra<int> camino(digrafo);	
	


	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero

	while (resuelveCaso());

	// para dejar todo como estaba al principio
	return 0;
}
