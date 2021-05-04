#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

struct Tarea {
	double t, p, c;
};

struct Nodo {
	vector<bool> sol;
	int k;
	double tiempo;	//tiempo acumulado
	double coste;	//coste acumulado
	double coste_estimado;	//prioridad
	// op para std priority queue
	bool operator<(Nodo const& otro) const {
		return otro.coste_estimado < coste_estimado;
	}
};

double calculo_estimacion(vector<Tarea> const & tareas, Nodo const& X) {
	double estimacion = X.coste;
	//todas las no seleccionadas aun
	for (int i = X.k + 1; i < tareas.size(); ++i) {
		//calculo del coste si la tarea se pasa del plazo
		if (X.tiempo + tareas[i].t > tareas[i].p)
			estimacion += tareas[i].c;
	}
	return estimacion;
}

//tareas ordenadas de menor a mayor plazo
void tareas_rp(vector, Tarea > const& tareas, vector<bool> & sol_mejor, double & coste_mejor) {
	int N = tareas.size();
	//generar raiz
	Nodo Y;
	Y.sol = vector<bool>(N, false);
	Y.k = -1;
	Y.tiempo = Y.coste = 0;
	Y.coste_estimado = calculo_estimacion(tareas, Y);
	priority_queue<Nodo> cola;
	cola.push(Y);
	coster_mejor = numeric_limits<double>::inifinity();

	while (!cola.empty() && cola.top().coste_estimado < coste_mejor) {
		Y = cola.top();	cola.pop();
		Nodo X(Y);
		++X.k;
		//hijo izquierdo, realizar tarea
		if (Y.tiempo + tareas[X.k].t <= tareas[X.k].p) {
			X.sol[X.k] = true;
			X.tiempo = Y.tiempo + tareas[X.k].t;
			X.coste = Y.coste;
			X.coste_estimado = calculo_estimacion(tareas, X);
			if(X.coste_estimado < coste_mejor)
				if (X.k == N - 1) {
					sol_mejor = X.sol;
					coste_mejor = X.coste;
				}
				else
					cola.push();
		}
		//hijo derecho, no realizar
		X.sol[X.k] = false;
		X.tiempo = Y.tiempo;
		X.coste = Y.coste + tareas[X.k].c;
		X.coste_estimado = calculo_estimacion(tareas, X);
		if (X.coste_estimado < coste_mejor) {
			if (X.k == N - 1) {
				sol_mejor = X.sol;
				coste_mejor = X.coste;
			}
			else
				cola.push(X);
		}

	}
}