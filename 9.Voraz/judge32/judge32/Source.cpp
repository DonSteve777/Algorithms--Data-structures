#include <iostream>
#include <fstream>
#include <algorithm>
#include<vector>
using namespace std;

#define MAX 1000000000 

struct Trabajo {
	int c;
	int f;
};

struct myclass1 {
	bool operator() (Trabajo a, Trabajo b) {
		return a.c < b.c || a.c == b.c && a.f > b.f;	//para que si a.c == b.c me quede con la mas larga (sobreescribo en el vector solucion al primero)
	}
} myobject;

/*
yo meteria conjuntos disjuntos para saber que tramos corresponden al mismo trabajo
pero el tam de los datos es demasiado grande
*/
int voraz(vector<Trabajo> v, int C, int F) {
	int ret = 0;
	int lastNew_c = -1;
	int lastNew_f = -1;
	
	if (v[0].c > C)
		return -1;
	lastNew_c = C;
	lastNew_f = v[0].f;
	ret++;

	int i = 1;
	while(i < v.size() && ret > -1 && lastNew_f < F){
		ret++;
		if (v[i].c > lastNew_f)	//hueco. Imosible abarcar todo
			ret = -1;
		else if (v[i].c <= lastNew_c && v[i].f >= lastNew_f) {	//tramo anterior ya es cubierto por tramo actual
			//actual cubre mas
			lastNew_f = v[i].f;
			ret--;	//descarto tramo (anterior primer if, o actual en else)
		}
		else if (v[i].c > lastNew_c && v[i].f <= lastNew_f) {	//tramo redundante
			ret--;
		}
		else        //tramo completamente nuevo
		{
			lastNew_c = lastNew_f;
			lastNew_f = v[i].f;
		}
		i++;
	}
	return ret;
}

bool resuelveCaso() {
	int C, F, N; // 0 <= C < F <= 10^9

	cin >> C >> F >> N;
	if (!C && !F && !N)
		return false;

	vector<Trabajo> v(N);
	for (int i = 0; i < N; i++) {
		cin >> v[i].c >> v[i].f;
	}
	sort(v.begin(), v.end(), myobject);
	int ret;
	
	if (N > 0)
		if (C + 1 == F)
			ret = 0;
		else
			ret = voraz(v, C, F);
	else
		ret = -1;


	if (ret > -1)
		cout << ret << '\n';
	else
		cout << "Imposible\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
