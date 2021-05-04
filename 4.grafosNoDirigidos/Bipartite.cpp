#include <queue>

#define INF 1000000

typedef vector<int> vi;


class Bipartite {
public:
	Bipartite(Grafo const& g, int s) : s(s), isBipartite(true) {
		
		bfs(g, s);
	}

private:
	bool isBipartite;
	int s;

	void bfs(Grafo const& g, int s) {
		std::queue<int> q;
		q.push(s);
		vi color(g.V(), INF);	color[s] = 0;
		while (!q.empty() && isBipartite ) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if ( color[w] == INF ) {
					color[w] = 1 - color[v];
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
