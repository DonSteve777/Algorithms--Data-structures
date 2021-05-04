#include <queue>

class CaminoMasCorto {
public:
	CaminoMasCorto(Grafo const& g, int s) : visit(g, V(), false),
		ant(g.V()), dist(g.V()), s(s) {
		bfs(g);
	}

	bool hayCamino(int v) const {
		return visit[v];
	}

	int distancia(int v) const {
		return dist[v];
	}

	using Camino = std::deque<int>;

	Camino camino(int v) const {
		Camino cam;
		if (!hayCamino(v)) throw std::domain_error("No existe camino");
		for (auto x = v; x != s; x = ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}


private:
	std::vector<bool> visit;
	std::vector<int> ant;
	std::vector<int> dist;
	int s;

	void bfs(Grafo const& g, int s) {
		std::queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
					q.push(w);
				}
			}
		}
	}

};
