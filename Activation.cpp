//
// Created by anna_seli on 13/06/2021.
//
#include "Activation.h"

#define INVALID_ACT_FUNC "invalid activation function"
#define EXIT_FAILURE 1

/*
* Activation constructor
*/
Activation::Activation(ActivationType act_type)
    : activation_type(act_type)
{
    if ((act_type != RELU) && (act_type != SOFTMAX))
    {
        std::cerr << INVALID_ACT_FUNC << std::endl;
        exit(EXIT_FAILURE);
    }
}

/*
* activation type getter
* @return activation type
*/
ActivationType Activation::get_activation_type() const
{
    return activation_type;
}

/*
* parenthesis operator that activates the right activation function
* @return reference to output of activation function
*/
Matrix Activation::operator()(const Matrix &input)
{
    Matrix output_vector = input;
    if (activation_type == RELU)
    {
        for (auto i = 0; i < input.get_rows() * input.get_cols(); i++)
        {
            if (output_vector[i] < 0.0)
            {
                output_vector[i] = 0.0;
            }
        }
    }

    else if (activation_type == SOFTMAX)
    {
        float sum = 0;
        for (auto i = 0; i < input.get_rows() * input.get_cols(); i++)
        {
            float temp = std::exp(input.matrix_data[i]);
            sum += temp;
            output_vector.matrix_data[i] = temp;
        }
        output_vector = (1 / sum) * output_vector;
    }
    else
    {
        std::cerr << INVALID_ACT_FUNC << std::endl;
        exit(EXIT_FAILURE);
    }
    return output_vector;
}

