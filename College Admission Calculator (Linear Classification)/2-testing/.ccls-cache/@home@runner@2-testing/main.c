/**************************
 *  Perceptron Classifier *
 *  Version 1.0           *
 *  by Chin-Sung Lin      *
 *  Date: 01/22/2017      *
 **************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_PATTERN     200                                    // set the maximum no. of training patterns

int calculateOutput(float weights[], float SAT, float GPA, float ESSAY, float REC, float EXTRA) 

{
    float sum = SAT * weights[5] + GPA * weights[4] + ESSAY * weights[3] + REC * weights[2] + EXTRA * weights[1] + weights[0];   // summation function. sum of the inputs * weights and bias.
    return (sum >= 0) ? 1 : 0;        
}

int main(int argc, char *argv[])
{
    float SAT[MAX_PATTERN], GPA[MAX_PATTERN], ESSAY[MAX_PATTERN], REC[MAX_PATTERN], EXTRA[MAX_PATTERN], errorRate, weights[6];
    int outputs[MAX_PATTERN], patternCount, i, p, iteration, output, errorCount, label[MAX_PATTERN];
    int classes;
    char result;
    FILE *fpatterns;
    FILE *fweights;
    FILE *fresult;
      

    fweights = fopen("weights.txt", "r");                     
    fresult = fopen("testing_output.txt", "w");
    fpatterns = fopen("testing.txt", "r"); 
  
    fscanf(fweights, "%f %f %f %f %f %f\n", &weights[5], &weights[4], &weights[3], &weights[2], &weights[1], &weights[0]);
 
    p = 0;
    while (fscanf(fpatterns, "%f %f %f %f %f %c", &SAT[p], &GPA[p], &ESSAY[p], &REC[p], &EXTRA[p], &result) != EOF)
    {
       SAT[p] = (SAT[p] - 1200)/40;
        GPA[p] = GPA[p]*2.5;
        label[p] = (result == 'A')? 1: 0;  
        p++;
    }
    patternCount = p;

    fprintf(fresult, "\nNumber of testing patterns: %d\n", patternCount);
    fprintf(fresult, "\nDecision boundary (line) equation: %.5f + %.5f + %.5f + %.5f + %.5f + %.5f = 0\n\n", weights[5], weights[4], weights[3], weights[2], weights[1], weights[0]);

    errorCount = 0;
    for (i = 0; i < patternCount; i++) {
        output =  calculateOutput(weights, SAT[i], GPA[i], ESSAY[i], REC[i], EXTRA[i]);
     // result = (output == 1)?'A':'R';
     fprintf(fresult, "SAT = %f   GPA = %f ESSAY = %f REC = %f EXTRA = %f  label = %d   class = %d   ", SAT[i], GPA[i], ESSAY[i], REC[i], EXTRA[i], label[i], output);
        if (output != label[i])
        {
          fprintf(fresult, "*** ERR\n");
          errorCount++;
        }
        else
          fprintf(fresult, "\n");
    }

  fprintf(fresult, "\nError =  %.2f %%\n", (float)errorCount/(float)patternCount*100.);      // print out calculated error rate.
    
  }