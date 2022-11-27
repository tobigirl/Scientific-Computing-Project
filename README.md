# Scientific-Computing-Project

This is a 2D finite difference solver to solve the following PDE boundary value problem

−𝛥𝑢 = 1, (𝑥,𝑦) ∈ 𝛺 ∶= (0,1)
𝑢(𝑥,𝑦) = 0, (𝑥,𝑦) ∈ 𝜕𝛺.

First I defined a sparse matrix and vector structure, then I wrote subprograms to build the linear system arising from the finite difference approximation of the problem equations, then I solved it using a multigrid linear solver.

This project is still a work in progress. If you need further clarification on it, contact me via thetobigeorge@gmail.com
