 

#include <stdio.h>

 
#include <stdlib.h>
#include <math.h>

#define INPUT_SIZE 784
#define HIDDEN_SIZE 128
#define OUTPUT_SIZE 10

#define e 2.71828

typedef struct {
    double w1[INPUT_SIZE][HIDDEN_SIZE];
    double b1[HIDDEN_SIZE];
    double w2[HIDDEN_SIZE][OUTPUT_SIZE];
    double b2[OUTPUT_SIZE];
} NeuralNetwork;

NeuralNetwork *init_network() {
    NeuralNetwork *nn = (NeuralNetwork*) malloc(sizeof(NeuralNetwork));

  
  
; The code is randomly initializing the weights of the first layer of a neural network.explain each line
; int i, j;
; This line declares two variables, i and j, which will be used as counters in the for loops.
; for (i = 0; i < INPUT_SIZE; i++) {
; This for loop will iterate through all of the inputs in the neural network.
; for (j = 0; j < HIDDEN_SIZE; j++) {
; This for loop will iterate through all of the hidden neurons in the neural network.
; nn->w1[i][j] = ((double) rand() / RAND_MAX) * 2 - 1;
; This line sets the weight between the input neuron at index i and the hidden neuron at index j to a random value between -1 and 1.
  
  
  
    int i, j;
    for (i = 0; i < INPUT_SIZE; i++) {
        for (j = 0; j < HIDDEN_SIZE; j++) {
            nn->w1[i][j] = ((double) rand() / RAND_MAX) * 2 - 1;
        }
    }
 
  
  
    for (i = 0; i < HIDDEN_SIZE; i++) {
        nn->b1[i] = 0;
        for (j = 0; j < OUTPUT_SIZE; j++) {
            nn->w2[i][j] = ((double) rand() / RAND_MAX) * 2 - 1;
        }
    }
    for (i = 0; i < OUTPUT_SIZE; i++) {
        nn->b2[i] = 0;
    }
    return nn;
}

void forward(NeuralNetwork *nn, double *input, double *output) {
    int i, j;
    double a1[HIDDEN_SIZE];
    for (i = 0; i < HIDDEN_SIZE; i++) {
        a1[i] = nn->b1[i];
        for (j = 0; j < INPUT_SIZE; j++) {
            a1[i] += nn->w1[j][i] * input[j];
        }
       a1[i] = 1 / (1 + pow(e, -a1[i]));  
    }
    
    for (i = 0; i < OUTPUT_SIZE; i++) {
        output[i] = nn->b2[i];
        for (j = 0; j < HIDDEN_SIZE; j++) {
            output[i] += nn->w2[j][i] * a1[j];
        }
        output[i] = 1 / (1 + pow(e, -output[i]));
    }
}

void train(NeuralNetwork *nn, double *input, double *target, double learning_rate) {
    int i, j;
    double output[OUTPUT_SIZE];
    double a1[HIDDEN_SIZE];
    double a2[OUTPUT_SIZE];
    double delta2[OUTPUT_SIZE];
    double delta1[HIDDEN_SIZE];
    double error = 0;
    
    forward(nn, input, output);
    
    for (i = 0; i < OUTPUT_SIZE; i++) {
        error = error + 0.5 * pow((target[i] - output[i]), 2);
        delta2[i] = output[i] - target[i];
    }
    
    for (i = 0; i < HIDDEN_SIZE; i++) {
        a1[i] = nn->b1[i];
        for (j = 0; j < INPUT_SIZE; j++) {
            a1[i] += nn->w1[j][i] * input[j];
        }
        a1[i] = 1 / (1 + pow(e, -a1[i]));
    }
    
    for (i = 0; i < HIDDEN_SIZE; i++) {
        delta1[i] = 0;
        for (j = 0; j < OUTPUT_SIZE; j++) {
            delta1[i] += nn->w2[i][j] * delta2[j];
        }
        delta1[i] *= a1[i] * (1 - a1[i]);
    }
    
    for (i = 0; i < INPUT_SIZE; i++) {
         for (j = 0; j < HIDDEN_SIZE; j++) {
            nn->w1[i][j] -= learning_rate * input[i] * delta1[j];
         }
    }
    
    for (i = 0; i < HIDDEN_SIZE; i++) {
        nn->b1[i] -= learning_rate * delta1[i];
    }
    
    for (i = 0; i < HIDDEN_SIZE; i++) {
        for (j = 0; j < OUTPUT_SIZE; j++) {
            nn->w2[i][j] -= learning_rate * a1[i] * delta2[j];
        }
    }
    
    for (i = 0; i < OUTPUT_SIZE; i++) {
        nn->b2[i] -= learning_rate * delta2[i];
    }
    
    printf("error: %f\n", error);
}

int main() {
    int i;
    double input[INPUT_SIZE];
    double target[OUTPUT_SIZE];
    NeuralNetwork *nn = init_network();
    for (i = 0; i < INPUT_SIZE; i++) {
        input[i] = 0;
    }
    target[0] = 1;
    while (1) {
        train(nn, input, target, 0.3);
        getchar();
    }
    return 0;
} 
