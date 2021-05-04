//////////////////////////////////////////////////
//		Colas de prioridad
//////////////////////////////////////////////////
/*
Colas de mínimos y colas de máximos

priority_queue de la std lib de c++ es de máximos
	Cambiando el objeto comparador por > pordemos usarla como cola de minimos*/
priority_queue<int, vector<int>, greater<int>> cola_min;


// b??? sí, para usar std priority_q como cola de máximos
bool operator<(usuario const& a, usuario const& b) {
	return b.momento < a.momento || (a.momento == b.momento && b.id < a.id);
}
////////////////////////////////////////////////

struct mi_comparador {
	bool operator()(miobjeto const& a, miobjeto const& b) {
		return b.x < a.x;
	}
};
priority_queue<int, vector<int>, mi_comparador> cola;



//////////////////////////////////////////////////
//		Implementación de colas: Montículos 
//////////////////////////////////////////////////
/* 
Mejor que implementación con vectores
	 push & pop	log N
Árbol binario completo
	completo:		todos sus hijos al mismo nivel
	semicompleto:	o completo o falta el último hijo, a la derecha, o los últimos

	altura h, nivel i
		completo	2^i-1 nodos en nivel i
		semicompleto	[log n] +1	([parte entera])

MONTICULO de mmínimos
	Árbol binario semicompleto
	raíz <= hijo izq
		 >	     der
	hijos son montículos

Implementación

				i			Padre de i en i/2
			2i	  2i+1		
			*/
	template<typename T, typename Comparator = std::less<T>>
	class PriorityQueue{
		std::vector<T> array;
		Comparator antes

	public:
		void insertar(e){
			array.push(e);
			flotar(array.size() - 1);//////////////////////// O log N
		
			void eliminar(e){
				if (empty)
					throw error
				else
					array[1] = array.back();
					array.pop_back()
					hundir(1);		//////////////////////////////	O log N













