#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "GrafoValorado.h"
using namespace std;

class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?

	void dfs(GrafoValorado<int> const& G, int v, int camion) {
		visit[v] = true;
		for (auto a : G.ady(v)) {
			if (a.valor() >= camion) {
				int w = a.otro(v);
				if (!visit[w])
					dfs(G, w, camion);
			}
		}
	}

public:
	CaminosDFS(GrafoValorado<int> const& G, int s, int camion) : visit(G.V(), false) {
		dfs(G, s, camion);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}
};


bool resuelveCaso() {
	int V, E, a, b, width;
	
	cin >> V >> E;
	if (!std::cin)
		return false;
	
	GrafoValorado<int> g(V);
	for (int i = 0; i < E; ++i) {
		cin >> a >> b >> width;
		Arista<int> arista(a-1, b-1, width);
		g.ponArista(arista);
	}
	int K;
	cin >> K;
	int src, dst;
	for (int i = 0; i < K; ++i) {
		cin >> src >> dst >> width;
		CaminosDFS camino(g, src-1, width);
		camino.hayCamino(dst-1) ? cout << "SI\n" : cout << "NO\n";
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
