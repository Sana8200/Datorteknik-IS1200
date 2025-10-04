
/* main.c

   This file written 2024 by Artur Podobas and Pedro Antunes

   For copyright and licensing, see file COPYING */

/* Below functions are external and found in other files. */


#include "hardware.h"
#include "tests.h"
#include "clock.h"
#include "lib.h"


int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";


/* Below is the function that will be called when an interrupt is triggered. */
void handle_interrupt(unsigned cause) 
{}


/* Add your code here for initializing interrupts. */
void labinit(void)
{}



/* Your code goes into main as well as any needed functions. */
int main() {

  // Call labinit()
  labinit();


  /* ============================== Lab 3 part d ================================ */
  run_start_sequence();
 

  /* ============================== Lab 3 part h ================================ */
  clock();



  /* ============================== Lab 3 part e ================================ */
  // set_display(0, 5);
  

  /* ============================== Lab 3 part f and g ================================ */
  // sw_btn_test();

  return 0;
}



