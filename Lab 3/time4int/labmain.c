/* main.c

   This file written 2024 by Artur Podobas and Pedro Antunes

   For copyright and licensing, see file COPYING */

/* Below functions are external and found in other files. */

#include "hardware.h"
#include "tests.h"
#include "lib.h"
#include "timer.h"

int prime = 1234567;
int mytime = 0x1059;
char textstring[] = "text, more text, and even more text!";
int timeoutcount = 0; // Global timeout counter variable




int main()
{
  labinit();
  while (1)
  {
    // The main loop just prints prime numbers. All display logic is handledby the interrupt routines.
    print("Prime: ");
    prime = nextprime(prime);
    print_dec(prime);
    print("\n");
  }
}
