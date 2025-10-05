
#include "hardware.h"
#include "tests.h"
#include "lib.h"
#include "timer.h"


/* ============================== Lab 3 part c assignment 2 ================================ */

/*
 * run_startup_sequence
 * This function runs a 16-second startup sequence, displaying a counter on the LEDs from 0 to 15.
 * this displays a binary counter from 0 to 15 on the LEDs
 * it is non blocking, and uses the hardware timer for precise one second intervals
 */
void run_start_sequence(void){

  //for(int led_counter = 0 ; led_counter <= 15 ; led_counter++){}  
  // Now instead of for loop, the counter will work base on the hardware's timer 

  int led_counter = 0;

  // A local software counter to count the 100ms hardware timouts 
  int timeoutcount = 0;

  set_leds(led_counter);

  while(led_counter < 16){
    if(*TIMER_STATUS & TIMER_STATUS_TO) {
      *TIMER_STATUS = TIMER_STATUS_TO;

      timeoutcount++;
 
      if(timeoutcount >= 10){
        timeoutcount = 0;

        time2string( textstring, mytime ); // Converts mytime to string
        display_string( textstring ); //Print out the string 'textstring'

        set_leds(led_counter);

        // delay(3000);          // Delays 1 sec (adjust this value)
        tick( &mytime );     // Ticks the clock once


        led_counter++;
      }
    }
  }
}
  