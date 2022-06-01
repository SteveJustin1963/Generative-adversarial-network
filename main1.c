 

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
; this is for loop which iterates for every node in hidden layer
; initialize bias of hidden layer nodes to 0
; for every hidden layer node, we have to initialize weights for every node in output layer
; the weights are initialized randomly between -1 and 1
 ;
 ; 
  
    for (i = 0; i < HIDDEN_SIZE; i++) {
        nn->b1[i] = 0;
        for (j = 0; j < OUTPUT_SIZE; j++) {
            nn->w2[i][j] = ((double) rand() / RAND_MAX) * 2 - 1;
        }
    }
 ; This line is creating a for loop that is going to iterate through the output size. 
 ; The output size is going to be the number of neurons in the second layer. 
 ; The variable i is going to be used as the iterator in this for loop. 
 ; The initial value of i will be 0 and will be incremented by 1 until it reaches the output size. 
 ; The purpose of this loop is to initialize the array of biases for the second layer of the neural network. 
 ; The array of biases is going to be set to 0 for all of the neurons in the second layer.
 
 
    for (i = 0; i < OUTPUT_SIZE; i++) {
        nn->b2[i] = 0;
    }
    return nn;
}
; This is the forward function for a neural network. The function takes in the neural network, 
 an input, and an output. The function then creates an array called a1 which is the size of the hidden layer. 
  The function then loops through the hidden layer and calculates the value at each node. 
  The value is calculated by taking the bias at that node, adding the product of each weight and input, 
 and then running it through a sigmoid function. The output of the hidden layer is then stored in the output array.
 
 
 
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
    
 
 
 
 ; This is the activation function for the output layer. 
  The activation function is 1 / (1 + pow(e, -output[i])). This is the sigmoid function.
  This for loop is iterating through the output layer. 
   The output at each node is equal to the bias of the node plus the sum of each weight 
   times the activation of the node in the previous layer. 
   Finally, the output is passed through an activation function.
   
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
    
 ; The for loop iterates through the output array
; The error variable stores the value of the difference between the target and output arrays
; The delta2 variable stores the value of the output array minus the target array
 
    for (i = 0; i < OUTPUT_SIZE; i++) {
        error = error + 0.5 * pow((target[i] - output[i]), 2);
        delta2[i] = output[i] - target[i];
     
     
    }
    
 
 ; This is the first layer of the neural network. 
  The purpose of this layer is to take in the input values and pass them through to the next layer. 
  The 'for' loop is iterating through each node in the hidden layer, 
 and the 'if' statement is checking to see if the node is connected to the input node. 
  If it is, it will take the weight of the connection and multiply it by the input value.
  
  
    for (i = 0; i < HIDDEN_SIZE; i++) {
        a1[i] = nn->b1[i];
        for (j = 0; j < INPUT_SIZE; j++) {
            a1[i] += nn->w1[j][i] * input[j];
        }
        a1[i] = 1 / (1 + pow(e, -a1[i]));
    }
    
 ;
 
 ;This for loop is for backpropagation. 
  The first for loop is for the hidden layer weights and the second for loop is for the output layer weights. 
   The delta1 array is for the hidden layer and the delta2 array is for the output layer. 
    The a1 array is for the hidden layer activation and the a2 array is for the output layer activation.
     
     
    for (i = 0; i < HIDDEN_SIZE; i++) {
        delta1[i] = 0;
        for (j = 0; j < OUTPUT_SIZE; j++) {
            delta1[i] += nn->w2[i][j] * delta2[j];
        }
        delta1[i] *= a1[i] * (1 - a1[i]);
    }
  ; This code is implementing the backpropagation algorithm. 
   The outer for loop is iterating through the input neurons, and the inner for loop is iterating through the hidden layer neurons. 
    For each input-hidden neuron pair, the code is adjusting the weight between them according to the backpropagation formula:
weight = weight - (learning rate * input * delta)
where delta is the error gradient for the neuron in the hidden layer.  

 
 
    for (i = 0; i < INPUT_SIZE; i++) {
         for (j = 0; j < HIDDEN_SIZE; j++) {
            nn->w1[i][j] -= learning_rate * input[i] * delta1[j];
         }
    }
    
 ;
 ; The code above is iterating through the hidden layer weights 
  and updating them based on the learning rate and the corresponding delta value.
  
  for (i = 0; i < HIDDEN_SIZE; i++) {
        nn->b1[i] -= learning_rate * delta1[i];
    }
    
 ;
; The code above iterates through the hidden layer and the output layer. 
 For each node in the hidden layer, it subtracts the learning rate 
 multiplied by the activation of that node in the hidden layer and the error in the output layer. 
 This gives us the new weight for each node in the hidden layer. 
 
  
  for (i = 0; i < HIDDEN_SIZE; i++) {
        for (j = 0; j < OUTPUT_SIZE; j++) {
            nn->w2[i][j] -= learning_rate * a1[i] * delta2[j];
        }
    }
   
 ; 
 
 ; The first line of code is a for loop that iterates through the entire array of output values. 
  The second line subtracts the learning rate from the output value. 
  The third line prints the error value to the console.
 
    for (i = 0; i < OUTPUT_SIZE; i++) {
        nn->b2[i] -= learning_rate * delta2[i];
    }
    
    printf("error: %f\n", error);
}

; 
 

int main() {
    //this is the main function of the program that contains all the other functions
    int i;
    //i is defined as an integer
    double input[INPUT_SIZE];
    double target[OUTPUT_SIZE];
    //input and target are both defined as double arrays of size INPUT_SIZE and OUTPUT_SIZE
    NeuralNetwork *nn = init_network();
    //nn is defined as a pointer to a NeuralNetwork struct and is initialized
    for (i = 0; i < INPUT_SIZE; i++) {
        input[i] = 0;
    }
    target[0] = 1;
    //the input and target arrays are both set to 0 and 1 respectively
    while (1) {
        train(nn, input, target, 0.3);
        getchar();
    }
    //the train function is called with the nn, input, target, and 0.3 parameters and the getchar function is also called
    return 0;
} 
