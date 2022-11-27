#include <iostream>

#include "sparse_matrix.hpp"
#include "vectors.hpp"


int main()
{
        //Read the matrix A in a file.
        Sparse_matrix matrixA = ReadMatrixFromFile("matrix1a.dat");     

        //Define vector x.
        Vector vectorx;
        double vectorarray [] = {6, 8, 2, 5};
        vectorx.vector_entries = vectorarray;                            
        
        //Product Ax. 
        Vector Ax = multiplyAx (matrixA, vectorx);                     
    
        //Output Product Ax.
        std::cout << "Ax = " << std::endl;
        PrintVector(Ax);   


       
        //void PrintSparseMatrix(sparse_matrix matrix);               //To print out the sparse matrix - Used for testing
        std::cout << "A = " << std::endl;
	    PrintSparseMatrix(matrixA);
	    std::cout << std::endl;
   
        /*
        void PrintVector(int l, double* vec);                       //To print out the vector - Used for testing
        std::cout << "x = " << std::endl;
	PrintVector(l, vectorx);
        std::cout << std::endl;
        */ 

                                
}
