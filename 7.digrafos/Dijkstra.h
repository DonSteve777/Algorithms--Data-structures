#include <vector>
#include <queue>
#include "IndexPQ.h"
#include "DigrafoValorado.h"


template <typename Valor>
class Dijkstra {
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ult(g.V()), pq(g.V()) {	//O( A log V)

		dist[origen] = 0;
		pq.push(origen, 0);		
		while (!pq.empty()) {	
			int v = pq.top().elem;  pq.pop();	//O(log V) monticulo
			for (auto a : g.ady(v))	// A * log V	forAll aristas => update
				relajar(a);	//si dist [a.hasta()] > dist[v] + a.valor() --> actualizo dist[hasta]
		}
		//umbral = dist[g.V()];
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

private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ult;
	IndexPQ<Valor> pq;	// (elem, prio) -> (v, dist[v])
	//int umbral;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ult[w] = a;
			pq.update(w, dist[w]);	//O(log V)	push si no existia else flotar/hundir
		}
	}
};