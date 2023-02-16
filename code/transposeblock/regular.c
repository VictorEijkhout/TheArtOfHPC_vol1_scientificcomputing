/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2023
 ****
 ****************************************************************/

// -*- c -*-
//snippet regulartranspose
for (int i=0; i<N; i++)
  for (int j=0; j<N; j++)
    A[i][j] = B[j][i];
//snippet end
