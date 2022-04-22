//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <iostream>
#include <cmath>

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

/*
 * Activation function class
 */
class Activation
{

private:
    ActivationType activation_type;

public:
    /*
    * Activation constructor
    */
    Activation(ActivationType act_type);
    /*
    * activation type getter
    * @return activation type
    */
    ActivationType get_activation_type() const;
    /*
    * parenthesis operator that activates the right activation function
    * @return reference to output of activation function
    */
    Matrix operator()(const Matrix &input);
};

#endif //ACTIVATION_H
