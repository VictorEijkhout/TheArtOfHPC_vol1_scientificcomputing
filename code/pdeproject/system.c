/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 ****************************************************************/

#include "petscksp.h"

PetscReal forcing(PetscReal x)
{
  return exp(x);
}

int main(int argc,char **argv)
{
  Mat A; Vec Sol,Rhs;
  int npts = 100,maxit = 50;
  PetscReal h;
  PetscErrorCode ierr;

  ierr = PetscInitialize(&argc,&argv,0,0); CHKERRQ(ierr);

  /* 
   * Get the problem size and maximum number of iterations
   */
  ierr = PetscOptionsGetInt
    (PETSC_NULL,"-size",&npts,PETSC_NULL); CHKERRQ(ierr);
  h = 1./(npts+1);
  ierr = PetscOptionsGetInt
    (PETSC_NULL,"-maxit",&maxit,PETSC_NULL); CHKERRQ(ierr);

  /*
   * Construct a matrix and vector
   */
  ierr = MatCreate(MPI_COMM_WORLD,&A); CHKERRQ(ierr);
  ierr = MatSetType(A,MATMPIAIJ); CHKERRQ(ierr);
  ierr = MatSetSizes(A,PETSC_DECIDE,PETSC_DECIDE,npts,npts); CHKERRQ(ierr);
  ierr = VecCreate(MPI_COMM_WORLD,&Rhs); CHKERRQ(ierr);
  ierr = VecSetType(Rhs,VECMPI); CHKERRQ(ierr);
  ierr = VecSetSizes(Rhs,PETSC_DECIDE,npts); CHKERRQ(ierr);
  ierr = VecDuplicate(Rhs,&Sol); CHKERRQ(ierr);

  /*
   * Set the elements
   */
  {
    PetscReal x,f,x0=0.,xN=1.;
    int myfirst,mylast,row;
    PetscScalar coeffs[3]; int jcoeffs[3];
    coeffs[0] = -1.; coeffs[1] = 2.; coeffs[2] = -1;
    ierr = MatGetOwnershipRange(A,&myfirst,&mylast); CHKERRQ(ierr);
    for (row=myfirst; row<mylast; row++) {
      /* Rhs vector */
      x = row*h; f = forcing(x)*h*h;
      if (row==0) f += x0;
      else if (row==npts-1) f += xN;
      ierr = VecSetValues(Rhs,1,&row,&f,INSERT_VALUES); CHKERRQ(ierr);
      /* Coefficient matrix */
      jcoeffs[0] = row-1; jcoeffs[1] = row; jcoeffs[2] = row+1;
      if (row==0) {
	ierr = MatSetValues
	  (A,1,&row,2,jcoeffs+1,coeffs+1,INSERT_VALUES); CHKERRQ(ierr);
      } else if (row==npts-1) {
	ierr = MatSetValues
	  (A,1,&row,2,jcoeffs,coeffs,INSERT_VALUES); CHKERRQ(ierr);
      } else {
	ierr = MatSetValues
	  (A,1,&row,3,jcoeffs,coeffs,INSERT_VALUES); CHKERRQ(ierr);
      }
    }
  }
  ierr = MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
  ierr = MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
  ierr = VecAssemblyBegin(Rhs); CHKERRQ(ierr);
  ierr = VecAssemblyEnd(Rhs); CHKERRQ(ierr);


  /* 
   * Solve system
   */
  {
    KSP solver;

    ierr = KSPCreate(MPI_COMM_WORLD,&solver); CHKERRQ(ierr);
    ierr = KSPSetOperators(solver,A,A,0); CHKERRQ(ierr);

    ierr = KSPSolve(solver,Rhs,Sol); CHKERRQ(ierr);
    VecView(Sol,0);
  }

  ierr = MatDestroy(A); CHKERRQ(ierr);
  ierr = VecDestroy(Rhs); CHKERRQ(ierr);
  ierr = VecDestroy(Sol); CHKERRQ(ierr);

  ierr = PetscFinalize(); CHKERRQ(ierr);

  return 0;
}
