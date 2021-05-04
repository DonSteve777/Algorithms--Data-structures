using namespace std;
#include <vector>
#include "Digrafo.h" 

class Sumidero {
public:
	Sumidero(Digrafo const& g) : descartados(g.V(), false){
		int w=1, v=0;
		while (v < g.V()-1 || w < g.V()) {
			/*if (v == w) {
				w++;	Asumo que no hay autoaristas
			}*/
			if (g.hayArista(v, w)) {
				v++;
				descartados[v] = true;
			}else
				w++;
		}
		int i = 0;
		while (i < g.V()) {
			if (!descartados[i])

		}
	
	}

	bool tieneSumidero() const{
		return _tiene;
	}


private:
	vector<bool> descartados;
	bool _tiene;
	

	

};