

#include "hardware.h"
#include "tests.h"
#include "lib.h"

/* ============================== Lab 3 part d ================================ */

/*
 * run_startup_sequence
 * This function runs a 16-second startup sequence, displaying a counter on the LEDs from 0 to 15.
 */
void run_start_sequence(void){
    for(int led_counter = 0 ; led_counter <= 15 ; led_counter++){

    time2string( textstring, mytime ); // Converts mytime to string
    display_string( textstring ); //Print out the string 'textstring'


    set_leds(led_counter);

    
    delay(3000);          // Delays 1 sec (adjust this value)
    tick( &mytime );     // Ticks the clock once

  }
}


  