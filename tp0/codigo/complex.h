#ifndef COMPLEX_INCLUDED_H
#define COMPLEX_INCLUDED_H

#define COMPLEX_BRACKETS_BEGIN_CHAR '('
#define COMPLEX_BRACKETS_END_CHAR ')'
#define COMPLEX_BRACKETS_SEPARATOR_CHAR ','

using namespace std;

class Complex
{
 private:
    double re_;
    double im_;
		
 public:
    Complex();
	Complex(const Complex &);
	Complex(double,double);
	Complex(double);
	~Complex();
		
	Complex const &operator=(const Complex &);
	Complex const &operator=(double);
	Complex const &operator+=(const Complex &);
	Complex const &operator+=(double);
	Complex const &operator-=(const Complex &);
	Complex const &operator-=(double);
	Complex const &operator*=(const Complex &);
	Complex const &operator*=(double);
	Complex const &operator/=(const Complex &);
	Complex const &operator/=(double);
		
	void setRe(double);
	void setIm(double);
	void setComplex(double,double);
	Complex const &conjugate();
		
	double getRe() const;
	double getIm() const;
	double computeAbs() const;
	double computeAbs2() const;
	double computeAngle() const;
	Complex const computeConjugated() const;
	bool isZero() const;
		
	friend Complex const operator+(const Complex &, const Complex &);
	friend Complex const operator+(const Complex &, double);
	friend Complex const operator+(double, const Complex &);
	friend Complex const operator-(const Complex &, const Complex &);
	friend Complex const operator-(const Complex &, double);
	friend Complex const operator-(double, const Complex &);
	friend Complex const operator*(const Complex &, const Complex &);
	friend Complex const operator*(const Complex &, double);
	friend Complex const operator*(double, const Complex &);
	friend Complex const operator/(const Complex &, const Complex &);
	friend Complex const operator/(const Complex &, double);
	friend Complex const operator/(double, const Complex &);
	friend bool operator==(const Complex &,const Complex &);
	friend bool operator==(const Complex &,double);
	friend bool operator==(double,const Complex &);
	friend bool operator!=(const Complex &,const Complex &);
	friend bool operator!=(const Complex &,double);
	friend bool operator!=(double,const Complex &);
	friend ostream &operator<<(ostream &, const Complex &);
	friend istream &operator>>(istream &, Complex &);
};
#endif // COMPLEX_INCLUDED_H
