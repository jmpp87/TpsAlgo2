#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include "DynamicArray.h"
#include "complex.h"
#include "ComplexSignal.h"

using namespace std;

#define NUMBER_PI  3.141592654


static Complex
Wn(size_t N, int k, size_t n);

static Complex 
Sumatory(const DynamicArray <Complex> &arr, int k);

static
DynamicArray <Complex> *
getEvenElements(const DynamicArray <Complex> &arr);

static
DynamicArray <Complex> *
getOddElements(const DynamicArray <Complex> &arr);


ComplexSignal::ComplexSignal()
{
	arr = new DynamicArray<Complex>();
}

ComplexSignal::ComplexSignal(DynamicArray <Complex> *ar)
{
	arr = ar;
}

const size_t
ComplexSignal::getLength() const
{
	return arr->getLength();
}

bool
ComplexSignal::increaseLength(size_t const newLength)
{
	return arr->increaseLength(newLength);
}


istream & operator>>(istream &is, ComplexSignal &v)
{
	is>>*(v.arr);
	return is;
}

ostream & operator<<(ostream &os, const ComplexSignal &v)
{
	os<<*(v.arr);
	os<<endl;
	return os;
}

ComplexSignal* ComplexSignal::computeDFT() const
{
	DynamicArray <Complex> *arrAux = new DynamicArray<Complex>( arr->getLength() );
	size_t N = arr->getLength();

	for (size_t k=0; k<N; k++){
				
	   (*arrAux)[k] = Sumatory(*arr, k);
    }	
	
	return new ComplexSignal( arrAux );
}



DynamicArray <Complex> *
ComplexSignal::_computeFFT(const DynamicArray <Complex> &arr) const
{
	size_t k,i;
	
	DynamicArray <Complex> *transformedElements =
	new DynamicArray <Complex>( arr.getLength() );
	
	
	if(arr.getLength() > 1){
		
		
		DynamicArray <Complex> *evenElements = getEvenElements(arr);
		DynamicArray <Complex> *oddElements = getOddElements(arr);
		
		DynamicArray <Complex> *transformedEvenElements = this->_computeFFT( *evenElements );
		DynamicArray <Complex> *transformedOddElements = this->_computeFFT( *oddElements );
		
		delete evenElements;
		delete oddElements;
		
		
		for( k = 0; k < arr.getLength(); )
			for( i = 0; i < transformedEvenElements->getLength(); k++, i++)
			{			
				(*transformedElements)[k] = (*transformedEvenElements)[i] + 
										 Wn( arr.getLength(), k, 1) * 
										 (*transformedOddElements)[i];											
			}
		
		delete 	transformedEvenElements;
		delete transformedOddElements;
	}
	else (*transformedElements)[0] = arr[0];
	
	return transformedElements;
}



ComplexSignal* ComplexSignal::computeFFT() const
{
	return new ComplexSignal( this->_computeFFT( *arr) );
}


ComplexSignal* ComplexSignal::computeIDFT() const
{
	DynamicArray <Complex> *arrAux = new DynamicArray<Complex>(arr->getLength());
	size_t N = arr->getLength();

	for (size_t k=0; k<N; k++)
		(*arrAux)[k] = Sumatory(*arr, -k)/N;
    
	
	return new ComplexSignal( arrAux );
}


DynamicArray <Complex> *
ComplexSignal::_computeIFFT(const DynamicArray <Complex> &arr) const
{
	size_t k,i;
	
	DynamicArray <Complex> *transformedElements =
	new DynamicArray <Complex>( arr.getLength() );
	
	
	if(arr.getLength() > 1){
		
		
		DynamicArray <Complex> *evenElements = getEvenElements(arr);
		DynamicArray <Complex> *oddElements = getOddElements(arr);
		
		
		DynamicArray <Complex> *transformedEvenElements = this->_computeIFFT( *evenElements );
		DynamicArray <Complex> *transformedOddElements  = this->_computeIFFT( *oddElements );
		
		delete evenElements;
		delete oddElements;
		
		
		for( k = 0; k < arr.getLength(); )
			for( i = 0; i < transformedEvenElements->getLength(); k++, i++)
			{			
				(*transformedElements)[k] = ( (*transformedEvenElements)[i] + 
										 Wn( arr.getLength(), -k, 1) * 
										 (*transformedOddElements)[i] )
										 /2;											
			}
			
		delete 	transformedEvenElements;
		delete transformedOddElements;	
	}
	else (*transformedElements)[0] = arr[0];
	
	return transformedElements;
}




ComplexSignal* ComplexSignal::computeIFFT() const
{
	return new ComplexSignal( this->_computeIFFT( *arr) );
}

ComplexSignal::~ComplexSignal()
{
	delete arr;
}


static Complex 
Sumatory(const DynamicArray <Complex> &arr, int k)
{	
	Complex sum;
	size_t N = arr.getLength();
	
	for (size_t n=0; n<N; n++)	
		sum = sum + arr[n] * Wn(N, k, n);
		
	return sum;
}

static Complex
Wn(size_t N, int k, size_t n)
{
	double aux;
	aux = (2*NUMBER_PI*n*k)/N;
	double re = cos(aux);
	double im = sin(aux);
	im = -1*im;
	Complex wn(re,im);
	
	return  wn;	
}

static
DynamicArray <Complex> *
getEvenElements(const DynamicArray <Complex> &arr)
{
	size_t i,j;
	
	DynamicArray <Complex> *evenElements =
	new DynamicArray <Complex>( ceil( arr.getLength()/2 ) );
	
	
	for(i = 0, j= 0; i < arr.getLength(); i+=2, j++){
		
		(*evenElements)[j] = arr[i];
	}
	
	return evenElements;
}

static
DynamicArray <Complex> *
getOddElements(const DynamicArray <Complex> &arr)
{
	
	size_t i,j;
	
	DynamicArray <Complex> *oddElements =
	new DynamicArray <Complex>( floor( arr.getLength()/2 ) );
	
	
	for(i = 1, j = 0; i < arr.getLength(); i+=2, j++){
		
		(*oddElements)[j] = arr[i];
	}
	
	return oddElements;
		
}

