#include<iostream>
#include "TreeSet_AVL.h"
using namespace std;

/*
Para practicar las rotaciones, comienza con un árbol vacío, y ves insertando uno a uno los siguientes elementos, dibujando el árbol tras cada inserción:
el 3, el 2 y el 1;
después los valores del 4 al 7, en ese orden;
después los valores del 10 al 16, en orden inverso (16, 15, 14...);
y por último los valores 8 y 9.
*/

int main() {
	Set<int> set = Set<int>();
	set.insert(3);
	set.insert(2);
	set.insert(1);
	set.insert(4);
	set.insert(5);
	set.insert(6);
	set.insert(7);
	set.insert(16);
	set.insert(15);	//rota doble der izq
	set.insert(14);
	set.insert(13);	//rot simple izq no intuitiva
	set.insert(12);
	set.insert(11);
	set.insert(10);
	set.insert(8);
	set.insert(9);

	return 0;
}

