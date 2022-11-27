#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "multigrid.hpp"

Vector prolongateVector(Vector vectorC)
{
Vector vectorF;
int n = sqrt(vectorC.length) - 1;                                       //Estimate the size of the prolongated vector
vectorF.length  = pow((n*2 + 1), 2);                                    //Lenght of prolongated vector.
vectorF.vector_entries = new double[vectorF.length];	

for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            {
                int x = (n + 1) * i + j;                                //Initial Values 
                int y =  (2*n + 1) * 2*i + 2*j;                         //Prolongated Values
                
                vectorF.vector_entries[y] = vectorC.vector_entries[x];
                //The entries in the prolongated vector at the red circle nodes which is the value corresponding to the red circle nodes
                
                vectorF.vector_entries[(2*n + 1) * (2*i) + (2*j) + 1] = (vectorC.vector_entries[(2*n + 1) * (2*i) + (2*j)] + vectorC.vector_entries[(2*n + 1) * (2*i) + (2*j) + 1]) / 2;
                //The entries in the prolongated vector at the green diamond nodes which is the average of the 2 neighbouring red circle nodes
                
                vectorF.vector_entries[(2*n+1) * (2*i+1) + (2*j+1)] = (vectorC.vector_entries[(n+1) * i+j] + vectorC.vector_entries[(n+1) * (i+1) +j] + vectorC.vector_entries[(n+1) * (i) + (j+1)] + vectorC.vector_entries[(n+1) * (i+1) +(j+1)]) / 4;                
                //The entries in the prolongated vector at the blue square nodes which is the average of the 4 neighbouring red circle nodes
            }  
    }  
return vectorF;                         //Value Output
}
 

Vector restrictVector(Vector vectorF)
{
Vector vectorC;
int n = sqrt(vectorF.length) - 1;                                           ////Estimate the size of the restricted vector
vectorC.length = pow((n/2 + 1), 2);                                         //Lenght of restricted vector.
vectorC.vector_entries = new double[vectorC.length];	

for (int i = 0; i < n; i+=2)
    {
        for (int j = 0; j < n; j+=2)
            { 
                int x = (n + 1) * i + j;                              //Initial Values 
                int y = (n/2 + 1) * i/2 + j/2;                        //Restricted Values
                
                vectorC.vector_entries[y] = vectorF.vector_entries[x];
                //The entries in the restricted vector at the red circle nodes which is the value corresponding to the red circle nodes
            }  
    }
return vectorC;                                        //Value Output
}


Vector vCycle(Sparse_matrix matrixA, Vector vectorF, Vector vectorU, int n, double w)
{
int max_num_iterate = 10;
double tol = 0;
//Pre-smoothing with Jacobi Method.
vectorU = jacobi_method(w, 0, 10, matrixA,  vectorF);

if (n % 2 > 0)
    {
        vectorU = jacobi_method(w, 0, 10, matrixA,  vectorF);
    }

else if (n % 2 == 0)
{

//Compute residual vector, f − A_h*U_h
Vector residualVector = computeResidualVector(matrixA, vectorU, vectorF);

//Restrict residual vector
Vector rv_2h = restrictVector(residualVector);

//Set initial value for the vector w_2h to be a zero vector	
Vector w_2h = createZeroVector(rv_2h);

//Recurse the function
w_2h = vCycle(matrixA, w_2h, residualVector, n/2, w);

//Prolongate w_2h
Vector w_h = prolongateVector(w_2h);

//Correction
Vector correct_w_h;
for (int i = 0; i <= w_h.length; i++) 
    {
       correct_w_h.vector_entries[i] = vectorU.vector_entries[i] + w_h.vector_entries[i];
    }

//Post-smoothing with Jacobi Method.
vectorU = jacobi_method(w, 0, 10, matrixA,  correct_w_h);

}
return vectorU;                                     //Value Output
}


Vector wCycle(Sparse_matrix matrixA, Vector vectorF, Vector vectorU, int n, double w)
{
int max_num_iterate = 10;
double tol = 0;

//Pre-smoothing with Jacobi Method.
vectorU = jacobi_method(w, 0, 10, matrixA,  vectorF);

if (n % 2 > 0)
    {
        vectorU = jacobi_method(w, 0, 10, matrixA,  vectorF);
    }

else if (n % 2 == 0)
    {
    //Compute residual vector, f − A_h*U_h
    Vector residualVector = computeResidualVector(matrixA, vectorU, vectorF);

    //Restrict residual vector
    Vector rv_2h = restrictVector(residualVector);

    //Set initial value for the vector w_2h to be a zero vector		
    Vector w_2h = createZeroVector(rv_2h);
                    
    //Recurse the function twice
    Vector w_2h_1 = wCycle(matrixA, w_2h, residualVector, n/2, w);
    Vector w_2h_2 = wCycle(matrixA, w_2h_1, residualVector, n/2, w);

    //Prolongate w_2h
    Vector w_h = prolongateVector(w_2h_2);

    //Correction
    Vector correct_w_h;
    for (int i = 0; i <= w_h.length; i++) 
        {
        correct_w_h.vector_entries[i] = vectorU.vector_entries[i] + w_h.vector_entries[i];
        }

    //Post-smoothing with Jacobi Method.
    vectorU = jacobi_method(w, 0, 10, matrixA, correct_w_h);

    }

return vectorU;                                 //Value Output
}


//The Full Multigrid Algorithm for  V-Cycle and W-Cycle 

//For V-Cycle

void multigrid_vCycle(Sparse_matrix matrixA, Vector vectorF, int n, double w, double tol)
{
     Vector vectorU;

    //Set initial value for the vector u_h to be a zero vector		
    vectorU = createZeroVector(vectorF);

    double rv_norm; 
    int k = 1;
    do
    { 

        vectorU = vCycle(matrixA, vectorF, vectorU, n, w);

        //Compute residual vector, f − A_h*U_h
        Vector residualVector = computeResidualVector(matrixA, vectorU, vectorF);

        //Find the 2-norm of the residual vector
        rv_norm = l2_norm(residualVector);

        std::cout << "The iteration counter is " << k << " and the norm of the residual vector is " <<  rv_norm << std::endl;   
        k=k+1;
    }
    //Termination Condition
    while (rv_norm >= tol);
}


//For W-Cycle 
void multigrid_wCycle(Sparse_matrix matrixA, Vector vectorF, int n, double w, double tol)
{
    Vector vectorU;

    //Set initial value for the vector u_h to be a zero vector		
    vectorU = createZeroVector(vectorF);

    double rv_norm; 
    int k = 1;
    do
    { 
 
        vectorU = wCycle(matrixA, vectorF, vectorU, n, w);

        //Compute residual vector, f − A_h*U_h
        Vector residualVector = computeResidualVector(matrixA, vectorU, vectorF);

        //Find the 2-norm of the residual vector
        rv_norm = l2_norm(residualVector);

        std::cout << "The iteration counter is " << k << " and the norm of the residual vector is " <<  rv_norm << std::endl;   
    }
    //Termination Condition
    while (rv_norm >= tol);
}