#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "linear_algebra.hpp"


//////////////////////////////////////////////////////////////////////////////////////
Vector CreateVectorF(int n)
//Function to create the RHS vector F.
{  
    Vector vectorF;
    vectorF.length = pow(n+1, 2);
    vectorF.vector_entries = new double [vectorF.length];

    for (int i = 0; i <= n; i++) 
    {
       for (int j = 0; j <= n; j++)
       {
            if ( i!=0 || j!=0 || i!=n || j!=n)
                {
                    vectorF.vector_entries[i*(n+1) + j] = 0;
                } 
            else
                {
                    vectorF.vector_entries[i*(n+1) + j] = 1;
                }   
       }
    }
return vectorF;                                     //Value Output
}


//////////////////////////////////////////////////////////////////////////////////////
Sparse_matrix CreateMatrixA(int n)
//Function to create the matrix A in diagonal format.
{
    Sparse_matrix matrixA;
    matrixA.n = pow(n+1, 2);
    matrixA.no_diagonals = 5;
    matrixA.diagonals_list = new int[5];
    matrixA.diagonals_list[0] = -n-1;
    matrixA.diagonals_list[1] = -1;
    matrixA.diagonals_list[2] = 0;
    matrixA.diagonals_list[3] = -1;
    matrixA.diagonals_list[4] = -n-1;
    
	matrixA.matrix_entries = new double* [matrixA.n];

    //Indicate the boundary conditions
    for (int i = 1; i <= n; i++) 
    {
       for (int j = 1; j <= n; j++)
       {
            if(i!=0 || j!=0 || i!=n || j!=n)
            {
                int m = i*(n+1) + j;
                matrixA.matrix_entries[0][m] = 0;
                matrixA.matrix_entries[1][m] = 0;
                matrixA.matrix_entries[2][m] = 0;
                matrixA.matrix_entries[3][m] = 0;
                matrixA.matrix_entries[4][m] = 0;
            }
            else
            {
                int m = i*(n+1) + j;
                matrixA.matrix_entries[0][m] = -pow(n,2);
                matrixA.matrix_entries[1][m] = -pow(n,2);
                matrixA.matrix_entries[2][m] = -4*pow(n,2);
                matrixA.matrix_entries[3][m] = -pow(n,2);
                matrixA.matrix_entries[4][m] = -pow(n,2);
            }
       }
    }
return matrixA;
}


double findMaximumNumberinVector(Vector vector)
{
    double max_number = 0;
    for(int i =0; i<vector.length; i++)
    {
        if(max_number < vector.vector_entries[i])
        {
            max_number = vector.vector_entries[i];
        }
    }
return max_number;                                     //Value Output
}
