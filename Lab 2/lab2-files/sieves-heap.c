#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6


void print_number(int n){            

  printf("%10d ", n);                

  static int col_count = 0;          
  col_count++;                      

  if (col_count >= COLUMNS) {        
      printf("\n");                  
      col_count = 0;                
  }
}



void print_sieves(int maxPrime){
    // Sieve of Eratosthenes algorithm 

    char *numbers;      // Pointer to hold the dynamically allocated array   

    // Dynamically allocating memory for the array to handle larger values of maxPrime without stack overflow
    // This is especially useful for large values of maxPrime, where stack memory might be insufficient
    // Dynamic memory allocation allows us to use heap memory, which is generally larger than stack memory
    
    numbers = (char*) malloc((maxPrime + 1) * sizeof(char));            // Dynamically allocate memory for the array  
                                                                        // (maxPrime + 1) to include the number maxPrime itself
    // Different system differs in the size of char, int, etc so we need to include sizeof to make it portable across systems


    /*
    if (numbers == NULL) {                                           // Check if memory allocation was successful
        fprintf(stderr, "Memory allocation failed\n");
        return;                                                      // Exit the function if allocation fails
    }
    */

    

    for(int i = 0; i <= maxPrime; i++){       
        numbers[i] = 1;                       
    }

    for(int p = 2; p * p <= maxPrime; p++){   
        if(numbers[p] == 1){                  
            for( int multiples = p * p; multiples <= maxPrime; multiples += p){
                numbers[multiples] = 0;        // Crossing out process
            }
        }
    }

    for(int i = 2; i <= maxPrime; i++){     // Printing prime numbers 
        if(numbers[i] == 1){
            print_number(i);               
        }
    }

    free(numbers);        // Freeing the dynamically allocated memory to prevent memory leaks

    printf("\n");        
}



int main(int argc, char *argv[]){
    if(argc == 2)
    {
        print_sieves(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}
