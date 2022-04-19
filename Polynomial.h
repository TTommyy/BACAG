//Tomasz Koczar
// Created by tomek on 28.03.2022.

#ifndef BACA_G_POLYNOMINAL
#define BACA_G_POLYNOMINAL

#include "Z3.h"

class Polynomial {
    /*Pola*/
    unsigned int deg; // stopien wielomianu
    Z3* coefficients; // wspolycziki

public:

    /*Konstruktory*/
    Polynomial();
    Polynomial(unsigned int n ,const Z3* tab);
    Polynomial(const Polynomial& p);
    ~Polynomial();
    /*Operatory*/
    Z3& operator[](unsigned int index)const;
    Polynomial& operator+=(const Polynomial& b);
    Polynomial& operator-=(const Polynomial& b);
    Polynomial& operator*=(const Polynomial& b);
    Polynomial& operator*=(const Z3& b);
    Polynomial& operator/=(const Z3& s);
    Polynomial& operator=(const Polynomial& b);

    /*Metody*/
    unsigned int degree()const;
    std::string toString(const std::string& xVar) const ;

    void reduce();// redukuje stopien jezeli przy najwyzszych wpsloczyniach stoja zera

    /*Operatory globalne*/
    friend Polynomial operator+(const Polynomial& a, const Polynomial& b );
    friend Polynomial operator-(const Polynomial& a,const  Polynomial& b );
    friend Polynomial operator*(const Polynomial& a,const  Polynomial& b );
    friend Polynomial operator*(const Polynomial& a, const Z3& b );
    friend Polynomial operator*(const Z3& b, const Polynomial& a );
    friend Polynomial operator/(const Polynomial& a,const Z3& b );
    friend void mod(Polynomial u, Polynomial v , Polynomial& q, Polynomial& r);
    friend std::ostream& operator<<(std::ostream& o,const  Polynomial& p);
    friend std::istream& operator>>(std::istream& i, Polynomial& p);


};

#endif
