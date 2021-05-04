#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <queue>

using namespace std;


#define INF 1000000

typedef vector<int> vi;


class Bipartite {
public:
	Bipartite(Grafo const& g) : isBipartite(true), color(g.V(), INF) {
		for (int v = 0; v < g.V(); ++v) {
			if (color[v] == INF)
				bfs(g, v);
		}
	}

	bool getBipartite() {
		return isBipartite;
	}

	int getMinGuardias() {
		int nV = color.size();
		return min(guardias, nV - guardias);
	}

private:
	bool isBipartite;
	int guardias;
	vi color;

	void bfs(Grafo const& g, int s) {
		std::queue<int> q;
		q.push(s);
		color[s] = 0;
 		while (!q.empty() && isBipartite) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (color[w] == INF) {
					color[w] = 1 - color[v];
					if (color[w] == 1)
						guardias++;
					q.push(w);
				}
				else if (color[w] == color[v]) {
					isBipartite = false;
					break;
				}
			}
		}
	}

};


bool resuelveCaso() {
	int N, C;	// cruces, calles

	cin >> N >> C;
	if (!std::cin)
		return false;

	Grafo g(N);
	int v, w;
	for (int i = 0; i < C; i++) {
		cin >> v >> w;
		g.ponArista(v - 1, w - 1);
	}
	//recorre todas las componentes conexas colocando guardias en vértices a distancias impares.
	Bipartite recorrido(g);
	if (recorrido.getBipartite())
		cout << recorrido.getMinGuardias() << '\n';
	else
		cout << "IMPOSIBLE\n";
		
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
