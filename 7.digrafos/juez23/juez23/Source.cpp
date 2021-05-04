using namespace std;
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include "Dijkstra.h"  // propios o los de las estructuras de datos de clase


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, M;
	int a, b, tiempo;
	std::vector<int> paginas(1000);

	// leer los datos de la entrada
	cin >> N;
	if (N == 0)
		return false;
	for (int i = 0; i < N; i++) {
		cin >> paginas[i];
	}
	cin >> M;
	DigrafoValorado<int> digrafo(N);
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> tiempo;
		digrafo.ponArista({ a-1, b-1, tiempo });
	}
	Dijkstra<int> nav(digrafo, paginas);	
	if (nav.hayCamino(N - 1))
		cout << nav.distancia(N - 1);
	else
		cout << "IMPOSIBLE";
	cout << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero

	while (resuelveCaso());

	// para dejar todo como estaba al principio
	return 0;
}
