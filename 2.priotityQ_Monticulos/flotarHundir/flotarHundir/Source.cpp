#include<iostream>
#include "PriorityQueue.h"

using namespace std;

int main() {
	PriorityQueue<int> cola;
	cola.push(15);
	cola.push(20);
	cola.push(8);
	cola.push(18);
	cola.pop();
	cola.push(7);
	cola.push(10);
	cola.push(3);
	cola.pop();
	cola.pop();
	cola.push(2);
	
	return 0;
}