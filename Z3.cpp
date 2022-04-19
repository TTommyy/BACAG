//Tomasz Koczar

#include "Z3.h"
#include <iostream>

/*Funkcja pomoncicza*/

Z3::VALUE evaluate(const int x){
    int n = x;
    n = n%3;
    if(n<0){
        n+=3;
    }

    if(n == 0)
        return Z3::VALUE::ZERO;
    if(n == 1)
        return Z3::VALUE::ONE;

    return Z3::VALUE::TWO;
}

short evaluate(Z3::VALUE n) {
    if(n == Z3::ZERO )
        return 0;
    if(n == Z3::ONE )
        return 1;
    return 2;
}


/*Konstruktory*/

//Konstruktor domyslny
Z3::Z3() :  value(VALUE::ZERO) {};
//Konstruktor jednoargumentowy
Z3::Z3(short n) { value = evaluate(n); }
//Konstruktor kopiujacy
Z3::Z3(Z3 const &a): value(a.value){};


/*Operatory*/

Z3::operator short()const { return evaluate(value); }

Z3 &Z3::operator+=(const Z3& b) {
    value = evaluate(evaluate(value) + evaluate(b.value));
    return *this;
}

Z3 &Z3::operator-=(const Z3& b) {
    value = evaluate(evaluate(value) - evaluate(b.value));
    return *this;
}
Z3 &Z3::operator*=(const Z3& b) {
    value = evaluate(evaluate(value) * evaluate(b.value));
    return *this;
}
Z3 &Z3::operator/=(const Z3& b) {
    if(evaluate(b.value)==0){
        std::cout << "Dzielenie przez zero\n";
        return *this;
    }
    value = evaluate(evaluate(value) * evaluate(b.value));
    return *this;
}

Z3 &Z3::operator=(const Z3 &b) {
    value = b.value;
    return *this;
}

Z3 &Z3:: operator =(const short b){
    value = evaluate(b);
    return *this;
}


/*Operatory globane*/

Z3 operator+(const Z3& a, const Z3& b){
    return Z3(evaluate((short)a+(short)b));
}
Z3 operator-(const Z3& a, const Z3& b){
    return Z3(evaluate((short)a-(short)b));
}
Z3 operator*(const Z3& a, const Z3& b){
    return Z3(evaluate((short)a*(short)b));
}
Z3 operator/(const Z3& a, const Z3& b){
    if(evaluate(b.value)==0){
        std::cout << "Dzielenie przez zero\n";
        return Z3((short)a);
    }
    return Z3( evaluate((short)a * (short)b) );
}

std::ostream &operator<<(std::ostream& o, const Z3 &a) {
    o<<evaluate(a.value);
    return o;
}









