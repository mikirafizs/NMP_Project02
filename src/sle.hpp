#ifndef SLE_HPP
#define SLE_HPP
#include <lapacke.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

struct Condition{
    double x; //location of node
    int deriv; //0 for value of function, 1 for first derivative
    double value; // value of the equation (right side)
};

inline void build_system(std::vector <Condition> cond, std::vector <double>& a, std::vector <double>& b, std::size_t n){
    a.assign(n*n, 0.0);
    b.assign(n, 0.0);

    for(size_t k = 0; k < n; k++){
        for(size_t j = 0; j < n; j++){
            if(cond[k].deriv == 0){
                a[k*n+j] = pow(cond[k].x, j);
            }
            if(cond[k].deriv > 0){
                if (j == 0) {
                    a[k*n+j] = 0.0;
                } else {
                    a[k*n+j] = j * pow(cond[k].x, j-1);
                }
            }
        }
        b[k] = cond[k].value;
    }
}

inline void print_matrix(std::vector <double>& a){
    const size_t n = sqrt(a.size());
    for(size_t k = 0; k < n; k++){
        std::cout<<"[ ";
        for(size_t i = 0; i < n; i++){
            std::cout<< std::setw(6) << std::setprecision(3)<<a[k*n+i]<<"    ";
        }
        std::cout<<"]\n";
    }
}

inline double determinant_from_LU(std::vector <double>& a, std::vector <int32_t>& ipiv, std::size_t n){

    LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, &a[0], n, &ipiv[0]);
    double det = 1.0;
    int swaps = 0;
    
    for(size_t i = 0; i < n; i++){
        det *= a[i*n + i]; 

        if(ipiv[i] != (int32_t)(i + 1)) {
            swaps++;
        }
    }

    if(swaps % 2 != 0){
        det = -det;
    }
    
    return det;
}

inline void solve(std::vector <double>&a, std::vector <int>&ipiv, std::vector <double>& b, size_t n){
    LAPACKE_dgetrs(LAPACK_ROW_MAJOR, 'N', n, 1, &a[0], n, &ipiv[0], &b[0], 1);
}

#endif
