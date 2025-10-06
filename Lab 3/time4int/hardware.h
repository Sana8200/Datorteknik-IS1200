
/* hardware.h
   Header file for hardware interaction functions. This file provides the "public interface" for the hardware.c implementation file.
*/

#ifndef HARDWARE_H
#define HARDWARE_H

/* --- Initialization --- */
// Initializes the hardware peripherals, particularly the timer.
// This function must be called once at the start of the program.
// void labinit(void);

// void handle_interrupt(unsigned cause);

/* --- Output Functions --- */
// Sets the state of the 10 LEDs using a bitmask.
void set_leds(int led_mask);
// Sets a single digit (0-9) on one of the six 7-segment displays.
void set_display(int display_number, int value);

/* --- Input Functions --- */
// Reads the state of the 10 toggle switches.
int get_sw(void);
// Reads the state of the push(second) buttons.
int get_btn(void);

#endif /* HARDWARE_H */









