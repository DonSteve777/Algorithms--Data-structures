#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include "IndexPQ.h"
#include "DigrafoValorado.h"
using namespace std;

#define MAX_N 1000

const long int INF = 1000000000;


int carga[MAX_N];

template <typename Valor>
class Dijkstra {
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ult(g.V()), pq(g.V()) {

		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem;  pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
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
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ult;
	IndexPQ<Valor> pq;
	//int umbral;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ult[w] = a;
			pq.update(w, dist[w]);
		}
	}
};


bool resuelveCaso() {
	int N, M;	//paginas, enlaces
	int a, b;
		long int time;

	cin >> N;
	if (N == 0)
		return false;
	for (int i = 0; i < N; i++) {
		cin >> carga[i];
	}
	cin >> M;	//enlaces

	DigrafoValorado<long int > g(N);
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> time;
		AristaDirigida<long int> arista(a-1, b-1, time + carga[b-1]);
		g.ponArista(arista);
	}
	long int result = 0;
	Dijkstra<long int> minTiempo(g, 0);	//O(A log V) y espacio O(v)

	if (minTiempo.hayCamino(N - 1)) {
		result += carga[0] + minTiempo.distancia(N-1);
		cout << to_string(result) << '\n';
	}
	else
		cout << "IMPOSIBLE\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
