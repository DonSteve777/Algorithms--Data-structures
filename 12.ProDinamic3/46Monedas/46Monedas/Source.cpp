
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include <algorithm>

//INF no es un valor de la matriz, por lo que podemos usar simplemente una constante muy elevada
const int INF = 1000000000;

struct tMoneda {
	int valor;
	int cantidad;

	tMoneda() {};
	tMoneda(int a, int b) : valor(a), cantidad(b) {};
};

/*
monedas(i,j) = numero minimo de monedas para pagar cantidad j considerando monedas del tipo 1 hasta el tipo i
t--> Numero de monedas a utilizar
Casos base
--> monedas(i,0) = 0
--> monedas(0,j) = INF

monedas (i,j) = monedas (i-1,j) si mi > j donde mi es el valor de la moneda
min(monedas(i-1, j),monedas(i-1,j-t*mi)+t ) mi < j
Coste de la solucion
-->Tiempo: Precio * Tipos de Moneda = N*precio
-->Espacio:N*precio + 2*N (vector de tMoneda)
*/
// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio´n, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, precio;
	std::cin >> N;
	if (!std::cin)
		return false;
	std::vector<tMoneda> lista(N + 1);

	for (int i = 1; i <= N; i++) {
		std::cin >> lista[i].valor;
	}

	for (int i = 1; i <= N; i++) {
		std::cin >> lista[i].cantidad;
	}

	std::cin >> precio;

	std:: vector<int> monedas(precio + 1, INF);
	//casos base: pagar cantidad 0
	monedas[0] = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = lista[i - 1]; j <= precio; j++) {
			int actual = INF;
			//calculamos el numero de monedas que necistamos, sera el minimo entre las que tengas disponibles o las del precio que hace falta/valor de la moneda
			int cantidad = std::min(lista[i].cantidad, j / lista[i].valor);

			//recorremos este numero de monedas para quedarnos con el minimo entre seleccionar cada una de las cantidades de monedas
			for (int t = 0; t <= cantidad; t++) {
				actual = std::min(actual, monedas[j - (t*lista[i].valor)] + t);
			}
			monedas[0] = actual;
		}
	}


	if (monedas[N][precio] == INF) std::cout << "NO\n";
	else std::cout << "SI " << monedas[N][precio] << "\n";


	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}