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
#include "myh5defs.h"

PetscReal forcing(PetscReal x)
{
  return exp(x);
}

int main(int argc,char **argv)
{
  Mat A; Vec Force;
  int npts, iim;
  PetscTruth implicit=PETSC_FALSE,restart=PETSC_FALSE,has;
  PetscReal deltaX=1.e-1, deltaT=1.e-3, alpha=1.;
  hid_t restart_fileid,dx_space,dt_space,im_space, dx_id,dt_id,im_id;
  herr_t status;
  PetscErrorCode ierr;

  ierr = PetscInitialize(&argc,&argv,0,0); CHKERRQ(ierr);

  /* 
   * Get the problem size and maximum number of iterations
   */
  ierr = PetscOptionsHasName
    (PETSC_NULL,"-help",&has); CHKERRQ(ierr);
  if (has) {
    printf("\nOptions: -restart OR -deltax dx -deltat dt [-implicit]\n\n");
    return 0;
  }
  ierr = PetscOptionsHasName
    (PETSC_NULL,"-restart",&restart); CHKERRQ(ierr);
#define RESTART "restart-file.h5"
  if (restart) {
    restart_fileid = H5Fopen(RESTART,H5F_ACC_RDONLY,H5P_DEFAULT); 
    H5REPORT(restart_fileid);
    dx_space = H5Dopen1(restart_fileid,"/dx"); H5REPORT(dx_space);
    dt_space = H5Dopen1(restart_fileid,"/dt"); H5REPORT(dt_space);
    im_space = H5Dopen1(restart_fileid,"/im"); H5REPORT(im_space);

    status = H5Dread(dx_space,H5T_NATIVE_DOUBLE,H5S_ALL,H5S_ALL,
		     H5P_DEFAULT,&deltaX); H5REPORT(status);
    status = H5Dread(dt_space,H5T_NATIVE_DOUBLE,H5S_ALL,H5S_ALL,
		     H5P_DEFAULT,&deltaT); H5REPORT(status);
    status = H5Dread(im_space,H5T_NATIVE_DOUBLE,H5S_ALL,H5S_ALL,
		     H5P_DEFAULT,&iim); H5REPORT(status);
    implicit = iim>0;
  } else {
    restart_fileid = H5Fcreate(RESTART,H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);
    ierr = PetscOptionsGetReal
      (PETSC_NULL,"-deltax",&deltaX,PETSC_NULL); CHKERRQ(ierr);
    ierr = PetscOptionsGetReal
      (PETSC_NULL,"-deltat",&deltaT,PETSC_NULL); CHKERRQ(ierr);
    //ierr = PetscOptionsGetInt
    //(PETSC_NULL,"-maxit",&maxit,PETSC_NULL); CHKERRQ(ierr);
    ierr = PetscOptionsHasName
      (PETSC_NULL,"-implicit",&implicit); CHKERRQ(ierr);

    dx_space = H5Screate(H5S_SCALAR); H5REPORT(dx_space);
    dx_id = H5Dcreate1(restart_fileid,"/dx",
		      H5T_NATIVE_DOUBLE,dx_space,H5P_DEFAULT); H5REPORT(dx_id);
    dt_space = H5Screate(H5S_SCALAR); H5REPORT(dt_space);
    dt_id = H5Dcreate1(restart_fileid,"/dt",
		      H5T_NATIVE_DOUBLE,dt_space,H5P_DEFAULT); H5REPORT(dt_id);
    im_space = H5Screate(H5S_SCALAR); H5REPORT(im_space);
    im_id = H5Dcreate1(restart_fileid,"/im",
		      H5T_NATIVE_INT,im_space,H5P_DEFAULT); H5REPORT(im_id);

    status = H5Dwrite(dx_id,H5T_NATIVE_DOUBLE,H5S_ALL,H5S_ALL,
		      H5P_DEFAULT,(void*)&deltaX); H5REPORT(status);
    status = H5Dwrite(dt_id,H5T_NATIVE_DOUBLE,H5S_ALL,H5S_ALL,
		      H5P_DEFAULT,(void*)&deltaT); H5REPORT(status);
    if (implicit) iim = 1; else iim = 0;
    status = H5Dwrite(im_id,H5T_NATIVE_INT,H5S_ALL,H5S_ALL,
		      H5P_DEFAULT,(void*)&iim); H5REPORT(status);
  }
  npts = 1./deltaX-1;
  printf("running with parameters Dx=%e, Dt=%e, npts=%d, im=%d\n",
	 deltaX,deltaT,npts,(int)implicit);
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

  status = H5Fclose(restart_fileid);
  ierr = MatDestroy(A); CHKERRQ(ierr);
  ierr = VecDestroy(Force); CHKERRQ(ierr);

  ierr = PetscFinalize(); CHKERRQ(ierr);

  return 0;
}
