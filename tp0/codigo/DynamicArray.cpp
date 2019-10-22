#ifndef DYNAMIC_ARRAY__CPP
#define DYNAMIC_ARRAY__CPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

#include "DynamicArray.hpp"

#define INIT_CHOP_SIZE	1
#define GROWTH_FACTOR	2

using namespace std;
using std::setw;

// Implementación métodos de la clase Arreglo Dinámico Genérico

// Método privado que redimensiona el tamaño del arreglo
template < class T >
bool 
DynamicArray< T >::resize()
{
	T* newArray;


	if( length_ == 0 && allocMemorySize_ == 0 ){
		if( !( array_ = new T[INIT_CHOP_SIZE]) )
			return	false;	
		
		allocMemorySize_=INIT_CHOP_SIZE;
		
	}
	else{
		if( !(newArray = new (std::nothrow) T[allocMemorySize_ * GROWTH_FACTOR]) )
			return	false;
		
		for(size_t i = 0; i < length_; i++)
			newArray[i] = array_[i];	
		allocMemorySize_*=GROWTH_FACTOR;
		
		delete []array_;

		array_ = newArray;
	}



	return	true;
}

// Constructor por default
template < class T >
DynamicArray< T >::DynamicArray():allocMemorySize_(0),length_(0), array_(0){} 

// Constructor por parámetro
template <class T>
DynamicArray<T>::DynamicArray(size_t len):allocMemorySize_(len), length_(len)
{



	if( !(array_ = new (std::nothrow)T[allocMemorySize_]) ){ 
		std::cout << "There is not enough memory" << std::endl;
		exit(1);
	}



}

// Constructor por copia
template < class T >
DynamicArray< T >::DynamicArray(const DynamicArray< T > &orig)
{



	if( !orig.empty() ){
		allocMemorySize_=orig.allocMemorySize_;
		

		length_ = orig.length_;
		 
		if( !(array_ = new (std::nothrow)T[allocMemorySize_]) ){
			std::cout << "There is not enough memory" << std::endl;
			exit(1);
		}
		
		for(size_t i = 0; i < length_; i++)
			array_[i] = orig.array_[i];
	}   



}

// Destructor
template < class T >
DynamicArray< T >::~DynamicArray()
{
	delete []array_;
}

// Método para obtener la longitud del arreglo
template < class T >
size_t
DynamicArray< T >::getLength()const
{
	return length_;
}


// Método para obtener sin modificar el valor del i-esimo elemento del arreglo
template < class T >
T const &
DynamicArray< T >::operator[](const size_t index)const
{



	if ( length_ != 0 ){

		if ( ( 0 <= index ) && ( index < length_ ) )
			return array_[index];

		else{
			cerr<<"invalid indexation."<<endl; 
			exit(1);
		}

	}
	else{ 
		cerr<<"array is empty."<<endl;
		exit(1);	
	}



}

// Método para indexar el i-esimo elemento del arreglo para despues poder asignarle un nuevo valor
template < class T >
T &
DynamicArray< T >::operator[](const size_t index)
{



	if(length_ != 0){

		if ( ( 0 <= index ) && ( index < length_ ) )
			return array_[index];
		else{
			cerr<<"invalid indexation."<<endl;
			exit(1);
		}
	}
	else{
		cerr<<"array is empty."<<endl;
		exit(1);
	} 



}

// Método asignación entre arreglos
template < class T >
DynamicArray< T > const &
DynamicArray< T >::operator=(const DynamicArray< T > &orig)
{	
	T *aux;



		if( this != &orig ){ // Evita la autoasignación
		
			if( length_ != orig.length_ ){
				
				allocMemorySize_=orig.allocMemorySize_;
				if( !(aux = new T[allocMemorySize_]) ){
					std::cerr << "There is not enough memory" << std::endl;
					exit(1);
				}

				delete []array_;	
				array_ = aux;
				length_ = orig.length_;
				
			}
			
			
			for ( size_t i = 0; i < length_; i++ )
				array_[i] = orig.array_[i]; 
		}

		else cerr<<"array=array is forbidden use.";

		

	return *this;
}

// Método para chequear si está vacío el arreglo
template < class T >
bool
DynamicArray< T >::empty()const
{
	return ( array_ == 0 ) ? true : false;
	
}



template < class T > 
ostream &
operator<<(ostream &os, const DynamicArray< T > &arr)
{
	for(size_t i = 0; i < arr.length_; i++)
	 os<<arr[i]<<" ";	
	return os;
}



template < class T >
istream &
operator>>(istream &is , DynamicArray< T > & array)
{
	T c;
	size_t i = 0;
	char ch;
	
	// Seteo que la longitud inicial de array es 0
	// cada vez que utilizo el operador >>
	// para meter un tira de datos de tipo T
	array.length_ = 0;
	//Como solo espacios y lineas nuevas
	while( is.get(ch) && ch != '\n' && ( ch == ' ' || ch == '\t' ) );
	if(  !is.eof()  && ch != '\n' )
	{	
		is.putback(ch);
		while( (is >> c) && !is.eof() )
		{
			
			if( array.length_ == array.allocMemorySize_ ){ 

				if( array.resize() == false ){
					std::cerr << "There is not enough memory" << std::endl;
					exit(1);
				}
			} 
			
			array.array_[i++] = c;
			array.length_++;

			while( is.get(ch) && ch != '\n' && ( ch == ' ' || ch == '\t' ) );
			if(is.eof()) break;
			if(ch == '\n') break;
			else is.putback(ch);
		}

	}
	return is;
}


#endif
