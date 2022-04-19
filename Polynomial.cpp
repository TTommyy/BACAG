//Tomasz Koczar

#include <iostream>
#include "Polynomial.h"
#include "Z3.h"

/*********************Konstrukory*******************/

/*Tworzy wilomian stopnia zero rowny zero*/
Polynomial::Polynomial(): deg(0) {
    coefficients = new Z3[1];
    coefficients[0] = Z3(0);
}

/*Tworzy wielomian z podnaymi wspolczynikami*/
Polynomial::Polynomial(const unsigned int n,const Z3 *tab): deg(n) {
    coefficients = new Z3[deg + 1];
    for(unsigned int i = 0; i<=deg ; i++)
        coefficients[i] = tab[i];
    reduce();
}

/*Konstruktor kopiujacy*/
Polynomial::Polynomial(const Polynomial &p) : deg(p.deg){
    coefficients = new Z3[deg + 1];
    for(unsigned int i = 0; i<=deg ; i++)
        coefficients[i] = p.coefficients[i];
}

Polynomial::~Polynomial() { delete[] coefficients; }
/******************************* Operatory *********************************/

/*Zwraca indeks, przy zerowym wyraz wolny.
 * Gdy indeks nie poprawny zrwaca indeks zerowy*/

Z3& Polynomial::operator[](const unsigned int index)const{
    if(index > deg || index < 0){
        std::cout << "Niepoprawny indeks wielomianu\n";
        return coefficients[0];
    }
    return coefficients[index];
}


/*Dodaje wielomian b do wielomianu*/
Polynomial &Polynomial::operator+=(const Polynomial &b) {
    if(b.deg > deg){
        Z3* nCoeff = new Z3[b.deg+1];
        for(unsigned int i = 0; i <=b.deg; i++)
            nCoeff[i] = b.coefficients[i];

        for(unsigned int i = 0; i <= deg; i++)
            nCoeff[i] += coefficients[i];

        delete[] coefficients;
        coefficients = nCoeff;
        deg = b.deg;
        reduce();
        return *this;

    }
    for(unsigned int i = 0; i<=b.deg; i++)
        coefficients[i]+=b.coefficients[i];
    reduce();
    return *this;
}

/*Odejmuje wielomian b od wielomianu*/
Polynomial &Polynomial::operator-=(const Polynomial &b) {
    if(b.deg > deg){
        Z3* nCoeff = new Z3[b.deg+1];

        for(unsigned int i = deg+1; i <=b.deg; i++)
            nCoeff[i] = Z3(0);

        for(unsigned int i = 0; i <=deg; i++)
            nCoeff[i] = coefficients[i];

        for(unsigned int i = 0; i <= b.deg; i++)
            nCoeff[i] -= b.coefficients[i];

        delete[] coefficients;

        coefficients = nCoeff;
        deg = b.deg;
        reduce();
        return *this;

    }
    for(unsigned int i = 0; i<=b.deg; i++)
        coefficients[i]-=b.coefficients[i];
    reduce();
    return *this;
}

/*Mnozy wielomian przez wielomian*/
Polynomial &Polynomial::operator*=(const Polynomial &b) {
    unsigned int nDegree = deg + b.deg;
    Z3* nCoeff =  new Z3[nDegree + 1];
    for(unsigned int i = 0; i <= nDegree; i++){
        nCoeff[i] = Z3(0);
    }

    for(unsigned int i = 0; i <= deg; i++){
        for(unsigned int j = 0; j<=b.deg; j++)
            nCoeff[i+j] += coefficients[i]*b.coefficients[j];
    }

    delete[] coefficients;
    coefficients = nCoeff;
    deg = nDegree;
    reduce();
    return *this;
}

/*Mnozy wielomian przez liczbe*/
Polynomial &Polynomial::operator*=(const Z3 &b) {
    for(unsigned int i = 0; i <= deg; i++)
        coefficients[i] *=b;
    reduce();
    return *this;
}

/*Dzieli wielomian przez liczbe*/
Polynomial &Polynomial::operator/=(const Z3 &s) {
    if( (short)s ==0 ){
        std::cout << "Dzielenie przez zero\n";
        return *this;
    }
    for(unsigned int i = 0; i <= deg; i++)
        coefficients[i] /=s;
    //reduce(); tutaj nie trzba
    return *this;
}

Polynomial &Polynomial::operator=(const Polynomial &b){
    if(this!=&b) {
        delete[] coefficients;
        deg = b.deg;
        coefficients = new Z3[deg + 1];
        for (unsigned int i = 0; i <= degree(); i++) {
            coefficients[i] = b.coefficients[i];
        }
    }
    return *this;
}


/*Zwaraca stopien wielomianu*/
unsigned int Polynomial::degree()const{
    return deg;
}

/*Zwraca wielomian jako lancuch znakowy*/
std::string Polynomial::toString(const std::string& xVar)const {
    std::string string;
    unsigned int n=0;
    if(deg==0 && (short)coefficients[0]==0)
        string += std::to_string((short)coefficients[n]);
    else if((short)coefficients[0]!=0)
        string += std::to_string((short)coefficients[n]);
    n++;
    while( n<=deg ){
        if((short )coefficients[n]!=0) {
            if( !string.empty() )string += "+";
            string += std::to_string((short) coefficients[n]);
            string += "*" + xVar + "^";
            string += std::to_string(n);

        }
        n++;
    }
    return string;
}

/*Usuwa zera z konca tablicy wspolczynikow
 za wyjatkiem zera w wyrazie wolnym*/
void Polynomial::reduce() {
    while((short)coefficients[deg]==0 && deg!=0){
        deg--;
    }
}


/********* Operatory globanle*************/

/*Dodaje dwa wielomiany*/
Polynomial operator+(const Polynomial &a,const Polynomial &b) {

    if(b.deg >= a.deg){
        Z3* nCoeff = new Z3[b.deg+1];
        for(unsigned int i = 0; i <=b.deg; i++)
            nCoeff[i] = b.coefficients[i];

        for(unsigned int i = 0; i <= a.deg; i++)
            nCoeff[i] += a.coefficients[i];


        Polynomial p(b.deg,nCoeff);
        delete[] nCoeff;
        p.reduce();
        return  Polynomial(p);

    }

    Z3* nCoeff = new Z3[a.deg+1];

    for(unsigned int i = 0; i <=a.deg; i++)
        nCoeff[i] = a.coefficients[i];

    for(unsigned int i = 0; i <= b.deg; i++)
        nCoeff[i] += b.coefficients[i];
    Polynomial p(a.deg,nCoeff);
    delete[] nCoeff;
    p.reduce();
    return  Polynomial(p);

}

/*Odejmuje b od a*/
Polynomial operator-(const Polynomial &a, const Polynomial &b) {
    if(b.deg > a.deg){
        Z3* nCoeff = new Z3[b.deg+1];
        for(unsigned int i = a.deg+1; i <=b.deg; i++)
            nCoeff[i] = Z3(0);

        for(unsigned int i = 0; i <=a.deg; i++)
            nCoeff[i] = a.coefficients[i];

        for(unsigned int i = 0; i <= b.deg; i++)
            nCoeff[i] -= b.coefficients[i];


        Polynomial p(b.deg,nCoeff);
        delete[] nCoeff;
        p.reduce();
        return  Polynomial(p);

    }

    Z3* nCoeff = new Z3[a.deg+1];

    for(unsigned int i = 0; i <=a.deg; i++)
        nCoeff[i] = a.coefficients[i];

    for(unsigned int i = 0; i <= b.deg; i++)
        nCoeff[i] -= b.coefficients[i];
    Polynomial p(a.deg,nCoeff);
    delete[] nCoeff;
    p.reduce();
    return  Polynomial(p);
}
/*Mnozy dwa wielomiany*/
Polynomial operator*(const Polynomial &a, const Polynomial &b) {
    unsigned int nDegree = a.deg + b.deg;
    Z3* nCoeff =  new Z3[nDegree + 1];
    for(unsigned int i = 0; i <= nDegree; i++){
        nCoeff[i] = Z3(0);
    }

    for(unsigned int i = 0; i <= a.deg; i++){
        for(unsigned int j = 0; j<=b.deg; j++)
            nCoeff[i+j] += a.coefficients[i]*b.coefficients[j];
    }


    Polynomial p(nDegree,nCoeff);
    delete[] nCoeff;
    p.reduce();
    return  Polynomial(p);
}

Polynomial operator*(const Polynomial &a, const Z3& b) {
    Z3* nCoeff = new Z3[a.deg+1];
    for(unsigned int i = 0; i<=a.deg ; i++)
        nCoeff[i] = a.coefficients[i]* Z3(b);

    Polynomial p(a.deg,nCoeff);
    delete[] nCoeff;
    p.reduce();
    return  Polynomial(p);
}

Polynomial operator*( const Z3& b, const Polynomial &a) {
    Z3* nCoeff = new Z3[a.deg+1];
    for(unsigned int i = 0; i<=a.deg ; i++)
        nCoeff[i] = a.coefficients[i]* Z3(b);

    Polynomial p(a.deg,nCoeff);
    delete[] nCoeff;
    p.reduce();
    return  Polynomial(p);
}

Polynomial operator/(const Polynomial &a, const Z3& b) {

    if((short)b==0){
        std::cout << "Dzielenie przez zero\n";
        return Polynomial(a.deg, a.coefficients);
    }

    Z3* nCoeff = new Z3[a.deg+1];
    for(unsigned int i = 0; i<=a.deg ; i++)
        nCoeff[i] = a.coefficients[i]* Z3(b);

    Polynomial p(a.deg,nCoeff);
    delete[] nCoeff;
    p.reduce();
    return  Polynomial(p);
}
//u = q*v + r
/* u jest dzielna,
 * v dzielnikem,
 * q wynikiem,
 * r reszta*/

/* Standardowy algorytm dzielenia wielomianow*/
void mod(Polynomial u, Polynomial v, Polynomial &q, Polynomial &r) {
    if(u.deg>=v.deg && v.deg!=0){
        Polynomial temp = u;//wielomian do pracy zostanie w nim reszta
        unsigned int qDeg = u.deg - v.deg;//stopien wyniku
        Z3*nCoeff = new Z3[qDeg+1];//wspolczynki wynikowaego
        Z3 number;//do obliczen


        /*Dzielenie*/
        for(unsigned int i= u.deg; i>v.deg; i--) {
            nCoeff[qDeg] = number = temp.coefficients[i] / v.coefficients[v.deg];//wspolczynik najwyszego
            qDeg--; // znmiejszamy najwsszy
            for (unsigned int j = i, k = v.deg; k > 0;j--,k--) {// monzemy co zostalo jak w pisemnym
                temp.coefficients[j] -= number * v.coefficients[k];
            }
            temp.coefficients[i - v.deg] -= number * v.coefficients[0];
        }
            nCoeff[0] = number = temp.coefficients[v.deg]/v.coefficients[v.deg];
            for(unsigned int j=v.deg; j>0; --j){//odejmojemy to co jest jak przy dzielniu wielomainow pisemnie
                temp.coefficients[j] -=number*v.coefficients[j];
            }
            temp.coefficients[0] -= number* v.coefficients[0];

            q= Polynomial(u.deg - v.deg,nCoeff);
            temp.reduce();
            r=temp;
            delete[] nCoeff;
        } else if( u.deg < v.deg ){//tu sie nie da
        q = Polynomial();
        r=u;
        return;
    } else{//poszczegolne przypadki gdy v.deg = 0;
        if( (short)v[0] == 0 ){
            std::cout << "Dzielenie przez zero\n";
            return;
        }
        if((short)v[0] == 1){
            q=u;
            r=Polynomial();
            return;
        }
        if((short)v[0] == 2){
            Z3 n(2);
            q=u;
            r=Polynomial();
            for(unsigned int i=q.deg; i>0; i--){
                q.coefficients[i] /=n;
            }
            q.coefficients[0] /=n;
        }
    }

    }

std::ostream &operator<<(std::ostream &o, Polynomial const &p) {
    o << "{" << p.coefficients[0];
    for(unsigned i = 1; i<=p.deg; i++ )
            o << "," << p.coefficients[i];
    o << "}";
    return o;
}

std::istream &operator>>(std::istream &i, Polynomial &p) {
    std::string s,rest;
    getline(i,rest,'{');
    getline(i,s,'}');

    delete[] p.coefficients;
    p.deg = (s.length()/2) ;
    unsigned int coeff = 0;
    p.coefficients = new Z3[p.deg+1];

    for( unsigned long i = 0; i<s.length(); i=i+2 ){
        p.coefficients[coeff] = s[i];
        coeff++;
    }

    p.reduce();
    return i;
}










