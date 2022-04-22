//
// Created by anna_seli on 13/06/2021.
//
#include "Dense.h"

#define INVALID_ACT_FUNC "invalid activation function"
#define EXIT_FAILURE 1

Dense::Dense(const Matrix &w, const Matrix &bias, ActivationType act_type)
    : w_matrix(w), b_vector(bias), activation_type(act_type)
{
    if ((act_type != RELU) && (act_type != SOFTMAX))
    {
        std::cerr << INVALID_ACT_FUNC << std::endl;
        exit(EXIT_FAILURE);
    }
}

/*
 * getter of array of weights
 */
Matrix Dense::get_weights() const
{
    return w_matrix;
}

/*
* getter of array of biases
*/
Matrix Dense::get_bias() const
{
    return b_vector;
}

/*
* getter of activation function
*/
Activation Dense::get_activation() const
{
    Activation act_func (activation_type);
    return act_func;
}

/*
 * parenthesis operator which calculates weights array * matrix input + bias
 * @param input matrix fot this layer
 * @return output matrix fot this layer
 */
Matrix &Dense::operator()(Matrix &input)
{
    Matrix matrix = (w_matrix * input + b_vector);
    Activation act_func (activation_type);
    input = act_func(matrix);
    return input;
}