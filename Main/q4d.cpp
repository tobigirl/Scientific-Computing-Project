#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "multigrid.hpp"


int main()
{
int n[5] = {128, 256, 512, 1024};
double w = 0.5;
double tol = pow(10,-7);
Vector vectorU;
    
    for (int i = 0; i < n[i]; i++)
    {
        //For each value of n.

        Sparse_matrix matrixA;
        matrixA = CreateMatrixA(n[i]); 

        Vector vectorF;
        vectorF = CreateVectorF(n[i]);

        multigrid_vCycle(matrixA, vectorF, n[i], w, tol);

        multigrid_wCycle(matrixA, vectorF, n[i], w, tol);
    }

return 0; 
}