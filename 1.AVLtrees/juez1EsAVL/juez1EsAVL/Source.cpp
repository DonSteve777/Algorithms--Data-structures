#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>

#include "bintree_eda.h"
using namespace std;

//AVL condition: raiz > left y raiz < right
bool AVLcondition1( bintree<int> const & left, int e, bintree<int> const & right) {
	int elemLeft = e - 1, elemRight = e + 1;
	if (!left.empty())
		elemLeft = left.root();
	if (!right.empty())
		elemRight = right.root();

	if (elemLeft >= e || elemRight <= e)
		return false;
}

//AVL condition:  alturaLeft - alturaRight < 2
bool AVLcondition2(int alturaLeft, int & altura, int alturaRight) {
	if (alturaLeft > alturaRight)
		altura = alturaLeft + 1;
	else
		altura = alturaRight + 1;
	if ( abs(alturaLeft - alturaRight) > 1)
		return false;
	return true;
}

bool leeYesAVL(bintree<int> & tree, int & altura) {
	int e;
	cin >> e;
	if (!cin)
		return true;

	if (e != -1) {
		bintree<int> leftTree;
		bintree<int> rightTree;
		int alturaLeft = altura, alturaRight = altura;

		if (!leeYesAVL(leftTree, alturaLeft) || !leeYesAVL(rightTree, alturaRight))
			return false;
		tree = bintree<int>(leftTree, e, rightTree);

		if (!AVLcondition1(leftTree, e, rightTree))
			return false;
		if (!AVLcondition2(alturaLeft, altura, alturaRight))
			return false;
	}
	return true;
}

bool leeYesAVL() {
	bintree<int> tree;
	int altura = 0;

	return leeYesAVL(tree, altura);
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

	if (leeYesAVL())
		cout << "SI\n";
	else
		cout << "NO\n";
  }

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
