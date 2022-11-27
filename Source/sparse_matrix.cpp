#include <iostream>
#include <fstream>
#include <cmath>

#include "sparse_matrix.hpp"


//////////////////////////////////////////////////////////////
//Question 1a

Vector multiplyAx (Sparse_matrix matrixA, Vector vectorx)
//Function to multiply matrix A and vector x
{	
	double* Ax = new double [matrixA.n];									//Allocating memory address to Ax.

	for (int j = 0; j < matrixA.n; j++)
	{		
		for (int k = 0; k < matrixA.no_diagonals; k++)
		{
			Ax[j] += matrixA.matrix_entries[k][j] * vectorx.vector_entries[j+matrixA.diagonals_list[k]];				//product Ax.
		}
	}
	
	Vector vectorAx;
	vectorAx.vector_entries = Ax;
	vectorAx.length = matrixA.n;
return vectorAx;																//Value Output
}


double* ComputeDInverse (Sparse_matrix matrixA)
//Function to find the inverse of the matrix diagonal
{	
//To extract the Matrix Diagonal
double* d = new double[matrixA.n];
for (int k = 0; k < matrixA.no_diagonals; k++) 
	{
        for (int j = 0; j < matrixA.n; j++) 
		{
            // Condition for diagonal
            if (0 == matrixA.diagonals_list[k])
            d[j] = matrixA.matrix_entries[k][j];
        }
	}

//To find the Inverse of the diagonal.
double* dInverse = new double[matrixA.n];
for (int j = 0; j < matrixA.n; j++) 
		{
            
			dInverse[j] = 1.0 / d[j];
        }
delete[] d;
return dInverse;								//Value Output
}


//////////////////////////////////////////////////////////////
Sparse_matrix ReadMatrixFromFile(std::string fileName)
//Read a matrix from an ASCII file
{
	std::ifstream read_file;
	read_file.open(fileName); // Open file
	assert(read_file.is_open()); 

	std::string line;
	Sparse_matrix matrix;

	//Read no of rows
	std::getline(read_file, line); //Ignore String
	std::getline(read_file, line);
	matrix.n = atoi(line.c_str());

	//Read no diagonals
	std::getline(read_file, line); //Ignore String
	std::getline(read_file, line);
	matrix.no_diagonals = atoi(line.c_str());

	std::getline(read_file, line); //Ignore String
	//Allocate diagonals_list and matrix_entries
	matrix.diagonals_list = new int[matrix.no_diagonals];
	matrix.matrix_entries = new double*[matrix.no_diagonals];
	for (int k=0;k<matrix.no_diagonals;k++)
	{
		//Read diagonal list at the same time
		std::getline(read_file, line);
		matrix.diagonals_list[k] = atoi(line.c_str());
		matrix.matrix_entries[k] = new double[matrix.n];
	}

	// Finally read the matrix entries
	std::getline(read_file, line); //Ignore String
	for (int k=0;k<matrix.no_diagonals;k++)
	{
		for (int j=0;j<matrix.n;j++)
		{
			std::getline(read_file, line);
			matrix.matrix_entries[k][j] = atoi(line.c_str());
		}
	}
	
	// Finally close file
	read_file.close();

	return matrix;											//Value Output
}


//////////////////////////////////////////////////////////////
void PrintSparseMatrix(Sparse_matrix matrix)
//Function to print a sparse matrix to screen 
// useful for debugging 
{
	//Output scalar quantities
	std::cout << "no_rows = " << matrix.n << std::endl;
	std::cout << "no_diagonals = " << matrix.no_diagonals << std::endl;
	std::cout << "diagonals_list = " << std::endl;
	
	//Finally output each of the diagonals
	for (int k=0;k<matrix.no_diagonals;k++)
	{
		std::cout << matrix.diagonals_list[k] << ":" << std::endl;
		std::cout << "   ";
		for (int j=0;j<matrix.n;j++)
		{
			std::cout << matrix.matrix_entries[k][j] << " ";
		}
		std::cout << std::endl;
	}
}


//////////////////////////////////////////////////////////////
void DeleteSparseMatrix(Sparse_matrix& matrix)
//Deallocate storage of sparse matrix and set other entries to 0
//for completeness
{

	delete[] matrix.diagonals_list;
	for (int k=0;k<matrix.no_diagonals;k++)
	{
		delete[] matrix.matrix_entries[k];
	}
	delete[] matrix.matrix_entries;

	matrix.n = 0;
	matrix.no_diagonals = 0;

}
