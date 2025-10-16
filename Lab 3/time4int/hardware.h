/* hardware.h
   Header file for hardware interaction functions. 
*/

#ifndef HARDWARE_H
#define HARDWARE_H

// Hardware memory addresses
// define, preprocessor directive, macro
#define LED_BASE_ADDR 0x04000000
#define SWITCH_BASE_ADDR 0x04000010
#define SEV_SEG_DISPLAY_BASE_ADDR 0x04000050
#define PUSH_BUTTON_BASE_ADDR 0x040000d0


// Suprise Assignment lab 3
// Address of the interruptmask register (Base + Offset 2 (2 * 4 bytes))
#define SWITCH_INTERRUPT_MASK ((volatile int *)(SWITCH_BASE_ADDR + 0x8))
// Address of the edgecapture register (Base + Offset 3 (3 * 4 bytes))
#define SWITCH_EDGECAPTURE ((volatile int *)(SWITCH_BASE_ADDR + 0xC))
// A mask to specifically target switch #3 (which corresponds to bit 3).
#define SWITCH_2_MASK 0x4



/* --- Initialization --- */
// Initializes the hardware peripherals, particularly the timer.
// This function must be called once at the start of the program.
void labinit(void);
void handle_interrupt(unsigned cause);



// Output Functions
// Sets the state of the 10 LEDs using a bitmask.
void set_leds(int led_mask);
// Sets a single digit (0-9) on one of the six 7-segment displays.
void set_display(int display_number, int value);



// Input Functions
// Reads the state of the 10 toggle switches.
int get_sw(void);
// Reads the state of the push(second) buttons.
int get_btn(void);



// 7 segment display functions
void set_timer_display(int hours, int minutes, int seconds);
void set_mytime_display(int time_val);

#endif /* HARDWARE_H */
