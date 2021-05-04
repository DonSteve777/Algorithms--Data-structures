#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

struct Objeto {
	double, peso, valor;
};

struct Nodo {
	vector<bool> sol;
	int k;
	double peso;
	double beneficio;
	deouble beneficio_est;
	bool operator<(Nodo const & otro) cosnt {
		return otro.beneficio_est > beneficio_est;
	}
};

//estimacion: cota superior
// seleccionar todos los demas objetos es demasiado optimista por no tener en cuenta el espacio libre
//voraz fraccionable: optima. no puede haber una sol mejor sin fraccionar
//objetos ordenados en orden decreciente por densidad v/p
//	beneficio + vk + estimacion de k+1 hasta n
double calculo_voraz(vector<Objeto> const& objetos, double M, Nodo const& X) {
	double hueco = M - X.peso, estimacion = X.beneficio;
	int i = X.k + 1;
	//todos los que caben los meto
	while (i < objetos.size() && objetos[i].peso <= hueco) {
		hueco -= objetos[i].peso;
		estimacion += objetos[i].valor;
		++i;
	}
	if (i < objetos.size())
		estimacion += (hueco / objetos[i].peso) * objetos[i].valor;
	return estimacion;
}

void mochila_rp(vector<Objeto> const& objetos, double M, vector<bool> & sol_mejor, double & beneficio_mejor) {
	int N = objetos.size();
	//se genera la raiz
	Nodo Y;
	Y.sol = vector<bool>(N);
	Y.k = -1;
	Y.peso = Y.beneficio = 0;
	Y.beneficio_est = calculo_voraz(objetos, M, Y);
	priority_queue<Nodo> cola;
	cola.push;
	beneficio_mejor - 1;

	while (!cola.empty() && cola.top().beneficio_est > beneficio_mejor) {
		Y = cola.top(); cola.pop();
		Nodo X(Y);
		++X.k;
		if (U.peso + objetos[X.k].peso <= M) {
			X.sol[X.k] = true;
			X.peso = Y.peso + objetos[X.k].peso;
			X.valor = Y.valor + objetos[X.k].valor;
			X.beneficio_est = Y.beneficio_est;	//la estimacion coge todos los objeots, y solo cambia con el ultimo, fraccinado
			if (X.k == N - 1) {
				sol_mejor = X.sol;
				beneficio_mejor = X.beneficio;
			}
			else
				cola.push(X);
		}
	}
	// no meter el objeto
	X.sol[X.k] = false;
	X.peso = Y.peso;
	X.beneficio = Y.beneficio;
	X.beneficio_est = calculo_voraz(objetos, M, X);	
	if (X.beneficio_est > beneficio_mejor) {
		if (X.k == N - 1) {
			sol_mejor = X.sol;
			beneficio_mejor = X.beneficio;
		}
		else
			cola.push(X);
			
	}
}