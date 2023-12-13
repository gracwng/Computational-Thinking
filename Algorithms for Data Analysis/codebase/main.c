// Read / Write Strings and Integers from / to Files
#include <stdio.h>
#define FILESIZE 2000
#define STRINGLENGTH 20

int main()
{
    FILE* fileInput = NULL;
    FILE* fileOutput = NULL;
    FILE* fileOutput2 = NULL;
    /*data fields such as last names, first names, positions, states, ages, salaries, education levels, and years of industrial experience will be provided.*/
    char last[FILESIZE][STRINGLENGTH]; 
    char first[FILESIZE][STRINGLENGTH]; 
    char position[FILESIZE][STRINGLENGTH]; 
    char state[FILESIZE][STRINGLENGTH];
    int age[FILESIZE]; 
    int salary[FILESIZE]; 
    char education[FILESIZE][STRINGLENGTH];
    int experience[FILESIZE]; 
    int i; 
    int j;
    int array[FILESIZE];
  
    
    fileInput = fopen("Employee_2021-22.txt", "r");
    fileOutput = fopen("output.txt", "w");  
    for (i = 0; i < FILESIZE; i++)
        fscanf (fileInput, "%s %s %s %s %d %d %s %d", last[i], first[i], position[i], state[i], &age[i], &salary[i], education[i], &experience[i]);
    
//(1) Create a sorted employee data file based on the descending order of their first names.
    char temp[STRINGLENGTH];
    int temps;
    for (i = 0; i < FILESIZE-1; i++)
    for (j = i+1; j < FILESIZE; j++)
      if (strcmp(first[i], first[j]) < 0)
      {
        strcpy(temp, first[i]);
        strcpy(first[i], first[j]);
        strcpy(first[j], temp);
        
        strcpy(temp, last[i]);
        strcpy(last[i], last[j]);
        strcpy(last[j], temp);

        strcpy(temp, position[i]);
        strcpy(position[i], position[j]);
        strcpy(position[j], temp);

        strcpy(temp, state[i]);
        strcpy(state[i], state[j]);
        strcpy(state[j], temp);
    
        temps = age[i];
        age[i] = age[j];
        age[j] = temps;

        temps = salary[i];
        salary[i] = salary[j];
        salary[j] = temps;

        strcpy(temp, education[i]);
        strcpy(education[i], education[j]);
        strcpy(education[j], temp);

        temps = experience[i];
        experience[i] = experience[j];
        experience[j] = temps;

      }
    
    for (i = 0; i < FILESIZE; i++)
        //fprintf(fileOutput, "%18s first[%d] = %18s position[%d] = %18s state[%d] = %18s     age[%d] = %3d\n\n salary[%d] = %3d\n\n  education[%d] = %18s experience[%d] = %3d\n\n ", i, last[i], i, first[i], i, position[i], i, state[i], i, age[i], i, salary[i], i, education[i], i, experience[i]);
        fprintf(fileOutput, "%13s \t%13s \t%13s \t%5s \t%3d \t%3d \t%13s \t%3d\n ", last[i], first[i], position[i],state[i], age[i], salary[i], education[i], experience[i]);

//(2) Print the data of top 5 highest salary managers.

    for (i = 0; i < FILESIZE-1; i++)
    for (j = i+1; j < FILESIZE; j++)
    if(salary[i] < salary[j])
      {
        strcpy(temp, first[i]);
        strcpy(first[i], first[j]);
        strcpy(first[j], temp);
        
        strcpy(temp, last[i]);
        strcpy(last[i], last[j]);
        strcpy(last[j], temp);

        strcpy(temp, position[i]);
        strcpy(position[i], position[j]);
        strcpy(position[j], temp);

        strcpy(temp, state[i]);
        strcpy(state[i], state[j]);
        strcpy(state[j], temp);
    
        temps = age[i];
        age[i] = age[j];
        age[j] = temps;

        temps = salary[i];
        salary[i] = salary[j];
        salary[j] = temps;

        strcpy(temp, education[i]);
        strcpy(education[i], education[j]);
        strcpy(education[j], temp);

        temps = experience[i];
        experience[i] = experience[j];
        experience[j] = temps;

      }
    //for (i = 0; i < FILESIZE; i++)
    //  fprintf(fileOutput2, "%13s \t%13s \t%13s \t%5s \t%3d \t%3d \t%13s \t%3d\n ", last[i], first[i], position[i],state[i], age[i], salary[i], education[i], experience[i]);

/*// Linear Search
int LinearSearch (int key, int a[], int array_size)
{*/ printf("(2) Top 5 highest salary managers:\n");

    int count = 0;
  // for(found = 0; found <=5; found++)
      for(i = 0; i < FILESIZE; i++)
        if (count > 4){
          break;
        }
        else if (strcmp(position[i], "Manager") == 0)
        {
            count += 1;

            //printf("position[%d] = %s\n\n", i, position[i]);
            printf( " position[%d] = %s %s %s %s %d %d %s %d\n ", i, last[i], first[i], position[i],state[i], age[i], salary[i], education[i], experience[i]);

        }

//(3) Find the data of an employee whose first name is Elon and he is a manager.
printf("\n\n");
   for(i = 0; i < FILESIZE; i++)
      if (strcmp(position[i], "Manager") == 0)
        if (strcmp(first[i], "Elon") == 0)
        {printf("(3)Find the data of an employee whose first name is Elon and he is a manager:\n position[%d] = %s %s %s %s %d %d %s %d\n ", i, last[i], first[i], position[i],state[i], age[i], salary[i], education[i], experience[i]);}
    
printf("\n\n");
//(4) Compare the average salaries of employees in Hawaii and Maryland.
  int popSum = 0, salSum = 0;
  float average;
  for(i = 0; i < FILESIZE; i++){
    if (strcmp(state[i], "HI") == 0){
      popSum = popSum + 1;
      salSum = salSum + salary[i];
    }
    else { 
      continue;
    } 
  }
    printf("(4) The average salary of employees in Hawaii is: %.2f\n", (float)salSum/popSum);

int popSums = 0, salSums = 0;
  float averages;
  for(i = 0; i < FILESIZE; i++){
    if (strcmp(state[i], "MD") == 0){
      popSums = popSums + 1;
      salSums = salSums + salary[i];
    }
    else { 
      continue;
    } 
  }
    printf("The average salary of employees in Maryland is: %.2f\n", (float)salSums/popSums);


    fprintf(fileOutput, "\n\n");
    fclose(fileInput);
    fclose(fileOutput);

    
}