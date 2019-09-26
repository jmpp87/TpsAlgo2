#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include "DynamicArray.hpp"
#include "complex.hpp"
#include "ComplexSignal.hpp"

using namespace std;

#define NUMBER_PI  3.141592654

static Complex
Wn(size_t N, int k, size_t n);

static Complex 
Sumatory(const DynamicArray <Complex> &arr, int k);




ComplexSignal::ComplexSignal()
{
	arr = new DynamicArray<Complex>();
}

ComplexSignal::ComplexSignal(DynamicArray <Complex> *ar)
{
	arr = ar;
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

ComplexSignal* ComplexSignal::computeDFT()
{
	DynamicArray <Complex> *arrAux = new DynamicArray<Complex>( arr->getLength() );
	size_t N = arr->getLength();

	for (size_t k=0; k<N; k++){
				
	   (*arrAux)[k] = Sumatory(*arr, k);
    }	
	
	return new ComplexSignal( arrAux );
}

ComplexSignal* ComplexSignal::computeIDFT()
{
	DynamicArray <Complex> *arrAux = new DynamicArray<Complex>(arr->getLength());
	size_t N = arr->getLength();

	for (size_t k=0; k<N; k++){
				
	   (*arrAux)[k] = Sumatory(*arr, -k)/N;
    }	
	
	return new ComplexSignal( arrAux );
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
	for (size_t n=0; n<N; n++){
	
		sum = sum + arr[n] * Wn(N, k, n);
	} 
	
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




