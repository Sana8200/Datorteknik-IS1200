
#include "hardware.h"
#include "lib.h"

/* ============================== Lab 3 part h ================================ */


/*
 * set_timer_displays
 * This function takes hours, minutes, and seconds and displays them across the six 7-segment displays.
 * Displays 5 & 4: Hours
 * Displays 3 & 2: Minutes
 * Displays 1 & 0: Seconds
 */
void set_timer_display(int hours, int minutes, int seconds) {
    // Display seconds (rightmost two displays: 0 and 1)
    set_display(0, seconds % 10);        
    set_display(1, (seconds / 10) % 10); 

    // Display minutes (middle two displays: 2 and 3)
    set_display(2, minutes % 10);        
    set_display(3, (minutes / 10) % 10); 

    // Display hours (leftmost two displays: 4 and 5)
    set_display(4, hours % 10);          
    set_display(5, (hours / 10) % 10);   
    
}
/*
  To display a number like 36, we isolate each digit. We get the ones digit (6) using the modulo operator (36 % 10), 
  and the tens digit (3) using integer division (36 / 10). Each digit is then sent to its respective display.
  % operator for the tens digit is just for safety, ensuring that we just send one digit to the displayers 
*/


#define PAUSE_SWITCH_BIT 6    // SW6 is used to Pause/Resum the program 
#define EXIT_SWITCH_BIT  7    // SW7 is used to exit the program 

// This value determines how many loop cycles make up one second.
// If each loop has a delay(50), and delay(5000) was one second,
// then 100 ticks (100 * 50) create the one-second interval.
#define TICKS_PER_SECOND 100

/*
 * clock_timer
 * Runs the primary clock loop. It handles timekeeping, display updates, and user input for setting the time or exiting.
 */
void clock(void){
    
  // Initialize time variables
  int hours = 0;
  int minutes = 0;
  int seconds = 0;

  int tick_counter = 0;    // This will count the fast loop cycles from 0 to 100

  // Clearing LEDs and displays before starting for ensuring 
  set_leds(0);
  set_timer_display(0, 0, 0);


  // Main infinite loop for the clock.
  while (1) {
    int switch_state = get_sw();

    // --- Exit Condition ---
    if (( switch_state >> EXIT_SWITCH_BIT) & 0x1) {
      break;    // Exit the while loop if SW7 is high (=1)
    }

    // --- Pause/Resume Logic ---
    int is_paused = ( switch_state >> PAUSE_SWITCH_BIT) & 0x1;     //Isolating the state of SW6, bit 6. if it's 1, the clock is pasued 


    // The timekeeping part runs only if the clock is not paused. (sw6 = 0)
    if(!is_paused){
      // --- Time Keeping ---
      // Incrementing the time every second.
      // delay(1000);  // Wait for approximately one second.
      tick_counter++;

      if(tick_counter >= TICKS_PER_SECOND){
        tick_counter = 0;
        seconds++;

        if (seconds >= 60) {
        seconds = 0;
        minutes++;
        }
        if (minutes >= 60) {
          minutes = 0;
          hours++;
        }
        if (hours >= 24) {
          hours = 0; // Clock resets after 24 hours.
        }
      }
    }


    // --- Button and Switch Input Handling ---
    // Checking if a button is pressed to modify the time.
    if (get_btn() == 1) {
      // set_leds(0x200);  // If the push button pressed LED9 will be turned on 

      int switch_state = get_sw();

      // Isolate the value from the 6 right-most switches (SW0-SW5).
      int value_to_set = switch_state & 0x3F;

      // Isolate the selector from the 2 left-most switches (SW9 and SW8).
      // 01 = seconds, 10 = minutes, 11 = hours.
      int selector = (switch_state >> 8) & 0x3;

      if (selector == 1 && value_to_set < 60) {       // Modify seconds
        seconds = value_to_set;

      } else if (selector == 2 && value_to_set < 60) { // Modify minutes
        minutes = value_to_set;

      } else if (selector == 3 && value_to_set < 24) { // Modify hours
        hours = value_to_set;
      }
  
      // Update the display immediately after setting a new time.
      set_timer_display(hours, minutes, seconds);

      // A small delay 
      delay(500);
      set_leds(0);    // Turning of the feedback LED 
    }

    set_timer_display(hours, minutes, seconds);
    delay(50);
  }

  // --- Program End ---
  // This part runs only after the loop is broken by SW7.
  // Clear displays and LEDs to indicate the program has ended.
  display_string("Program End.");
  set_timer_display(0,0,0);
  set_leds(0);
}