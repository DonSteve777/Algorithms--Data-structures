
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
string resolver(int eventos, int v[]) {
	while (eventos) {

	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int eventos, v[200000];
   // leer los datos de la entrada
	cin >> eventos;
   if (!std::cin)  // fin de la entrada
      return false;
   PriorityQueue<int> cola;
   for (int i = 0; i < eventos; i++) {
	   cin >> v[i];
	   if (v[i] == 0) {
		   cola.heapsort(v, Comparator());
	   }
   }
	   
   cout << resolver( eventos,  v) << "\n";
   
   // escribir sol
   
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
