#include "Digrafo.h"
#include <vector>

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
