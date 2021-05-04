//
//  Grafo.h
//
//  Implementaci�n de grafos no dirigidos
//
//  Facultad de Inform�tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2020  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un v�rtice

class Grafo {
private:
	int _V;  // n�mero de v�rtices
	int _A;  // n�mero de aristas
	std::vector<std::vector<bool>> _ady; // matriz de adyacencia

public:

	/**
	* Crea un grafo con V v�rtices.
	*/
	Grafo(int V) : _V(V), _A(0), _ady(V, std::vector<bool>(V, false)) {}

	/**
	* Devuelve el n�mero de v�rtices del grafo.
	*/
	int V() const { return _V; }

	/**
	* Devuelve el n�mero de aristas del grafo.
	*/
	int A() const { return _A; }

	/**
	* A�ade la arista v-w al grafo.
	* @throws domain_error si alg�n v�rtice no existe
	*/
	void ponArista(int v, int w) {
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::domain_error("Vertice inexistente");
		++_A;
		_ady[v][w] = _ady[w][v] = true;

	}

	bool hayArista(int v, int w) const {
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::domain_error("Vertice inexistente");
		/* falta */
		return _ady[v][w];
	}

	/**
	* Devuelve la lista de adyacencia de v.
	* @throws domain_error si v no existe
	*/
	Adys ady(int v) const {
		if (v < 0 || v >= _V)
			throw std::domain_error("Vertice inexistente");
		Adys ret;
		for (int i = 0; i < _V; i++) {
			if (_ady[v][i])
				ret.push_back(i);
		}
		return ret;
	}

};

#endif /* GRAFO_H_ */

using namespace std;

int main() {

	Grafo g(7);
	g.ponArista(0, 1);
	g.ponArista(2, 3);
	g.ponArista(4, 3);
	g.ponArista(1, 5);
	g.ponArista(1, 6);

	if (g.hayArista(3, 4))
		cout << "Hay arista entre el 3 y el 4.\n"; // debe mostrar este mensaje
	else
		cout << "No hay arista entre el 3 y el 4.\n";
	if (g.hayArista(0, 5))
		cout << "Hay arista entre el 0 y el 5.\n"; // debe mostrar este mensaje
	else
		cout << "No hay arista entre el 0 y el 5.\n";

	cout << "Los adyacentes al 1 son:";
	for (int i = 0; i < g.V(); i++) // debe mostrar  0 5 6
		if (g.hayArista(1, i))
			cout << ' ' << i;
	cout << '\n';

	system("PAUSE");

	return 0;
}
