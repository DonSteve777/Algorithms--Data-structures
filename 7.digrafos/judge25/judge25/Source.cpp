#include "BFS.h"
#include <iostream>
#include <fstream>
#include "Dijkstra.h"
using namespace std;

#define MAX_N 20000
#define MAX_C 100000

using CaminoDijkstra = std::deque<AristaDirigida<int>>;
using CaminoAnchura = std::deque<int>;

bool resuelveCaso() {
	int N, C; //intersecciones, calles
	
	cin >> N >> C;
	if (!std::cin)
		return false;
	DigrafoValorado<int> d(N);
	Grafo g(N);
	int v, w, longitud;
	for (int i = 0; i < C; i++) {
		cin >> v >> w >> longitud;
		AristaDirigida<int> vw(v-1, w-1, longitud);
		AristaDirigida<int> wv(w-1, v-1, longitud);
		d.ponArista(vw);
		d.ponArista(wv);
		g.ponArista(v - 1, w - 1);
	}
	int k, src, dest;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> src >> dest;
		src--;
		dest--;
		CaminoMasCorto anchura(g, src);
		Dijkstra<int> dijkstra(d, src);
		if (!dijkstra.hayCamino(dest))
			cout << "SIN CAMINO\n";
		else {
			CaminoDijkstra cD = dijkstra.camino(dest);	//aristas
			CaminoAnchura cA = anchura.camino(dest);	//vertices
			int callesDisjkstra = cD.size();	//aristas
			int callesAnchura = cA.size() -1;	//vertices
			int minDistancia = dijkstra.distancia(dest);

			cout << minDistancia;
			if (callesDisjkstra == callesAnchura)
				cout << " SI\n";
			else
				cout << " NO\n";
		}
	}
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
