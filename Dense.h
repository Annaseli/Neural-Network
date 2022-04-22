#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"
#include "Matrix.h"

/*
* Dense cass
*/
class Dense
{

private:
    Matrix w_matrix;
    Matrix b_vector;
    ActivationType activation_type;

public:
    /*
    * Dense class constructor
    * @param w array of weights for the layer
    * @param bias array of biases for the layer
    * @param act_type activation type of the object
    */
    Dense(const Matrix &w, const Matrix &bias, ActivationType act_type);
    /*
     * getter of array of weights
     */
    Matrix get_weights() const;
    /*
    * getter of array of biases
    */
    Matrix get_bias() const;
    /*
    * getter of activation function
    */
    Activation get_activation() const;
    /*
    * parenthesis operator which calculates weights array * matrix input + bias
     * @param input matrix fot this layer
     * @return output matrix fot this layer
    */
    Matrix &operator()(Matrix &input);
};

#endif //C___PROJECT_DENSE_H
