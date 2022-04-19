#include "Z3.h"
#include "Polynomial.h"
#include <iostream>
#include <sstream>
using namespace std;
#define LOGGER(x) std::cout << (#x) << "=" << (x) << std::endl;

int main(){
    Z3 x(2), y(4);

    LOGGER(x);
    LOGGER(y);
    LOGGER(x+y);
    LOGGER(x-y);
    LOGGER(x*y);
    LOGGER(x/y);

    std::istringstream in("litery 0001122233{0,2,1}");
    Polynomial w;
    in >> w;
    cout  << w << endl;
    cout << w.toString("x") << endl;

    const int N1 = 24;
    const int N2 = 3;
    Z3 d1[N1+1] = {Z3(1),Z3(5),Z3(15),Z3(0),Z3(1),Z3(1),Z3(1),Z3(20),Z3(1),Z3(0),Z3(0),Z3(1),Z3(1),Z3(20),Z3(1)};
    Z3 d2[N2+1] = {Z3(0),Z3(5),Z3(7),Z3(1)};
    d1[N1] = 1;
    Polynomial u(N1,d1), v(N2,d2);
    LOGGER(u);
    LOGGER(v);
    LOGGER(u+v);
    LOGGER(u-=v);
    LOGGER(u*v);
    LOGGER(u*v-v*u);
    LOGGER((u*v).toString("x"));

    Polynomial q, r;
    mod(u,v,q,r);
    LOGGER(q.toString("q"));
    LOGGER(r.toString("r"));

    return 0;
}