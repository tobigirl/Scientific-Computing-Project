#include <iostream>
#include <fstream>
#include <cmath>

#include "linear_algebra.hpp"

int main()
{
     double w = 0.5;
     double tol = pow(10,-10);
     int max_num_iterate = 10000;
     
    //Read in the matrix A from matrix.dat
    Sparse_matrix matrixA = ReadMatrixFromFile("matrix.dat");

    //Read in d the vector x from vector.dat,
    Vector vectorx = ReadVector("vector.dat");

    //compute b = 𝐴x
    Vector b = multiplyAx (matrixA, vectorx);  

    //Use the Jacobi function to find an approximation x̂ to x.
    Vector x = jacobi_method(w, tol, max_num_iterate, matrixA, b);
    std::cout << "The approximation x̂ to x is ";
    PrintVector(x);
   

    //To find the Error, ||x - x||2
        double error;
        double a = -1;

        //The substraction of x and approx x using the linear combination function but first I set "a=-1" to negate the approximate value.
        Vector x_x = linearcombination(vectorx, x, a);
        error = l2_norm(x_x);

        std::cout << "The error is " << error<< std::endl;

return 0;
}