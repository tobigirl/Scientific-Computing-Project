#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "linear_algebra.hpp"


//Function to Calculate the residual vector
Vector computeResidualVector(Sparse_matrix matrixA, Vector x, Vector b)
{
    //First, I find the RHS product of matrix and vector.
    Vector Ax = multiplyAx (matrixA, x);	

    //Solve the residual, r = b - Ax
    Vector r;
    r.length = b.length;
    r.vector_entries = new double[r.length];
    for (int i = 0; i < r.length; i++)
        {
            r.vector_entries[i] = b.vector_entries[i] - Ax.vector_entries[i];
        }
return r;                                       //Value Output
}


//Function to implement the Damped Jacobi method
Vector jacobi_method(double w, double tol, int max_num_iterate, Sparse_matrix& matrixA, Vector& vectorb)
{

//Set initial guess for the solution x0 to be a zero vector	
Vector vectorx = createZeroVector(vectorb);

//Use the residual function to solve r0 = b - Ax0
Vector r0 = computeResidualVector(matrixA, vectorx, vectorb);

///Use the Diagonal Inverse function to compute the Inverse of D
double* D_1 = ComputeDInverse(matrixA);										

//Now, to the actual Damped Jacobi Method
Vector x_kp1;               //The approximation value, x_k + 1
Vector r_kp1;               //The value of the residual vector r_k + 1.
double r_k_l2_norm;         //The value of the l2 Norm, ||r_k||.

/* Is this neccessary?

//Initializing 
for (int i = 0; i < vectorb.length; i++)
    {
       x_kp1.vector_entries[i] = vectorx.vector_entries[i];
       r_kp1.vector_entries[i] = r0.vector_entries[i];  
    }             
*/

do
 { 
	for (int n = 0; n < max_num_iterate; n++)
		{
            //////Step i - find the approximation x 

            //Solve for the approximation, x_k + 1
            x_kp1.length = vectorb.length;
            x_kp1.vector_entries = new double[x_kp1.length];
            for (int k = 0; k < r0.length; k++)
                {
                    x_kp1.vector_entries[k] =  x_kp1.vector_entries[k] + (w * D_1[matrixA.n] * r0.vector_entries[k]);
                    //x_kp1.vector_entries[k] =  x.vector_entries[k] + wr0.vector_entries[k] * D_1[matrixA.n];
                }


            //////Step ii - Use the residual function to solve r_k + 1 = b - Ax_k + 1
            r_kp1 = computeResidualVector(matrixA, x_kp1, vectorb);


            //The l2 Norm, ||r_k||.
            double r_k_l2_norm = l2_norm (r_kp1);            
            

            std::cout << "The iteration counter is " << n << " and the norm of the residual vector is " << r_k_l2_norm << std::endl;   
	    }
}

//Termination Condition
while (r_k_l2_norm >= tol);

return x_kp1;                                   //Value Output                    

}

