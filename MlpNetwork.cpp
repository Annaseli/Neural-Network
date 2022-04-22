//
// Created by anna_seli on 13/06/2021.
//
#include "MlpNetwork.h"

#define FINAL_DIM 10

/*
* MlpNetwork class constructor
*/
MlpNetwork::MlpNetwork(Matrix weights[], Matrix biases[])
{
    w1 = weights[0];
    w2 = weights[1];
    w3 = weights[2];
    w4 = weights[3];
    b1 = biases[0];
    b2 = biases[1];
    b3 = biases[2];
    b4 = biases[3];
}

/*
 * parenthesis operator which activates the network by using the 4 layers.
 * @param input matrix fot this network
 * @return the digit that the network predicted after calculating all layers
 */
digit MlpNetwork::operator()(Matrix &input)
{
    Dense dense1 (w1, b1, RELU);
    Matrix r1 = dense1(input);

    Dense dense2 (w2, b2, RELU);
    Matrix r2 = dense2(r1);

    Dense dense3 (w3, b3, RELU);
    Matrix r3 = dense3(r2);
    
    Dense dense4 (w4, b4, SOFTMAX);
    //Matrix r4 = dense4(dense3(dense2(dense1(input)))));
    Matrix r4 = dense4(r3);

    int max_index = 0;
    for (int i = 1; i < FINAL_DIM; i++)
    {
        if (r4.matrix_data[i] > r4.matrix_data[max_index])
        {
            max_index = i;
        }
    }

    digit d;
    d.value = max_index;
    d.probability = r4.matrix_data[max_index];
    return d;
}
