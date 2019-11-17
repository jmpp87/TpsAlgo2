#ifndef COMPLEX_SIGNAL_H_INCLUDED
#define COMPLEX_SIGNAL_H_INCLUDED

#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "DynamicArray.h"
#include "complex.h"

using namespace std;

class ComplexSignal
{
	private:
		
		DynamicArray <Complex> *arr;
		
		DynamicArray <Complex> * _computeFFT(const DynamicArray <Complex> &arr) const;
		DynamicArray <Complex> * _computeIFFT(const DynamicArray <Complex> &arr) const;
	public:
    
		ComplexSignal();
		ComplexSignal(DynamicArray <Complex> *);
		~ComplexSignal();
		
		size_t const getLength() const;
		bool increaseLength(size_t const);
		
		friend istream &operator>>(istream &, ComplexSignal &);
		friend ostream &operator<<(ostream &, const ComplexSignal &);		
		
		ComplexSignal* computeDFT() const;
		ComplexSignal* computeFFT() const;
		ComplexSignal* computeIDFT() const;
		ComplexSignal* computeIFFT() const;
};
#endif
