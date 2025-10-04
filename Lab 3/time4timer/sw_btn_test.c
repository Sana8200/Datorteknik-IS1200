
#include "hardware.h"
#include "tests.h"
#include "lib.h"


/* ============================== Lab 3 part f and g ================================ */
/*
 * sw_btn_test
 * An infinite loop to test switches and buttons.
 * - LEDs mirror the state of the switches.
 * - Pressing the button turns on an additional LED (LED9).
 * - The rightmost 7-segment display shows the value of the first 4 switches.
 */

void sw_btn_test(void){

    // Enter a forever loop
    while (1) {
    
    int switch_state = get_sw();         // getting the state of switch values 
    int push_btn_state = get_btn();      // getting the state of push button value (it's either 0 or 1)


    int led_value = switch_state;
    
    // If the button is pressed, use a bitwise OR to turn on the 9th LED without affecting the other LEDS
    // If we do the OR operator with for exmaple 0x300, LEDs 9 and 8 will turn on when pushing the button

    if (push_btn_state == 1){
      led_value = led_value | 0x200;
    }

    set_leds(led_value);
 
    // Setting the display to show the value of the first 4 switches (0-15)
    int display_value = switch_state & 0xF;
    
    set_display(0, display_value);
  }

}



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


