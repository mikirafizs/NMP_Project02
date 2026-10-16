#ifndef SLE.HPP
#define SLE.HPP
#include <lapacke.h>
#include <vector>
#include <cmath>
#include <iostream>

struct Condition{
    double x; //location of node
    int deriv; //0 for value of function, 1 for first derivative
    double value; // value of the equation (right side)
};

inline void build_system(std::vector <Condition> cond, std::vector <double>& a, std::vector <double>& b){
    const int n = cond.size();
    a.assign(n*n, 0.0);
    b.assign(n, 0.0);

    for(size_t k = 0; k < n; k++){
        for(size_t j = 0; j < n; j++){
            if(cond[k].deriv == 0){
                a[k*n+j] = pow(cond[k].x, j);
            }
            if(cond[k].deriv > 0){
                a[k*n+j] = j*pow(cond[k].x, j-1);
            }
        }
        b[k] = cond[k].value;
    }
}

inline void print_matrix(std::vector <double>& a){
    const size_t n = sqrt(a.size());
    for(size_t k = 0; k < n; k++){
        for(size_t i = 0; i < n; i++){
            
        }
    }
}

inline double determinant_from_LU(std::vector <double>& a, std::vector <double>& ipiv){}

inline double solve(std::vector <double>&a, std::vector <double>&ipiv, std::vector <double>& coef, size_t n){
    coef.assign(n, 0.0);
}

#endif


/*
std::vector<Condition> cond = {
    {x0, 0,  0.0},
    {x0, 1,  1.0},
    {x1, 0,  1.0},
    {x2, 0,  0.0},
    {x3, 0, -1.0},
    {x3, 1,  0.0},
};
*/