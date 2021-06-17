#include <vector>
#include <queue>
#include "IndexPQ.h"
#include "DigrafoValorado.h"


template <typename Valor>
class Dijkstra {
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ult(g.V()), pq(g.V()), formas(g.V(), 0), cole(0) {
		dist[origen] = 0;
		pq.push(origen, 0);		
		while (!pq.empty()) {
			int v = pq.top().elem;  pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
		if (hayCamino(g.V()-1))
			cole = caminoCole(g.V()-1);
	}

	bool hayCamino(int v) const { return dist[v] != INF; }

	Valor distancia(int v) const { return dist[v]; }

	using Camino = std::deque<AristaDirigida<Valor>>; 

	Camino camino(int v) const {
		Camino cam;
		// recuperamos el camino retrocediendo
		AristaDirigida<Valor> a;
		for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
			cam.push_front(a);
		cam.push_front(a);
		return cam;
	}

	int caminoCole(int v) {
		Camino way = camino(v);
		int ret = 0;	
		if (hayCamino(v)) {
			ret = 1;
			while (!way.empty()) {
				AristaDirigida<long int> a = way.back();
				way.pop_back();
				ret *= formas[a.hasta()];
			}
		}
		return ret;
	}

	int getCole() {
		return cole;
	}

private:
	const Valor INF = 2000000000 ;
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ult;
	IndexPQ<Valor> pq;
	std::vector<Valor> formas;
	int cole;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ult[w] = a;
			pq.update(w, dist[w]);
			formas[w] = 1;
		}
		else if (dist[w] == dist[v] + a.valor()) {
			formas[w]++;
		}
	}
};