
/* main.c

   This file written 2024 by Artur Podobas and Pedro Antunes

   For copyright and licensing, see file COPYING */

/* Below functions are external and found in other files. */


#include "hardware.h"
#include "tests.h"
#include "lib.h"
#include "timer.h"

#define LED_TICK  0x01

int prime = 1234567;   
int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";

static int timeoutcount = 0;

/** 
 * @brief Sets the time on the six 7-segment displays.
 * 
 * Helper function
 */
void set_timer_display(int hours, int minutes, int seconds) {
    set_display(0, seconds % 10);        
    set_display(1, (seconds / 10) % 10); 
    set_display(2, minutes % 10);        
    set_display(3, (minutes / 10) % 10); 
    set_display(4, hours % 10);          
    set_display(5, (hours / 10) % 10);   
}


/**
 * @brief The Interrupt Service Routine (ISR).
 *
 * This function is automatically called by the processor every time the
 * hardware timer generates an interrupt (every 100ms). It must be very fast.
 */

void handle_interrupt(unsigned cause) {
  // Initializing static variables
  // These variable initialized only one and keep their values between calls 
  // This alllows the clock to remember the timer from one interrupt to the next 
  static int hours = 0;
  static int minutes = 0;
  static int seconds = 0;

  // Part (e): Acknowledge the interrupt by resetting the timer's timeout flag.
  *TIMER_STATUS = 0;

  // --- Clock Logic ---
  timeoutcount++;      // Incrementing the timeout counter 

  if(timeoutcount >= 10){         // If the timeout counter reached 10 (if 10 interrupts happend), start incrementing the time and applying the clock logic 
    timeoutcount = 0;
    seconds++;
    if(seconds >=60) { seconds = 0; minutes++; }
    if(minutes >= 60) { minutes = 0; hours++; }
    if(hours >= 24) { hours = 0; }

    // Part (d): Update displays and call tick().
    // Part (f): calling the display and tick functions once every 10 interrupts, it means once per second 
    set_timer_display(hours, minutes, seconds);
    tick( &mytime );
  }

  
}



/* Your code goes into main as well as any needed functions. */
int main() {

  labinit();
  
  while(1){
    print("Prime: ");
    prime = nextprime( prime );
    print_dec( prime );
    print("\n");
  }
  return 0;
}



