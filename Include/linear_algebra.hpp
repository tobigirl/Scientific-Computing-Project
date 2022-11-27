#include <iostream>
#include <fstream>
#include <string>

#include "sparse_matrix.hpp"

#ifndef linear_algebra
#define linear_algebra

//////////////////////////////////////////////////////////////
//Function Prototype
//////////////////////////////////////////////////////////////
Vector computeResidualVector(Sparse_matrix matrixA, Vector x, Vector b);
Vector jacobi_method(double w, double tol, int max_num_iterate, Sparse_matrix& matrixA, Vector& vectorb);

#endif