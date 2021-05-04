#include "Camion.h"
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int V, E, K; // N el numero de cruces (vertices) y C el numero de calles (aristas)
	int origen, destino, ancho;
	std::cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;
	std::cin >> E;
	
	GrafoValorado<int> grafo(V);
	int v1, v2, a;

	for (int i = 0; i < E; i++) {
		std::cin >> v1 >> v2 >> a;
		grafo.ponArista({ v1 - 1, v2 - 1, a });	//constructor implícito (arista)
	}
	std:: cin >> K;
	for (int i = 0; i < E; i++) {
		std::cin >> origen >> destino >> ancho;
		Camion camion(grafo, origen, ancho);
		if (camion.esPosible(destino)) 
			std::cout << "SI" << "\n";
	
		else 
			std::cout << "NO\n";
	}

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
