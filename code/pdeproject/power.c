/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 ****************************************************************/

#include "petscksp.h"

int main(int argc,char **argv)
{
  Mat A; Vec X,Y,T;
  int npts = 100,maxit = 50, it;
  PetscErrorCode ierr;

  ierr = PetscInitialize(&argc,&argv,0,0); CHKERRQ(ierr);

  /* 
   * Get the problem size and maximum number of iterations
   */
  ierr = PetscOptionsGetInt
    (PETSC_NULL,"-size",&npts,PETSC_NULL); CHKERRQ(ierr);
  ierr = PetscOptionsGetInt
    (PETSC_NULL,"-maxit",&maxit,PETSC_NULL); CHKERRQ(ierr);

  /*
   * Construct a matrix
   */
  ierr = MatCreate(MPI_COMM_WORLD,&A); CHKERRQ(ierr);
  ierr = MatSetType(A,MATMPIAIJ); CHKERRQ(ierr);
  ierr = MatSetSizes(A,PETSC_DECIDE,PETSC_DECIDE,npts,npts); CHKERRQ(ierr);

  /*
   * Set the elements
   */
  {
    int myfirst,mylast,row;
    PetscScalar coeffs[3]; int jcoeffs[3];
    coeffs[0] = -1.; coeffs[1] = 2.; coeffs[2] = -1;
    ierr = MatGetOwnershipRange(A,&myfirst,&mylast); CHKERRQ(ierr);
    for (row=myfirst; row<mylast; row++) {
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
    ierr = MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
    ierr = MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
  }

  ierr = VecCreate(MPI_COMM_WORLD,&X); CHKERRQ(ierr);
  ierr = VecSetType(X,VECMPI); CHKERRQ(ierr);
  ierr = VecSetSizes(X,PETSC_DECIDE,npts); CHKERRQ(ierr);
  ierr = VecDuplicate(X,&Y); CHKERRQ(ierr);
  ierr = VecDuplicate(X,&T); CHKERRQ(ierr);

  /*
   * Set initial vector
   */
  {
    int myfirst;
    ierr = VecGetOwnershipRange(X,&myfirst,PETSC_NULL); CHKERRQ(ierr);
    if (myfirst==0) {
      int izero=0; PetscScalar zero=0.,one=1.;
      ierr = VecSetValues(X,1,&izero,&one,INSERT_VALUES); CHKERRQ(ierr);
    }
    ierr = VecAssemblyBegin(X); CHKERRQ(ierr);
    ierr = VecAssemblyEnd(X); CHKERRQ(ierr);
  }

  /*
   * Iterate Power Method
   */
  for (it=0; it<maxit; it++) {
    PetscReal nrm,mag; PetscScalar mone=-1.;
    ierr = MatMult(A,X,Y); CHKERRQ(ierr);
    ierr = VecNorm(Y,NORM_2,&nrm); CHKERRQ(ierr);
    mag = nrm;
    if (nrm>0.) nrm = 1./nrm;
    ierr = VecScale(Y,nrm); CHKERRQ(ierr);
    ierr = VecCopy(Y,T); CHKERRQ(ierr);
    ierr = VecAXPY(T,mone,X); CHKERRQ(ierr);
    ierr = VecNorm(T,NORM_2,&nrm); CHKERRQ(ierr);
    ierr = PetscPrintf
      (MPI_COMM_WORLD,"[%3d] Magnification: %e, difference norm: %e\n",
       it,mag,nrm); CHKERRQ(ierr);
    ierr = VecCopy(Y,X); CHKERRQ(ierr);
  }

  ierr = MatDestroy(A); CHKERRQ(ierr);
  ierr = VecDestroy(X); CHKERRQ(ierr);
  ierr = VecDestroy(Y); CHKERRQ(ierr);
  ierr = VecDestroy(T); CHKERRQ(ierr);

  ierr = PetscFinalize(); CHKERRQ(ierr);

  return 0;
}
