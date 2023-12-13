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

#define LEARNING_RATE     0.0001 
#define MAX_ITERATION     10000     
#define MAX_PATTERN       800                                    

// function to create random floating point numbers
float randomFloat()
{
    return (float)rand() / (float)RAND_MAX;                     // get a pseudo random float between 0 .. 1 inclusive.
}

// function to evaluate summation and activation
int calculateOutput(float weights[], float SAT, float GPA, float ESSAY, float REC, float EXTRA) 
{
    float sum = SAT * weights[5] + GPA * weights[4] + ESSAY * weights[3] + REC * weights[2] + EXTRA * weights[1] + weights[0];   // summation function. sum of the inputs * weights and bias.
    return (sum >= 0) ? 1 : 0;                                 // activation, threshold or transfer function. output 1 if sum >= 0; output -1 otherwise (sign function).
}

int main(int argc, char *argv[])
{
    float SAT[MAX_PATTERN], GPA[MAX_PATTERN], ESSAY[MAX_PATTERN], REC[MAX_PATTERN], EXTRA[MAX_PATTERN], errorRate, weights[6], errorCount;
    int outputs[MAX_PATTERN], patternCount, i, p, iteration, output;
    char result;
  
    FILE *fpatterns;                                            // declare input file pointer.
    FILE *fweights; 
    FILE *ferror;    // declare weight file pointer.
    FILE *fresult;
    // time() function returns the value of time in seconds.
    // Seeds the pseudo-random number generator used by rand() with the value seed.
    // If rand() is used before any calls to srand(), rand() behaves as if it was seeded with srand(1).
    // Each time rand() is seeded with the same seed, it must produce the same sequence of values.
    
    srand((unsigned int)time(NULL));                            // get a distinct seed each time, only need to call it once, not before each time you call rand().
    
    fweights = fopen("weights.txt", "w");                       // open weights file, the training results, the coefficients of linear function (decision boundary).
    ferror = fopen("errors.txt", "w");
    fresult = fopen("training_output.txt", "w");
    if ((fpatterns = fopen("data.txt", "r")) == NULL)      // open training data file.
    {
        printf("Cannot open file.\n");
        exit(1);                                                // stop program if can not open training file.
    }
    
    p = 0;                                                      // initialize pattern index.
    while (fscanf(fpatterns, "%f %f %f %f %f %c", &SAT[p], &GPA[p], &ESSAY[p], &REC[p], &EXTRA[p], &result) != EOF) // reading training data one by one till the end of file, and store them in arrays.
    {
        if (result == 'A')
            outputs[p] = 1;  
        else 
          outputs[p] = 0;  

        SAT[p] = (SAT[p] - 1200)/40;
        GPA[p] = GPA[p]*2.5;
        p++;                                                    // increment pattern index.
    }
    patternCount = p;                                           // record no. of training data.
    fprintf(fresult, "\nNumber of training patterns: %d\n", patternCount);    // print out the number of training file.

    weights[5] = randomFloat()*10;
    weights[4] = randomFloat()*10;     // initialize weights with random values between 0 and 1.
    weights[3] = randomFloat()*10;
    weights[2] = randomFloat()*10;
    weights[1] = randomFloat()*10;
    weights[0] = randomFloat()*10;
    
    fprintf(fresult, "\nInitial weights : w5 = %8.4f w4 = %8.4f w3 = %8.4f w2 = %8.4f w1 = %8.4f w0 = %8.4f \n", weights[5], weights[4], weights[3], weights[2], weights[1], weights[0]);    // print out initial weights.
    
    iteration = 0;    // intialize iteration.
    errorRate = 50;
    do
    {                                                           // do loop.
        iteration++;  
        errorCount = 0;      

        for (i = 0; i < patternCount; i++) {                    // for each iteration, run through all training pattrens.
            p = (int) (rand()*(float)(MAX_PATTERN-1) / (float)RAND_MAX); 
            output = calculateOutput(weights, SAT[p], GPA[p], ESSAY[p], REC[p], EXTRA[p]);      // calculate output (1 or -1) by giving inputs and weights.
            if (outputs[p] < output)
              {
                weights[5] -= LEARNING_RATE * SAT[p];  
                weights[4] -= LEARNING_RATE * GPA[p];  // updating weight based on learning rate, local errors, and inputs. KEY FOR PERCEPTRON LEARNING AND IMPROVING
                weights[3] -= LEARNING_RATE * ESSAY[p];
                weights[2] -= LEARNING_RATE * REC[p];
                weights[1] -= LEARNING_RATE * EXTRA[p];
                weights[0] -= LEARNING_RATE;
                errorCount++;
              }
            else if (outputs[p] > output)
              {
                weights[5] += LEARNING_RATE * SAT[p];  
                weights[4] += LEARNING_RATE * GPA[p];  // updating weight based on learning rate, local errors, and inputs. 
                weights[3] += LEARNING_RATE * ESSAY[p];
                weights[2] += LEARNING_RATE * REC[p];
                weights[1] += LEARNING_RATE * EXTRA[p];
                weights[0] += LEARNING_RATE;
                errorCount++;
              }
        }
        errorRate = errorCount/8;             // accumulate golbal errors by adding  squared local error.

        /* Root Mean Squared Error */
                            
        fprintf(fresult, "Training weights: w5 = %8.4f w4 = %8.4f w3 = %8.4f w2 = %8.4f w1 = %8.4f w0 = %8.4f ", weights[5], weights[4], weights[3], weights[2], weights[1], weights[0]);         
        fprintf(fresult, "Iteration %d: Error Rate = %2.2f%%\n", iteration, errorRate);  
        fprintf(ferror, "%2.2f%%\n", errorRate);  

    } while (errorRate != 0 && iteration < MAX_ITERATION);     // loop ends if global error equals to 0 (linearly seperable) or iterations execeeds the maximum number.
    
    fprintf(fresult, "\nDecision boundary (linear) equation: %.5f + %.5f + %.5f + %.5f + %.5f + %.5f = 0\n", weights[5], weights[4], weights[3], weights[2], weights[1], weights[0]);    // print out the trained network weights.
    fprintf(fweights, "%.5f %.5f %.5f %.5f %.5f %.5f\n", weights[5], weights[4], weights[3], weights[2], weights[1], weights[0]);
    
    return 0;
}
//purpose of training is to find weights

// WEIGHTS.TXT MAKE SURE NUMBERS GOING 6