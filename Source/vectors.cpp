#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "vectors.hpp"


//////////////////////////////////////////////////////////////
void DeleteVector(Vector& vectorx)
//Deallocate storage of vector - for completeness
{
	for (int k = 0; k < vectorx.length; k++)
	{
		delete[] vectorx.vector_entries;                  //delete storage and sets entries to O;
	}
	delete[] vectorx.vector_entries;
	vectorx.length = 0;
}


//////////////////////////////////////////////////////////////
void PrintVector(Vector& vectorx)
//Function to print a vector to screen - useful for debugging 
{
	for (int k = 0; k < vectorx.length; k++)
	{
		std::cout << vectorx.vector_entries[k] << std::endl;
	}
}


//////////////////////////////////////////////////////////////
Vector ReadVector(std::string fileName)
// This function reads a vector in from a file
{	
    // Open the file
	std::ifstream read_file;
    read_file.open(fileName);                               // Open file
	assert(read_file.is_open());                            //Check that the file is open.

    std::string line;
	Vector vectorx;

    //Read lenght of vector
	std::getline(read_file, line);                          //Ignore String
	std::getline(read_file, line);
	vectorx.length = atoi(line.c_str());

	//Allocate vector_entries
    vectorx.vector_entries = new double[vectorx.length];

	// Finally read the vector entries
    std::string line_as_string;                             //Ignore String
	std::getline(read_file,line_as_string);
	for (int k = 0; k < vectorx.length; k++)
	{
		//read_file >> vectorx[k];
		std::getline(read_file, line);
		vectorx.vector_entries[k] = atoi(line.c_str());
	}
	read_file.close();
	return vectorx;										//Value Output
}


//////////////////////////////////////////////////////////////
Vector createZeroVector(Vector vectorb) 
//Function to create a zero vector
{
Vector vectorx;
vectorx.length = vectorb.length;
vectorx.vector_entries = new double[vectorx.length];									
for (int i = 0; i < vectorx.length; i++)
    {
        vectorx.vector_entries[i] = 0;
    }	
return vectorx; 								//Value Output
}


//////////////////////////////////////////////////////////////
Vector linearcombination(Vector& u, Vector& w, double a)
//Function to compute the linear combination of a scalar and two vectors 
{
	Vector lc;													//Allocating memory address to lc.
	lc.length = u.length;
	lc.vector_entries = new double[lc.length];	

	for (int k = 0; k < lc.length; k++)
	{
			lc.vector_entries[k] = u.vector_entries[k] + (a * w.vector_entries[k]);		//Linear Combination.
	}
	return lc; 															//Value Output
}


//////////////////////////////////////////////////////////////
double l2_norm(Vector& vectorx)
//Function to compute the l2-norm of the vector 
{
	double l2_norm = 0.0;
	for (int x = 0; x < vectorx.length; x++) // Alternative for loop .
		{
			 l2_norm += pow (x ,2); 
		}
	l2_norm = sqrt ( l2_norm );

	return l2_norm;															//Value Output
}