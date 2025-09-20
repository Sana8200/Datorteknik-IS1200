

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


/*
void print_sieves(int maxPrime){
    // Sieve of Eratosthenes algorithm 

    char *numbers;   
    numbers = (char*) malloc((maxPrime + 1));            
                                                       
    for(int i = 0; i <= maxPrime; i++){       
        numbers[i] = 1;                       
    }

    for(int p = 2; p * p <= maxPrime; p++){   
        if(numbers[p] == 1){                  
            for( int multiples = p * p; multiples <= maxPrime; multiples += p){
                numbers[multiples] = 0;        
            }
        }
    }

    for(int i = 2; i <= maxPrime; i++){    
        if(numbers[i] == 1){
            print_number(i);               
        }
    }

    free(numbers);        

    printf("\n");        
}
*/


void mean_sieves(int maxPrime){
    // The function computes and prints the mean of all prime numbers up to maxPrime 
    
    // Sieve of Eratosthenes algorithm
    char *numbers;   
    numbers = (char*) malloc((maxPrime + 1));            
                                                       
    for(int i = 0; i <= maxPrime; i++){       
        numbers[i] = 1;                       
    }

    for(int p = 2; p * p <= maxPrime; p++){   
        if(numbers[p] == 1){                  
            for( int multiples = p * p ; multiples <= maxPrime; multiples += p){
                numbers[multiples] = 0;        
            }
        }
    }

    for(int i = 2; i <= maxPrime; i++){    
        if(numbers[i] == 1){
            print_number(i);               
        }
    }
    printf("\n");


      

    // Calculating the mean of all prime numbers found
    // Summing all the numbers and then divide that by the count of prime numbers founf 

    long long sum = 0;       // long long for large numbers and preventing overflow, because it can be very large if maxPrime is large
    int count = 0;     // Number of primes found 

    for(int i = 2; i <= maxPrime; i++){    
        if(numbers[i] == 1){
            sum += i;               // adding all the prime numbers sum = sum + i 
            count++;          // Counting the number of primes found, incrementing the count primes by 1 each time a prime is found 
        }
    }

    if(count){ 
        double mean = (double) sum / count;     // Calculating the mean 

        printf("\nMean value of all prime numbers between a 1 and N (maxPrime):\t%f\n", mean);
        
    }
    else{
        printf("No prime numbers found.\n");
    }
    
    free(numbers);  

}






int main(int argc, char *argv[]){
    if(argc == 2)
    {
        // print_sieves(atoi(argv[1]));
        mean_sieves(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}
