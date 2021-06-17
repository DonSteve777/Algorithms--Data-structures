template <typename Valor>
class ARM_Kruskal {
private:
	std::vector<Arista<Valor>> _ARM;
	Valor coste;
public:
	Valor costeARM() const {
		return coste;
	}

	std::vector<Arista<Valor>> const & ARM() const {
		return _ARM;
	}

	ARM_Kruskal(GrafoValorado<Valor> const & g) : coste(0) {	//A log A
		PriorityQueue<Arista<Valor>> pq(g.aristas());	//O(A)
		ConjunstosDisjuntos cjtos(g.V());  //O(V)
		while (!pq.empty()) {	// A veces
			auto a = pq.top(); pq.pop();	//O(log A)	
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, q)) {	//log * V 
				cjtos.unir(v, w);	//log * V (como mucho se hacen v-1 veces)
				_ARM.push_back(a);
				coste += a.valor();
				if (_ARM.size() == g.V() - 1)	break;
			}
		}
	}
};
