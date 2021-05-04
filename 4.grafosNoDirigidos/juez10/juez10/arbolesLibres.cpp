
// Álvaro Abad de Donesteve

//Recorrido en profundidad: O(V+A) para listas de adyacentes y O(n^2) para matrices de adyaciencia
//árbol libre: 
//		conexo: se recorren todos los vértices en un recorrido en profundidad
//		y acíclico => tiene v-1 aristas para los v vértices
//
#include <iostream>
#include <fstream>
#include "ArbolLibre.h"

using namespace std;
// función que resuelve el problema
// comentario sobre

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
  int V, A;
   // leer los datos de la entrada
   cin >> V;
   if (!std::cin)  // fin de la entrada
      return false;
    cin >> A;
    Grafo grafo(V);
    int a, b; //aristas
    for (int i =0; i < A; ++i){
      cin >> a >> b;
      grafo.ponArista(a, b);
    }
    ArbolLibre arbol = ArbolLibre(grafo);
	if (arbol.esLibre())
		cout << "SI\n";
	else
		cout << "NO\n";
   return true;
}

int main() {/*
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif*/

   while (resuelveCaso());
   /*
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif*/
   return 0;
}
