#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "finite_difference.hpp"


int main()
{

double n[5] = {16, 32, 64, 128, 256};
double w = 0.5;
double tol = pow(10,-10);
int max_num_iterate = 10000;
Vector vectorU;
    
    for (int i = 0; i < n[i]; i++)
    {
        //For each value of n.

        Sparse_matrix matrixA;
        matrixA = CreateMatrixA(n[i]); 

        Vector vectorF;
        vectorF = CreateVectorF(n[i]);
            
        vectorU = jacobi_method(w, tol, max_num_iterate, matrixA,  vectorF);
        std::cout << "U = ";
        PrintVector(vectorU);

       // Find max value of vectorU
        double max_vectorU = findMaximumNumberinVector(vectorU);
        std::cout << "The maximum value of U is ";
        std::cout << max_vectorU << std::endl;
    }
    

//std::cout << "A = " << std::endl;
//PrintSparseMatrix(matrixA);
//std::cout << std::endl;

//std::cout << "A = " << std::endl;
//PrintVector(vectorF);
//std::cout << std::endl;


return 0; 

}