#include <iostream>
#include <cmath>

#include "complex.hpp"


// Constructor por default
Complex::Complex(): re_(0), im_(0)
{
}

// Constructor por parámetro real
Complex::Complex(double re): re_(re), im_(0)
{
}

// Constructor por parámetros real e imaginario
Complex::Complex(double re,double im): re_(re), im_(im)
{
}

// Constructor por copia
Complex::Complex(const Complex &orig): re_(orig.re_), im_(orig.im_)
{
}

// Destructor
Complex::~Complex()
{
}

// Método de asignación entre complejos
Complex const &
Complex::operator=(const Complex &c)
{
	re_=c.re_;
	im_=c.im_;
	return *this;
}

// Método de asignación a la parte real de un complejo
Complex const &
Complex::operator=(double r)
{
	re_=r;
	
	return *this;
}

// Método suma y asignación entre complejos
Complex const &
Complex::operator+=(const Complex &c)
{
	re_+=c.re_;
	im_+=c.im_;
	
	return *this;
}

// Método suma y asignación a la parte real de un complejo
Complex const &
Complex::operator+=(double r)
{
	re_+=r;
	
	return *this;
}

// Método resta y asignación entre complejos
Complex const &
Complex::operator-=(const Complex &c)
{
	re_-=c.re_;
	im_-=c.im_;
	
	return *this;
}

// Método resta y asignación a la parte real de un complejo
Complex const &
Complex::operator-=(double r)
{
	re_-=r;

	return *this;
}

// Método multiplicación y asignación entre complejos
Complex const &
Complex::operator*=(const Complex &c)
{
	re_= re_*c.re_ - im_*c.im_;
	im_= re_*c.im_ + im_*c.re_;
	
	return *this;
}

// Método multiplicación y asignación a la parte real de un complejo
Complex const &
Complex::operator*=(double r)
{
	re_*=r;
	im_*=r;
	
	return *this;
}

// Método división y asignación entre complejos
Complex const &
Complex::operator/=(const Complex &c)
{
	*this=*this*c.computeConjugated()/c.computeAbs2();
	
	return *this;
}

// Método división y asignación a la parte real de un complejo
Complex const &
Complex::operator/=(double r)
{
	re_/=r;
	im_/=r;
	
	return *this;
}

// Método para cargar la parte real de un complejo
void
Complex::setRe(double r)
{
	re_=r;
}

// Método para cargar la parte imaginaria de un complejo
void
Complex::setIm(double i)
{
	im_=i;
}

// Método para cargar la parte real e imaginaria de un complejo
void 
Complex::setComplex(double r, double i)
{
	re_=r;
	im_=i;
}

// Método para conjugar un complejo
Complex const &
Complex::conjugate()
{
	im_=-im_;
	return *this;
}

// Método para obtener la parte real de un complejo
double
Complex::getRe() const
{
	return re_;
}

// Método para obtener la parte imaginaria de un complejo
double
Complex::getIm() const
{
	return im_;
}

// Método para computar el modulo de un complejo
double
Complex::computeAbs() const
{
	return sqrt(re_*re_+im_*im_);
}

// Método para computar el modulo al cuadrado de un complejo
double
Complex::computeAbs2() const
{
	return re_*re_+im_*im_;
}

double
Complex::computeAngle() const
{
	return atan2(im_,re_);
}

// Método para obtener el conjugado de un complejo
Complex const
Complex::computeConjugated() const
{
	return Complex(re_, -im_);
}

// Método que analiza si el complejo es o nulo
bool
Complex::isZero() const
{
#define ZERO(x) ((x) == +0.0 && (x) == -0.0)
	return ZERO(re_) && ZERO(im_) ? true : false;
}


// Método para sumar complejos
Complex const 
operator+(const Complex &c1, const Complex &c2)
{
	Complex z(c1.re_ + c2.re_, c1.im_ + c2.im_); 
	return  z;
}

// Método para sumarle una constante a la parte real de un complejo
Complex const 
operator+(const Complex &c1, double r)
{
	Complex z(c1.re_ + r, c1.im_); 
	return  z;
}

// Método para sumarle una constante a la parte real de un complejo
Complex const 
operator+(double r, const Complex &c1)
{
	Complex z(c1.re_ + r, c1.im_);
	return  z;
}

// Método para restar complejos
Complex const 
operator-(const Complex &c1, const Complex &c2)
{
	Complex z(c1.re_ - c2.re_, c1.im_ - c2.im_);
	return  z;
}

// Método para restarle una constante a la parte real de un complejo
Complex const 
operator-(const Complex &c1, double r)
{
	Complex z(c1.re_ - r, c1.im_);
	return  z;
}

// Método para restarle una constante a la parte real complejo
Complex const 
operator-(double r, const Complex &c1)
{
	Complex z(r - c1.re_ , c1.im_); 
	return  z;
}

// Método para multiplicar complejos
Complex const 
operator*(const Complex &c1, const Complex &c2)
{
	Complex z(c1.re_ * c2.re_ - c1.im_ * c2.im_,
			   c1.re_ * c2.im_ + c1.im_ * c2.re_); 
	return  z;
}

// Método para multiplicar la parte real e imaginaria de un complejo por una constante
Complex const 
operator*(const Complex &c1, double r)
{
	Complex z(c1.re_ * r, c1.im_ * r);
	return  z;
}

// Método para multiplicar la parte real de un complejo
Complex const 
operator*(double r, const Complex &c1)
{
	Complex z(r * c1.re_ , c1.im_ * r); 
	return  z;
}

// Método para dividir complejos
Complex const 
operator/(const Complex &c1, const Complex &c2)
{
	
	return  c1 * c2.computeConjugated() / c2.computeAbs2();
}

// Método para dividir la parte real e imaginaria de un complejo por una constante
Complex const 
operator/(const Complex &c1, double r)
{
	Complex z(c1.re_ / r, c1.im_ / r);
	return  z;
}

Complex const 
operator/(double r, const Complex &c1)
{
	
	return  r * c1.computeConjugated() / c1.computeAbs2();
}

// Método para evaluar si dos complejos son iguales
bool 
operator==(const Complex &c1, const Complex &c2)
{
	return (c1.re_==c2.re_ && c1.im_==c2.im_)? true: false;
}

// Método para evaluar si la parte real de un complejo es igual a una constante
bool 
operator==(const Complex &c1, double r)
{
	return (c1.re_==r && c1.im_==0)? true: false;
}

// Método para evaluar si la parte real de un complejo es igual a una constante
bool 
operator==(double r, const Complex &c1)
{
	return (c1.re_==r && c1.im_==0)? true: false;
}

// Método para evaluar si dos complejos son distintos
bool 
operator!=(const Complex &c1,const Complex &c2)
{
	return (c1.re_!=c2.re_ && c1.im_!=c2.im_)? true: false;
}

// Método para evaluar si la parte real de un complejo no es igual a una constante
bool 
operator!=(const Complex &c1, double r)
{
	return (c1.re_!=r && c1.im_!=0)? true: false;
}

// Método para evaluar si la parte real de un complejo no es igual a una constante
bool 
operator!=(double r, const Complex &c1)
{
	return (c1.re_!=r && c1.im_!=0)? true: false;
}

// Método para imprimir un complejo a través de un flujo
ostream &
operator<<(ostream &os, const Complex &c)
{
	os<<fixed;
	
	os << COMPLEX_BRACKETS_BEGIN_CHAR 
	   << c.re_
	   << COMPLEX_BRACKETS_SEPARATOR_CHAR
	   << c.im_
	   << COMPLEX_BRACKETS_END_CHAR;
			   
	return os;
}

// Método para leer un complejo a través de un flujo
istream &
operator>>(istream &is, Complex &c)
{
    bool    good = false;
    double    re = 0;
    double    im = 0;
    char    ch;


    if ( is >> ch && ch == COMPLEX_BRACKETS_BEGIN_CHAR ) {
        if ( 
             is >> re &&
             is >> ch &&
             ch == COMPLEX_BRACKETS_SEPARATOR_CHAR &&
             is >> im &&
             is >> ch &&
             ch == COMPLEX_BRACKETS_END_CHAR
           )
           good = true;
        else good = false;
    }
    else{ 
        is.putback(ch);
        if(is >> re){
            im = 0;
            good = true;
        }
        else good = false;
    }

    if( good ) {
       c.re_ = re; 
       c.im_ = im; 
    }
    else is.clear( ios::failbit );


    return    is;
}
