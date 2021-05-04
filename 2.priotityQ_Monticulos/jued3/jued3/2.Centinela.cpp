
// Álvaro Abad de Donesteve

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "PriorityQueue.h"  // de máximos, top devuelve máx

using namespace std;

//class com_registro{ tb vale
struct comp_lessEqual {
	bool operator()(int a, int b) {
		return a <= b;
	}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int n, x;
   // leer los datos de la entrada
	cin >> n;
   if (n == 0)
      return false;
   PriorityQueue<int, comp_lessEqual> cola;

   for (int i = 0; i < n; i++) {
	   cin >> x;
	   cola.push(x);
   }
   int esfuerzo = 0;

   //algortimo O(N log N)
   while (cola.size() > 1) {	//O(k log N)
	   auto a = cola.top();	//O(1)
	   cola.pop();	//O(log N)
	   auto b = cola.top();	//O(1)
	   cola.pop();	//O(log N)
	   esfuerzo += a + b;
	   
	   if (!cola.empty())
		cola.push(a+b);
   }
   cout << esfuerzo << endl;
   
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
