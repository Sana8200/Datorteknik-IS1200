/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){

  if (n <= 1) {
    return 0;          // Numbers less than or equal to 1 are not prime.
  }
  
  if (n == 2){
    return 1;          // 2 is the only even prime number.
  }

  if (n % 2 == 0){
    return 0;          // Other even numbers larger than 2 are not prime. 
  }
 
  for (int i = 3; i < n; i += 2) {       // Checking odd numbers larger than 2 
     if (n % i == 0) {                   // If n is divisible by i, it is not prime.
      return 0;
     }
  }

/*
for (int i = 3; i * i <= n; i += 2) {           // Check only odd numbers from 3 to sqrt(n), more efficent 
                                                // No need to check even numbers or numbers greater than sqrt(n)
    if (n % i == 0) {
        return 0; // n is divisible by i, so it is not prime
    }
}
*/

  return 1;                              // If no divisors were found, the number is prime.
}


int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
  return 0;
}




