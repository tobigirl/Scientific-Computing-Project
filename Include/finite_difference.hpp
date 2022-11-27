#include <iostream>
#include <fstream>

#include "linear_algebra.cpp"

#ifndef finite_diffference
#define finite_difference

//////////////////////////////////////////////////////////////
//Function Prototypes
//////////////////////////////////////////////////////////////

Vector CreateVectorF(int n);

Sparse_matrix CreateMatrixA(int n);

double findMaximumNumberinVector(Vector vectorx);

#endif