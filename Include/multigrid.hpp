#include <iostream>
#include <fstream>
#include <string>

#include "finite_difference.hpp"

#ifndef multigrid
#define multigrid

//////////////////////////////////////////////////////////////
//Function Prototype

Vector prolongateVector(Vector vectorC);
Vector restrictVector(Vector vectorF);
Vector vCycle(Sparse_matrix matrixA, Vector vectorF, Vector vectorU, int n, double w);
Vector wCycle(Sparse_matrix matrixA, Vector vectorF, Vector vectorU, int n, double w);
void multigrid_vCycle(Sparse_matrix matrixA, Vector vectorF, int n, double w, double tol);
void multigrid_wCycle(Sparse_matrix matrixA, Vector vectorF, int n, double w, double tol);


#endif