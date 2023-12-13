/***********************
 *  Perceptron Trainer *
 *  Version 1.0        *
 *  by Chin-Sung Lin   *
 *  Date: 01/22/2017   *
 ***********************/

#include <stdio.h>
#include <stdlib.h>     // definitions of rand(), srand() & RAND_MAX.
#include <math.h>       // definition of sqrt().
#include <time.h>       // definition of time().

#define LEARNING_RATE    0.1                                    // set learning rate.
#define MAX_ITERATION    100                                    // set the maximum no. of iterations to train the network.
#define MAX_PATTERN     1000                                    // set the maximum no. of training patterns

// function to create random floating point numbers
float randomFloat()
{
    return (float)rand() / (float)RAND_MAX;                     // get a pseudo random float between 0 .. 1 inclusive.
}

// function to evaluate summation and activation
int calculateOutput(float weights[], float SAT, float GPA, float ESSAY, float REC, float EXTRA) 
{
    float sum = SAT * weights[4] + GPA * weights[3] + ESSAY * weights[2] + REC * weights[1] + EXTRA * weights[0];   // summation function. sum of the inputs * weights and bias.
    return (sum >= 0) ? 1 : -1;                                 // activation, threshold or transfer function. output 1 if sum >= 0; output -1 otherwise (sign function).
}

int main(int argc, char *argv[])
{
    float SAT[MAX_PATTERN], GPA[MAX_PATTERN], ESSAY[MAX_PATTERN], REC[MAX_PATTERN], EXTRA[MAX_PATTERN], localError, globalError;
    int outputs[MAX_PATTERN], patternCount, i, p, iteration, output;
    
    FILE *fpatterns;                                            // declare input file pointer.
    FILE *fweights;                                             // declare weight file pointer.
    
    // time() function returns the value of time in seconds.
    // Seeds the pseudo-random number generator used by rand() with the value seed.
    // If rand() is used before any calls to srand(), rand() behaves as if it was seeded with srand(1).
    // Each time rand() is seeded with the same seed, it must produce the same sequence of values.
    
    srand((unsigned int)time(NULL));                            // get a distinct seed each time, only need to call it once, not before each time you call rand().
    
    fweights = fopen("data.txt", "w");                       // open weights file, the training results, the coefficients of linear function (decision boundary).
    
    if ((fpatterns = fopen("data.txt", "r")) == NULL)      // open training data file.
    {
        printf("Cannot open file.\n");
        exit(1);                                                // stop program if can not open training file.
    }
    
    p = 0;                                                      // initialize pattern index.
    while (fscanf(fpatterns, "%f %f %f %f %f", &SAT[p], &GPA[p], &ESSAY[p], &REC[p], &EXTRA[p]) != EOF) // reading training data one by one till the end of file, and store them in arrays.
    {
        if (outputs[p] == 0)
            outputs[p] = -1;                                    // change the output value to 1 and -1 instead of 0 and 1 (sign function instead of step function.
        p++;                                                    // increment pattern index.
    }
    patternCount = p;                                           // record no. of training data.
    printf("\nNumber of training patterns: %d\n", patternCount);    // print out the number of training file.
     
    weights[4] = randomFloat();     // initialize weights with random values between 0 and 1.
    weights[3] = randomFloat();
    weights[2] = randomFloat();
    weights[1] = randomFloat();
    weights[0] = randomFloat();
    
    printf("\n              ");
    printf("Initial weights : w4 = %8.4f w3 = %8.4f w2 = %8.4f w1 = %8.4f w0 = %8.4f \n", weights[4], weights[3], weights[2], weights[1], weights[0]);    // print out initial weights.
    
    iteration = 0;                                              // intialize iteration.
    do
    {                                                           // do loop.
        iteration++;                                            // increment iteration.
        globalError = 0;                                        // initialize global error.
        for (i = 0; i < patternCount; i++) {                    // for each iteration, run through all training pattrens.
            output = calculateOutput(weights, SAT[i], GPA[i], ESSAY[i], REC[i], EXTRA[i]);      // calculate output (1 or -1) by giving inputs and weights.
            localError = outputs[i] - output;                   // calculate local error, the output for each pattern.
            weights[4] += LEARNING_RATE * localError * SAT[i];  // updating weight based on learning rate, local errors, and inputs. KEY FOR PERCEPTRON LEARNING AND IMPROVING
            weights[3] += LEARNING_RATE * localError * GPA[i];
            weights[2] += LEARNING_RATE * localError * ESSAY[i];
            weights[1] += LEARNING_RATE * localError * REC[i];
            weights[0] += LEARNING_RATE * localError * EXTRA[i];
            
            globalError += (localError*localError);             // accumulate golbal errors by adding  squared local error.
        }
        
        /* Root Mean Squared Error */
        printf("\nIteration %d : RMSE = %.4f          ", iteration, sqrt(globalError/patternCount));                    // print out root mean square global error.
        printf("Training weights: w4 = %8.4f w3 = %8.4f w2 = %8.4f w1 = %8.4f w0 = %8.4f \n", weights[4], weights[3], weights[2], weights[1], weights[0]);            // print out updated weights.
        
    } while (globalError != 0 && iteration < MAX_ITERATION);     // loop ends if global error equals to 0 (linearly seperable) or iterations execeeds the maximum number.
    
    printf("\nDecision boundary (linear) equation: %.2f*SAT + %.2f*GPA + %.2f*ESSAY + %.2f*REC + %.2f*EXTRA = 0\n" weights[4], weights[3], weights[2], weights[1], weights[0]);    // print out the trained network weights.
    fprintf(fweights, "%.4f %.4f %.4f %.4f %.4f\n", weights[4], weights[3], weights[2], weights[1], weights[0]);
    
    return 0;
}
//purpose of training is to find weights