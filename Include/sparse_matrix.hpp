#include <iostream>
#include <fstream>

#include "vectors.hpp"


#ifndef sparse_matrix
#define sparse_matrix


//////////////////////////////////////////////////////////////
struct Sparse_matrix
//Structure to store a sparse matrix in diagonal form.
//The matrix is assumed to be square
{
	int n; //Number of rows in the matrix.
	int no_diagonals; //Number of non-zero diagonals
	int* diagonals_list; //A list of the non-zeros diagonals, can appear in any order
	double** matrix_entries; //Columns of this matrix are the diagonals of the sparse matrix
};

//////////////////////////////////////////////////////////////
//Function Prototypes
//////////////////////////////////////////////////////////////
Sparse_matrix ReadMatrixFromFile(std::string fileName);
void DeleteSparseMatrix(Sparse_matrix& matrix);
void PrintSparseMatrix(Sparse_matrix matrix);
Vector multiplyAx (Sparse_matrix matrixA, Vector vectorx);
double* ComputeDInverse (Sparse_matrix matrixA);

#endif