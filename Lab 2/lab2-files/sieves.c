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
    // Sieve of Eratosthenes algorithm to find all prime numbers up to maxPrime
    // maxPrime states the max prime number values to be found

    char numbers[maxPrime + 1];                // local array represinting numbers from 0 to maxPrime
                                               // Using char to save memory, as we only need to store 0 or 
                                               // (n + 1) bytes of memory (not exceeding at most n + 8 bytes)
                                               // If we use int, it takes (4 * n) bytes of memory
    
    for(int i = 0; i <= maxPrime; i++){       // Initializing the array, first step of the algorithm
        numbers[i] = 1;                       // setting all numbers as 1, assuming all numbers are prime
    }


    for(int p = 2; p * p <= maxPrime; p++){   // Starting from the first prime number 2, second step of the algorithm  
        if(numbers[p] == 1){                  // If numbers[p] is still marked as prime
            for( int multiples = p * p; multiples <= maxPrime; multiples += p){
                numbers[multiples] = 0;       // Marking all multiples of p as non-prime, setting them to 0, crossing them out 
            }
        }
    }

    // Printing all prime numbers
    for(int i = 2; i <= maxPrime; i++){
        if(numbers[i] == 1){
            print_number(i);               // Printing the prime number using the print_number function
        }
    }
    printf("\n");         // Just printing a new line at the end 

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

 
