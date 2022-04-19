//Tomasz Koczar

#ifndef BACA_G_Z3
#define BACA_G_Z3

#include <iostream>

class Z3{
    /*Pola*/

    enum VALUE{ZERO=0,ONE=1,TWO=2};
    VALUE value;

    /*Metody*/
public:
    /*Konstruktory*/
    Z3();
    explicit Z3(short n);
    Z3( Z3 const & a);

    /*Operatory*/
    explicit operator short ()const;
    Z3& operator +=(const Z3& b);
    Z3& operator -=(const Z3& b);
    Z3& operator *=(const Z3& b);
    Z3& operator /=(const Z3& b);
    Z3& operator =(const Z3& b);
    Z3& operator =(short b);// nie obowiazkowy

    /*Funkcje zaprzyjaznone*/
    friend VALUE evaluate(int n);
    friend short evaluate(VALUE n);

    /*Operatory globalne*/
    friend Z3 operator+(const Z3& a,const  Z3& b);
    friend Z3 operator-(const Z3& a, const Z3& b);
    friend Z3 operator*(const Z3& a, const Z3& b);
    friend Z3 operator/(const Z3& a, const Z3& b);
    friend std::ostream& operator<<(std::ostream& o ,const Z3& a);

};

#endif


