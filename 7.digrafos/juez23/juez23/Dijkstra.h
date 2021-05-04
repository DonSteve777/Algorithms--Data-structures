#include <vector>
#include "DigrafoValorado.h" 
#include "IndexPQ.h"
#include <limits>
template <typename Valor>
class Dijkstra {
public:
	Dijkstra(DigrafoValorado<Valor> const& g, vector<Valor> pags) : 
		dist(g.V(), INF), ult(g.V()), pq(g.V()), paginas(pags) {
		int origen = 0;
		dist[origen] = paginas[origen];
		pq.push(origen, paginas[origen]);		
		while (!pq.empty()) {
			int v = pq.top().elem;  pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }

	Valor distancia(int v) const { return dist[v]; }

private:
	const Valor INF = numeric_limits<Valor>::max();
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ult;
	IndexPQ<Valor> pq;
	std::vector<Valor> paginas;


	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor() + paginas[w]; ult[w] = a;
			pq.update(w, dist[w]);
		}
	}
};