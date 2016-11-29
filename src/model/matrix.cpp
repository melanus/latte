#include "matrix.h"

//debugging, delete this
#include <iostream>

Matrix::Matrix() { }

Matrix::Matrix(vector<size_t> dimensions) : shape(dimensions) {
  size_t total_size = 1;
  for (auto d : dimensions) {
    total_size *= d;
  }

  data = new double[total_size];

  //TEMP: fill with zeros
  memset(data, -1.0, total_size*sizeof(double));
}

//something about this feels dirty, but I think the scope will be okay
Matrix::Matrix(double *in_data, vector<size_t> in_shape) : shape(in_shape), data(in_data) { }

//get single value from dim
double &Matrix::get(vector<size_t> dim) {
  assert(dim.size() == shape.size());
  int index = 0;
  for(int i = 0; i < shape.size(); i++) {
    index += dim[i] * pow(shape[i], i);
  }
  return data[index];
}

Matrix Matrix::operator[](size_t index) {
  //do bound checking at some point
  
  vector<size_t> new_shape(shape.size() - 1);
  for (int i = 0; i < shape.size() - 1; i++) {
    new_shape[i] = shape[i];
  }

  if (shape.size() == 1) {
    new_shape.push_back(1);
  }

  return Matrix(&operator()(index), new_shape); //Matrix(operator()(index), shape);
}

double &Matrix::operator()(size_t index) {
  //do bound checking at some point
  int slice = 0;
  int size = shape.size();
  slice = index * pow(shape[size - 1], size - 1);
  return data[slice];
}
