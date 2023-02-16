/****************************************************************
 ****************************************************************
 ****
 **** This text file is part of the source of 
 **** `Introduction to High-Performance Scientific Computing'
 **** by Victor Eijkhout, copyright 2012-2021
 ****
 **** Deep Learning Network code 
 **** copyright 2021 Ilknur Mustafazade
 ****
 ****************************************************************
 ****************************************************************/

#ifndef CODE_VEC2_H
#define CODE_VEC2_H

#include <vector>
#include "vector.h"
#include "matrix.h"
#include <iostream>
#ifdef BLISNN
#include "blis/blis.h"
#endif

class VectorBatch{
  friend class Matrix;
  friend class Vector;

#if 0
  // hm. this doesn't work
  friend void relu_io    (const Vector &i, Vector &v);
  friend void sigmoid_io (const Vector &i, Vector &v);
  friend void softmax_io (const Vector &i, Vector &v);
  friend void none_io    (const Vector &i, Vector &v);
  friend void reluGrad_io(const Vector &m, Vector &a);
  friend void sigGrad_io (const Vector &m, Vector &a);

  friend void relu_io    (const VectorBatch &i, VectorBatch &v);
  friend void sigmoid_io (const VectorBatch &i, VectorBatch &v);
  friend void softmax_io (const VectorBatch &i, VectorBatch &v);
  friend void none_io    (const VectorBatch &i, VectorBatch &v);
  friend void reluGrad_io(const VectorBatch &m, VectorBatch &a);
  friend void sigGrad_io (const VectorBatch &m, VectorBatch &a);
#endif

public: //private:
  std::vector<float> vals;
public:
    int r;
    int c;
    VectorBatch();
    VectorBatch(int nRows, int nCols, bool rand=false);

    int size() const { return vals.size(); };
    void resize(int m,int n) { r = m; c = n; vals.resize(m*n); };
    int item_size() const { return c; };
    int batch_size() const { return r; };
    VectorBatch transpose() const;
    std::vector<float>& vals_vector() { return vals; };
    const std::vector<float>& vals_vector() const { return vals; };
    float *data() { return vals.data(); };
    const float *data() const { return vals.data(); };

	
	void v2mp( const Matrix &x, VectorBatch &y) const;
    void v2tmp( const Matrix &x, VectorBatch &y ) const;
	void v2mtp( const Matrix &x, VectorBatch &y ) const;
	void outer2( const VectorBatch &x, Matrix &y ) const;
	
	void set_col(int j,const std::vector<float> &v ) {
      assert( v.size()==r );
      for (int i = 0; i < r; i++) {
	vals.at( j + c * i ) = v.at(i);
      };
    };
    std::vector<float> get_col(int j) const {
      std::vector<float> col(r);
      for (int i=0; i<r; i++)
	col.at(i) = vals.at( j + c*i );
      return col;
    };

    std::vector<float> get_vector(int v) const {
      //return get_col(v);
	  return get_row(v);
    };
    
	Vector get_vectorObj(int j) const {
	  /*Vector vec(r,0);
	  for (int i=0; i<r; i++)
	    vec.vals.at(i) = vals.at( j+c*i );
	return vec;*/
		Vector vec(c,0);
		for (int i = 0; i < c; i++ ) 
			vec.vals.at(i) = vals.at( j * c + i );

		return vec;
	}

	void set_vector( const Vector &v, int j) {
	  for (int i=0; i<c; i++)
	    vals.at( j * c + i ) = v.vals.at(i); 
	}

	// contiguous set/get methods
	void set_row( int j, const std::vector<float> &v ) {
	  assert( v.size()==c );
	  for (int i = 0; i < c; i++) {
	    vals.at( j * c + i ) = v.at(i);
	  };
	}

	std::vector<float> get_row(int j) const {
   	  std::vector<float> row(c);
   	  for (int i = 0; i < c; i++)
	    row.at(i) = vals.at( j * c + i );
      return row;
    };
	
	void show() const;

	void addh(const Vector &y);
	Vector meanh();
	
	VectorBatch operator-(); // Unary negate operator
    VectorBatch& operator=(const VectorBatch& m2); // Copy constructor
    VectorBatch operator*(const VectorBatch &m2); // Hadamard Product Element-wise multiplication
    VectorBatch operator/(const VectorBatch &m2); // Element-wise division
    VectorBatch operator-(const VectorBatch &m2); // Element-wise subtraction
	friend VectorBatch operator/(const VectorBatch &m, const float &c); // for matrix-constant division
	friend VectorBatch operator*(const float &c, const VectorBatch &m); // for matrix-constant division
};


#endif
