#include "sle.hpp"
#include <fstream>

//From excercise data
const size_t n = 6;
double x0 = 0;
double x1 = 1;
double x2 = 2;
double x3 = 3;
std::vector<Condition> cond = {
    {x0, 0,  0.0},
    {x0, 1,  1.0},
    {x1, 0,  1.0},
    {x2, 0,  0.0},
    {x3, 0, -1.0},
    {x3, 1,  0.0},
};

int main(){
    std::vector <double> A(n*n, 0.0);
    std::vector <double> b(n, 0.0);
    std::vector <int32_t> ipiv(n, 0);

    double determinant;

    build_system(cond, A, b, n);
    print_matrix(A);
    determinant = determinant_from_LU(A, ipiv, n);
    
    std::cout<<"\nDeterminant of matrix A: "<<determinant<<"\n";
    
    solve(A, ipiv, b, n);

    std::ofstream coefficients;
    coefficients.open("../data/coefficients.csv");
    if(!coefficients.is_open()){
        std::cerr<<"Cannot open file.\n";
        return -1;
    }
    for(size_t k = 0; k < n; k++){
        coefficients << "a" << k << ": " << b[k] << "\n";
    }
    coefficients.close();
    return 0;
}