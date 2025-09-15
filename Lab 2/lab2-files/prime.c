/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
  if (n <= 1) {
    return 0;    // Numbers less than or equal to 1 are not prime.
  }
  
  if (n == 2){
    return 1;    // 2 is the only even prime number.
  }

  if (n % 2 == 0){
    return 0;    // Other even numbers are not prime.
  }
  
  for (int i = 2; i * i <= n; i++) {    // Check divisors from 2 to sqrt(n)
     if (n % i == 0) {
      return 0;  // Found a divisor, so n is not prime.
  
    return 0;
}
int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
  return 0;
}

