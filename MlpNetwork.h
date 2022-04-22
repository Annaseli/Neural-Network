//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Dense.h"
#include "Digit.h"

#define MLP_SIZE 4

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};
/*
 * MlpNetwork class
 */
class MlpNetwork
{

private:
    Matrix w1;
    Matrix w2;
    Matrix w3;
    Matrix w4;
    Matrix b1;
    Matrix b2;
    Matrix b3;
    Matrix b4;

public:
    /*
     * MlpNetwork class constructor
     */
    MlpNetwork(Matrix weights[], Matrix biases[]);
    /*
     * parenthesis operator which activates the network by using the 4 layers.
     * @param input matrix fot this network
     * @return the digit that the network predicted after calculating all
     * layers.
     */
    digit operator()(Matrix &input);
};

#endif // MLPNETWORK_H
