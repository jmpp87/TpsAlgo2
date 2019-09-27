#ifndef DYNAMIC_ARRAY__H
#define DYNAMIC_ARRAY__H

#include <iostream>
#include <cstdlib>


using namespace std;


template< typename T > class DynamicArray;
template< typename T > istream &operator>>(istream &, DynamicArray< T > &);  
template< typename T > ostream &operator<<(ostream &, const DynamicArray< T > &); 


// Definición clase Arreglo Dinámico Genérico

template< class T >
class DynamicArray{
	
	private:
		size_t allocMemorySize_;
		size_t length_;
		T *array_;

		// Método privado que redimensiona el tamaño del arreglo
		bool resize();
		
	public:
		// CONSTRUCTORES

			// Constructor por defecto
			DynamicArray();

			// Constructor por parámetro
			DynamicArray(size_t);

			// Constructor por copia
			DynamicArray(const DynamicArray< T > &);

		// FIN CONSTRUCTORES


		// DESTRUCTOR

			~DynamicArray();
		
		// FIN DESTRUCTOR


		// OPERACIONES DE UN ARREGLO


			// Método para obtener longitud del arreglo
			size_t getLength()const;

		
			// Método para obtener sin modificar el valor del i-esimo elemento del arreglo
			T const &operator[](size_t)const;

			// Método para obtener el valor del i-esimo elemento del arreglo
			T &operator[](size_t);

			// Método asignación entre arreglos 
			DynamicArray< T > const &operator=(const DynamicArray< T > &);

			// Método para chequear si el arreglo está vacío 
			bool empty()const;
	
			friend ostream &operator<< <>(ostream &, const DynamicArray< T > &);

			friend istream &operator>> <>(istream &, DynamicArray< T > &);	

		// FIN OPERACIONES DE UN ARREGLO


		
}; // Fín de la clase Arreglo Dinámico Genérico

#include "DynamicArray.cpp"

#endif

