#include "Digrafo.h"
#include <queue>

class CicloDirigido {
public:
	CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false),
	hayciclo(false) {
		for (int v = 0; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);	//diferente al original
	}

	bool hayCiclo() const { return hayciclo; }
	using Camino = std::deque<int>; // para representar caminos

	Camino const& ciclo() const { return _ciclo; }

private:
	std::vector<bool> visit;
	std::vector<int> ant;
	std::vector<bool> apilado;
	Camino _ciclo;
	bool hayciclo;

	//difiere del original
	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (hayciclo)
				return;
			if (!visit[w]) {
				ant[w] = v;
				dfs(g, w);
			}
			else if (apilado[w]) {
				hayciclo = true;
				for (int x = v; x != w; x = ant[x])
					_ciclo.push_front(x);
				_ciclo.push_front(w);
				_ciclo.push_front(v);
			}
		}
		apilado[v] = false;
	}

};