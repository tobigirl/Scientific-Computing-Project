#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef vectors
#define vectors


//////////////////////////////////////////////////////////////
struct Vector
//Structure to store my vector.
{
	int length;                                         //Vector lenght.
	double* vector_entries;                            //The values of the vector.
};


//////////////////////////////////////////////////////////////
//Function Prototypes
//////////////////////////////////////////////////////////////
void DeleteVector(Vector& vectorx);
void PrintVector(Vector& vectorx);
Vector ReadVector(std::string fileName);
Vector createZeroVector(Vector vectorb);
Vector linearcombination(Vector& u, Vector& w, double a);
double l2_norm(Vector& vec);

#endif