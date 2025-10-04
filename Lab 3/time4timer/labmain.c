
/* main.c

   This file written 2024 by Artur Podobas and Pedro Antunes

   For copyright and licensing, see file COPYING */

/* Below functions are external and found in other files. */


#include "hardware.h"
#include "tests.h"
#include "clock.h"
#include "lib.h"
#include "timer.h"


int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";


/* Below is the function that will be called when an interrupt is triggered. */
void handle_interrupt(unsigned cause) 
{}




/* Your code goes into main as well as any needed functions. */
int main() {

  // Call labinit()
  labinit();

  // run_start_sequence();
  set_leds(0);

  clock_timer();



  return 0;
}



