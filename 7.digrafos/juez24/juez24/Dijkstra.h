using namespace std;
#include <vector>
#include "DigrafoValorado.h" 
#include "IndexPQ.h"

template <typename Valor>
class Dijkstra {
public:
	Dijkstra(DigrafoValorado<Valor> const& g) : 
		dist(g.V(), INF), ult(g.V()), pq(g.V()) {
		int origen = 0;
		dist[origen] = 0;
		pq.push(origen, 0);		
		while (!pq.empty()) {
			int v = pq.top().elem;  pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
		umbral = dist[g.V()];
	}

	bool hayCamino(int v) const { return dist[v] != INF; }

	Valor distancia(int v) const { return dist[v]; }

	using Camino = std::deque<int>; // para representar caminos

	Camino<Valor> camino(int v) const {
		Camino<Valor> cam;
		// recuperamos el camino retrocediendo
		AristaDirigida<Valor> a;
		for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
			cam.push_front(a);
		cam.push_front(a);
		return cam;
	}

private:
	const Valor INF = std::numeric_limits<Valor>::max();
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ult;
	IndexPQ<Valor> pq;
	int umbral;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ult[w] = a;
			pq.update(w, dist[w]);
		}
	}
};