#ifndef COMPLEX_SIGNAL_H_INCLUDED
#define COMPLEX_SIGNAL_H_INCLUDED

#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "DynamicArray.hpp"
#include "complex.hpp"


using namespace std;


class ComplexSignal
{
	private:
		
		DynamicArray <Complex> *arr;
    
	public:
    
		ComplexSignal();
		ComplexSignal(DynamicArray <Complex> *);
		~ComplexSignal();
		
		friend istream &operator>>(istream &, ComplexSignal &);
		friend ostream &operator<<(ostream &, const ComplexSignal &);		
		
		ComplexSignal* computeDFT();
		ComplexSignal* computeIDFT();
};


#endif
