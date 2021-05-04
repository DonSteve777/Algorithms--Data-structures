#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

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

	int numfils() const { return datos.size(); }
	int numcols() const { return numfils() > 0 ? datos[0].size() : 0; }

	bool posCorrecta(int f, int c) const {
		return 0 <= f && f < numfils() && 0 <= c && c < numcols();
	}

private:
	std::vector<std::vector<Object>> datos;
};

template <typename Object>
inline std::ostream & operator<<(std::ostream & out, Matriz<Object> const& m) {
	for (int i = 0; i < m.numfils(); ++i) {
		for (int j = 0; j < m.numcols(); ++j) {
			out << m[i][j] << ' ';
		}
		out << '\n';
	}
	return out;
}

#endif


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


/*
Enfoque descendente

monedas(i, j) = min monedas para pagar j, 
	considerando monedas de tipo 1 al n

Recursión
si mi > j
	monedas(i -1, j) 	no cogemos tipo i: cogemos monedas m�s peque�as
si mi <= j
	min(
		monedas(i-1, j), 
		monedas(i, j-mi) +1)	
						min entre coger una moneda mas de este tipo
						y coger del siguiente

complejidad en espacio n*C
en tiempo n*C
*/
EntInf cambio(vector<int> const& M, int C) {
	int n = M.size();
	Matriz<EntInf> monedas(n + 1, C + 1, Infinito);	//realmente sólo hay que inicialziar la primera fila
	monedas[0][0] = 0;	// i = 0 : conjunto vacío de tipos de monedas

	for (int i = 1; i <= n; ++i) {
		monedas[i][0] = 0;	//cantidad a pagar 0
		for (int j = 1; j <= C; ++j)
			if (M[i - 1] > j)
				monedas[i][j] = monedas[i - 1][j];
			else
				monedas[i][j] = min(monedas[i - 1][j], monedas[i][j - M[i - 1]] + 1);
	}
	return monedas[n][C];
}

/////////////////////////////////////////////////////////////////
//			versión para reconstruir la solución
/////////////////////////////////////////////////////////////////

vector<int> cambio(vector<int> const& M, int C) {
	int n = M.size();
	Matriz<EntInf> monedas(n + 1, C + 1, Infinito);	//realmente sólo hay que inicialziar la primera fila
	monedas[0][0] = 0;	// i = 0 : conjunto vacío de tipos de monedas

	for (int i = 1; i <= n; ++i) {
		monedas[i][0] = 0;	//cantidad a pagar 0
		for (int j = 1; j <= C; ++j)
			if (M[i - 1] > j)
				monedas[i][j] = monedas[i - 1][j];
			else
				monedas[i][j] = min(monedas[i - 1][j], monedas[i][j - M[i - 1]] + 1);
	}
	//RECONSTRUCCI�N DE LA SOLUCI�N		O(max(n,C))
	vector<int> sol;
	if (monedas[n][C] != Infinity) {	//si hay solución
		int i = n, j = C;
		while (j > 0) {	//no se ha pagado todo
			if (M[i - 1] <= j && monedas[i][j] != monedas[i - 1][j]) {
				//tomamos una de tipo i
				sol.push_back(M[i - 1]);
				j = j - M[i - 1];
			}
			else
				--i;					//no tomamos tipo i

		}
	}
	return sol;
}

/*
Enfoque ascendente

complejidad en espacio C+1
en tiempo n*C
*/
/////////////////////////////////////////////////////////////////
//			Enfoque ascendente (REDUCCION DEL ESPACIO)
/////////////////////////////////////////////////////////////////
vector<int> cambio(vector<int> const& M, int C) {
	int n = M.size();
	vector<int> monedas(C + 1, Infinity);
	monedas[0] = 0 ;

	for (int i = 1; i <= n; i++) {
		for (int j = M[i - 1]; j <= C; ++j) {
			monedas[j] = min(monedas[j], monedas[j - M[i - 1]] + 1);
		}
	}
	//reconstrucci�n de la soluci�n
	vector<int> sol;
	if (monedas[C] != Infinity) {
		int i = n, j = C;
		while (j > 0) {	// no se ha pagado todo
			if (M[i - 1] <= j && monedas[j] == monedas[j - M[i - 1]] + 1) {
				sol.push_back(M[i - 1]);
				j = j - M[i - 1];
			}
			else --i;
		}
	}
	return sol;
}
