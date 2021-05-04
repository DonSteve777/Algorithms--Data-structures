#include <vector>
#include "Grafo.h"
#include <queue>

class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
	int s; // vértice origen
	int aristasRecorridas;

	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {	//cada vertice se recorre una vez O(v+A)
				ant[w] = v;
				aristasRecorridas++;
				dfs(G, w);
			}
		}
	}

public:
	CaminosDFS(Grafo const& G, int s) : visit(G.V(), false),
		ant(G.V()), s(s), aristasRecorridas(0) {
		dfs(G, s);
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}

	int getAristas() {
		return aristasRecorridas;
	}

	using Camino = std::deque<int>; // para representar caminos
									// devuelve un camino desde el origen a v (debe existir)
									//doble para recorrer desde el principio una vez construida, y para poder ir añadiendo por el final

	//reconstruir camino mediante la info de anterior
	Camino camino(int v) const {
		Camino cam;
		if (!hayCamino(v))
			throw std::domain_error("No existe camino");
		// recuperamos el camino retrocediendo
		for (int x = v; x != s; x = ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}
};