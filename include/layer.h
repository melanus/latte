#ifndef LAYER_H
#define LAYER_H

#include "matrix.h"
#include <string>
#include <vector>

class Layer {
  public:
    Layer() { };
    Layer(const Layer &obj) { }
    virtual ~Layer() { };
    virtual Matrix &forward(Matrix &) = 0;
    virtual Matrix &forward(vector<Matrix> &) = 0;
    std::string name;
    std::vector<std::string> next;
    std::vector<std::string> prev;
};

#endif
