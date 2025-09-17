/*
 print-primes.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

void print_number(int n);  // Function prototype for print_number

int is_prime(int n){     
  // Returns 1 if n is prime, returns 0 if n is not prime.

  if (n <= 1) {
    return 0;          
  }
  
  if (n == 2){
    return 1;          
  }

  if (n % 2 == 0){
    return 0;          
  }
 
for (int i = 3; i * i <= n; i += 2) {           
                                                
    if (n % i == 0) {
        return 0; 
    }
}
  return 1;                              
}


void print_number(int n){            // Column formatter function

  printf("%10d ", n);                // Print the number with a width of 10 characters

  static int col_count = 0;          // Static variable to keep track of the current column count
  col_count++;                       // Increment the column count

  if (col_count >= COLUMNS) {        // If we've reached the defined number of columns which is 6 
      printf("\n");                  // Print a newline
      col_count = 0;                 // Reset the column count for the next row 
  }
  // If col_count is less than COLUMNS, do nothing and continue printing in the same row
}





void print_primes(int n){                  
    // The function to manage the whole process of finding and printing the functions in columns 

    // Should print out all prime numbers less than 'n'
    // with the following formatting. Note that the number of columns is stated in the define COLUMNS

    for(int i = 2 ; i <= n ; i++){
      if(is_prime(i)){
        print_number(i);
      }
    }
    printf("\n");     // Just printing a new line at the end for better output formatting
}



// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
    if(argc == 2)
    {
        print_primes(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}

 
