

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

//
//  Matriz.h
//
//  Implementación de matrices (arrays bidimensionales)
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>

template <typename Object>
class Matriz {
public:
	// crea una matriz con fils filas y cols columnas,
	// con todas sus celdas inicializadas al valor e
	Matriz(int fils = 0, int cols = 0, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}

	// operadores para poder utilizar notación M[i][j]
	std::vector<Object> const& operator[](int f) const {
		return datos[f];
	}
	std::vector<Object> & operator[](int f) {
		return datos[f];
	}

	// métodos que lanzan una excepción si la posición no existe
	Object const& at(int f, int c) const {
		return datos.at(f).at(c);
	}
	Object & at(int f, int c) {
		return datos.at(f).at(c);
	}

	size_t numfils() const { return datos.size(); }
	size_t numcols() const { return numfils() > 0 ? datos[0].size() : 0; }

	bool posCorrecta(int f, int c) const {
		return 0 <= f && f < numfils() && 0 <= c && c < numcols();
	}

private:
	std::vector<std::vector<Object>> datos;
};

template <typename Object>
inline std::ostream & operator<<(std::ostream & out, Matriz<Object> const& m) {
	for (auto i = 0; i < m.numfils(); ++i) {
		for (auto j = 0; j < m.numcols(); ++j) {
			out << m[i][j] << ' ';
		}
		out << '\n';
	}
	return out;
}

#endif

//
//  EnterosInf.h
//
//  Implementación de enteros con +infinito.
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef ENTEROSINF_H_
#define ENTEROSINF_H_

#include <limits>
#include <iostream>

class EntInf {
	int num;
public:
	static const int _intInf = 1000000000;

	EntInf(int n = 0) : num(n) {}

	EntInf operator+(EntInf const& b) const {
		if (num == _intInf || b.num == _intInf || num >= (_intInf - b.num))
			return _intInf;
		else return num + b.num;
	}

	bool operator==(EntInf const& b) const {
		return num == b.num;
	}

	bool operator!=(EntInf const& b) const {
		return !(*this == b);
	}

	bool operator<(EntInf const& b) const {
		if (num == _intInf) return false;
		else if (b.num == _intInf) return true;
		else return num < b.num;
	}

	bool operator>(EntInf const& b) const {
		return b < *this;
	}

	void print(std::ostream & out = std::cout) const {
		if (num == _intInf) out << "+Inf";
		else out << num;
	}
};

const EntInf Infinito(EntInf::_intInf);

inline std::ostream & operator<<(std::ostream & out, EntInf const& e) {
	e.print(out);
	return out;
}

#endif



void Floyd(Matriz<EntInf> const& G, Matriz<EntInf> & C, Matriz<int> & A) {
	int V = G.numfils(); // número de vértices de G
						 // inicialización
	C = G;
	A = Matriz<int>(V, V, -1);
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (i != j && G[i][j] != Infinito) A[i][j] = i;
		}
	}
	// actualizaciones de las matrices
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				auto temp = C[i][k] + C[k][j];
				if (temp < C[i][j]) { // es mejor pasar por k
					C[i][j] = temp;
					A[i][j] = A[k][j];
				}
			}
		}
	}
}


bool resuelveCaso() {
	int P, R, vertice;
	unordered_map<string, int> entrada;

	cin >> P >> R;
	if (!cin)
		return false;
	vertice = 0;

	Matriz<EntInf> grafo(P, P, Infinito);
	for (int i = 0; i < P; ++i) {
		grafo[i][i] = 0;
	}
	for (int i = 0; i < R; i++) {
		string nombre1, nombre2;
		cin >> nombre1 >> nombre2;
		if (entrada.count(nombre1) == 0) {
			entrada[nombre1] = vertice  ;
			vertice++;
		}
		if (entrada.count(nombre2) == 0) {
			entrada[nombre2] = vertice;
			vertice++;
		}
		grafo[entrada[nombre1]][entrada[nombre2]] = 1;
		grafo[entrada[nombre2]][entrada[nombre1]] = 1;

	}
		
	Matriz<EntInf> C;
	Matriz<int> S;

	Floyd(grafo, C, S);

	EntInf maximo=0;
	for (int i = 0; i < P; ++i) {
		for (int j = 0; j < P; ++j)
			maximo = max(maximo, C[i][j]);
	}

	if (maximo == Infinito) cout << "DESCONECTADA\n";
	else cout << maximo << "\n";

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



/*
int main() {

	// construcción del grafo
	int V = 5;
	Matriz<EntInf> grafo(V, V, Infinito);
	for (int i = 0; i < V; ++i) {
		grafo[i][i] = 0;
	}

	grafo[0][1] = 3;
	grafo[0][2] = 8;
	grafo[0][4] = -4;
	grafo[1][4] = 7;
	grafo[1][3] = 1;
	grafo[2][1] = 4;
	grafo[3][2] = -5;
	grafo[3][0] = 2;
	grafo[4][3] = 6;

	Matriz<EntInf> C;
	Matriz<int> S;

	Floyd(grafo, C, S);

	int u = 2, v = 4;
	cout << "Coste de " << u << " a " << v << ": " << C[u][v] << '\n';
	// debe salir: Coste de 2 a 4: 3
	if (C[u][v] != Infinito) {
		auto cam = ir_de(u, v, S);
		cout << "Camino:";
		for (int v : cam) cout << ' ' << v; cout << '\n';
		// debe salir: Camino: 2 1 3 0 4
	}

	return 0;
}*/
