/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 ****************************************************************/

#include "petscksp.h"
#include <stdio.h>

PetscReal forcing(PetscReal x)
{
  return exp(x);
}

int main(int argc,char **argv)
{
  Mat A; Vec Force;
  int npts;;
  PetscTruth implicit=PETSC_FALSE;
  PetscReal deltaX=1.e-1, deltaT=1.e-3, alpha=1.;
  PetscErrorCode ierr;

  ierr = PetscInitialize(&argc,&argv,0,0); CHKERRQ(ierr);

  /* 
   * Get the problem size and maximum number of iterations
   */
  ierr = PetscOptionsGetReal
    (PETSC_NULL,"-deltax",&deltaX,PETSC_NULL); CHKERRQ(ierr);
  npts = 1./deltaX-1;
  ierr = PetscOptionsGetReal
    (PETSC_NULL,"-deltat",&deltaT,PETSC_NULL); CHKERRQ(ierr);
  //ierr = PetscOptionsGetInt
  //(PETSC_NULL,"-maxit",&maxit,PETSC_NULL); CHKERRQ(ierr);
  ierr = PetscOptionsHasName
    (PETSC_NULL,"-implicit",&implicit); CHKERRQ(ierr);
  ierr = PetscOptionsHasName
    (PETSC_NULL,"-implicit",&implicit); CHKERRQ(ierr);
  {
    PetscTruth explicit;
    ierr = PetscOptionsHasName
      (PETSC_NULL,"-explicit",&explicit); CHKERRQ(ierr);
    if (explicit) implicit = PETSC_FALSE;
  }
  /*
   * Construct a matrix and vector
   */
  ierr = MatCreate(MPI_COMM_WORLD,&A); CHKERRQ(ierr);
  ierr = MatSetType(A,MATMPIAIJ); CHKERRQ(ierr);
  ierr = MatSetSizes(A,PETSC_DECIDE,PETSC_DECIDE,npts,npts); CHKERRQ(ierr);
  ierr = VecCreate(MPI_COMM_WORLD,&Force); CHKERRQ(ierr);
  ierr = VecSetType(Force,VECMPI); CHKERRQ(ierr);
  ierr = VecSetSizes(Force,PETSC_DECIDE,npts); CHKERRQ(ierr);

  /*
   * Set the elements
   */
  {
    PetscReal x,f,x0=0.,xN=1.,h=deltaX;
    int myfirst,mylast,row;
    PetscScalar coeffs[3]; int jcoeffs[3];
    coeffs[0] = -1.; coeffs[1] = 2.; coeffs[2] = -1;
    ierr = MatGetOwnershipRange(A,&myfirst,&mylast); CHKERRQ(ierr);
    for (row=myfirst; row<mylast; row++) {
      /* Force vector */
      x = row*h; f = forcing(x)*h*h;
      if (row==0) f += x0;
      else if (row==npts-1) f += xN;
      ierr = VecSetValues(Force,1,&row,&f,INSERT_VALUES); CHKERRQ(ierr);
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
    ierr = MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
    ierr = MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
    ierr = VecAssemblyBegin(Force); CHKERRQ(ierr);
    ierr = VecAssemblyEnd(Force); CHKERRQ(ierr);
  }

  {
    PetscReal fraction; PetscScalar one=1.;
    int myfirst,mylast,row;

    fraction = alpha*deltaT/(deltaX*deltaX);
    printf("fraction %e\n",fraction);
    if (implicit) {
      ierr = MatScale(A,fraction); CHKERRQ(ierr);
    } else {
      ierr = MatScale(A,-fraction); CHKERRQ(ierr);
    }
    ierr = MatGetOwnershipRange(A,&myfirst,&mylast); CHKERRQ(ierr);
    for (row=myfirst; row<mylast; row++) {
      ierr = MatSetValues(A,1,&row,1,&row,&one,ADD_VALUES); CHKERRQ(ierr);
    }
    ierr = MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
    ierr = MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
  }

  /* 
   * Time iteration
   */
  {
    FILE *f;
    KSP solver;
    Vec Tk,temp,diff;
    PetscReal t; int it;

    ierr = VecDuplicate(Force,&Tk); CHKERRQ(ierr);
    ierr = VecDuplicate(Force,&temp); CHKERRQ(ierr);
    ierr = VecDuplicate(Force,&diff); CHKERRQ(ierr);

    if (implicit) {
      ierr = KSPCreate(MPI_COMM_WORLD,&solver); CHKERRQ(ierr);
      ierr = KSPSetOperators(solver,A,A,0); CHKERRQ(ierr);
    }
    f = fopen("plot.dat","w");
    for (it=0,t=0; it<100 && t<1.; it++,t+=deltaT) {
      if (implicit) {
	ierr = VecCopy(Tk,diff); CHKERRQ(ierr);
	ierr = VecAXPY(diff,deltaT,Force); CHKERRQ(ierr);
	ierr = KSPSolve(solver,diff,temp); CHKERRQ(ierr);
      } else {
	ierr = MatMult(A,Tk,temp); CHKERRQ(ierr);
	ierr = VecAXPY(temp,deltaT,Force); CHKERRQ(ierr);
      }
      /* temp now contains the new Tk; compute the difference and copy over */
      {
	PetscReal diffnorm,mone=-1.;
	ierr = VecCopy(temp,diff); CHKERRQ(ierr);
	ierr = VecAXPY(diff,mone,Tk); CHKERRQ(ierr);
	ierr = VecNorm(diff,NORM_2,&diffnorm); CHKERRQ(ierr);
	ierr = PetscPrintf
	  (MPI_COMM_WORLD,
	   "[%d] Difference between iterates: %e\n",it,diffnorm); CHKERRQ(ierr);
      }
      ierr = VecCopy(temp,Tk); CHKERRQ(ierr);
      {
	PetscScalar *a; int i;
	ierr = VecGetArray(Tk,&a); CHKERRQ(ierr);
	for (i=0; i<npts; i++) {
	  fprintf(f,"%e ",a[i]);
	} fprintf(f,"\n");
	ierr = VecRestoreArray(Tk,&a); CHKERRQ(ierr);
      }
    }
    ierr = VecDestroy(Tk); CHKERRQ(ierr);
    ierr = VecDestroy(temp); CHKERRQ(ierr);
    ierr = VecDestroy(diff); CHKERRQ(ierr);
    if (implicit) {
      ierr = KSPDestroy(solver); CHKERRQ(ierr);
    }
    fclose(f);
  }

  ierr = MatDestroy(A); CHKERRQ(ierr);
  ierr = VecDestroy(Force); CHKERRQ(ierr);

  ierr = PetscFinalize(); CHKERRQ(ierr);

  return 0;
}
