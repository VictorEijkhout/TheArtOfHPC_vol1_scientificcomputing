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

#ifndef SRC_FUNCS_H
#define SRC_FUNCS_H
#include "matrix.h"
#include "vector.h"
#include "vector2.h"

enum acFunc{RELU,SIG,SMAX,NONE};

template <typename V>
void relu_io    (const V &i, V &v);
template <typename V>
void sigmoid_io (const V &i, V &v);
template <typename V>
void softmax_io (const V &i, V &v);
template <typename V>
void linear_io    (const V &i, V &v);

template <typename V>
void reluGrad_io(const V &m, V &a);
template <typename V>
void sigGrad_io (const V &m, V &a);
template <typename V>
void smaxGrad_io(const V &m, V &a);
template <typename V>
void linGrad_io	(const V &m, V &a);

Matrix smaxGrad_vec(std::vector<float> &v);

#endif //SRC_FUNCS_H
