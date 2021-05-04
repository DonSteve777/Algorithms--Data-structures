#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 10000
#define MAX_M 100000

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


//el postorden inverso de un DAG es una ordenacion topologica
class OrdenTopologico {
public:
	//g es DAG
	OrdenTopologico(Digrafo & g) : visit(g.V(), false) {
		for (int v = 0; v < g.V(); v++)
			if (!visit[v])
				dfs(g, v);
		reverse(_orden.begin(), _orden.end());
	}

	std::vector<int> const & orden() const {
		return _orden;
	}

private:
	std::vector<bool> visit;
	std::vector<int> _orden;	//ordenacion topologica

	void dfs(Digrafo const& g, int v) {
		visit[v] = true;
		for (int w : g.ady(v))
			if (!visit[w])
				dfs(g, w);
		_orden.push_back(v);
	}
	
	template<class BidirIt>
	void reverse(BidirIt  first, BidirIt  last)
	{
		while ((first != last) && (first != --last)) {
			std::iter_swap(first++, last);
		}
	}
};



bool resuelveCaso() {
	int N, M; // tareas, relaciones de dependencia
	cin >> N;
	if (!std::cin)
		return false;
	cin >> M;
	Digrafo g(N);
	int v, w;
	for (int i = 0; i < M; i++) {
		cin >> v >> w;
		g.ponArista(v-1, w-1);
	}
	CicloDirigido ciclo(g);
	if (ciclo.hayCiclo())
		cout << "Imposible\n";
	else {
		OrdenTopologico ord(g);
		int count=1;
		for (int v : ord.orden()) {
			if ( count < g.V())
				cout << v + 1 << " ";
			else
				cout << v + 1;
			count++;
		}
		cout << '\n';
	}
		

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

