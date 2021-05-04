//////////////////////////////////////////////////
//		Colas de prioridad
//////////////////////////////////////////////////
/*
Colas de m�nimos y colas de m�ximos

priority_queue de la std lib de c++ es de m�ximos
	Cambiando el objeto comparador por > pordemos usarla como cola de minimos*/
priority_queue<int, vector<int>, greater<int>> cola_min;


// b??? s�, para usar std priority_q como cola de m�ximos
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
//		Implementaci�n de colas: Mont�culos 
//////////////////////////////////////////////////
/* 
Mejor que implementaci�n con vectores
	 push & pop	log N
�rbol binario completo
	completo:		todos sus hijos al mismo nivel
	semicompleto:	o completo o falta el �ltimo hijo, a la derecha, o los �ltimos

	altura h, nivel i
		completo	2^i-1 nodos en nivel i
		semicompleto	[log n] +1	([parte entera])

MONTICULO de mm�nimos
	�rbol binario semicompleto
	ra�z <= hijo izq
		 >	     der
	hijos son mont�culos

Implementaci�n

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













