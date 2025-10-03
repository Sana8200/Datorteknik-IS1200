
#include "hardware.h"

// Hardware memory addresses
// define, preprocessor directive, macro 
#define LED_BASE_ADDR           0x04000000
#define SWITCH_BASE_ADDR        0x04000010
#define SEV_SEG_DISPLAY_BASE_ADDR 0x04000050
#define PUSH_BUTTON_BASE_ADDR   0x040000d0




/* ============================== Lab 3 part c ================================ */
/*
 * set_leds(int led_mask)
 * Takes an integer and writes it to the LED base address to control the 10 LEDs.
 * Calling the funciton:    set_leds(0x2A);   modify 0x2A led_mask to turn on which led we want 
 */
void set_leds(int led_mask){
    // Creating a volatile pointer to the LED address 
    // volatile : tells the compiler don't optimize since the address might change at this pointer 
    volatile int * led_pointer = (volatile int *) LED_BASE_ADDR;

    // Defrenece the pointer to write the led_mask value to the hardware address, turning the LEDs on or off 
    *led_pointer = led_mask;
}





/* ============================== Lab 3 part g ================================ */
/*
 * get_btn reads the status of teh push button
 * The second(push) button corresponds to bit 1 of the hardware register 
 * This function isolates that bit and returns it as the least significant bit (0 not pressed or 1 pressed)
 */
int get_btn(void){
    volatile int *push_button_pointer = (volatile int *) PUSH_BUTTON_BASE_ADDR;

    // Masking operation 0x01 to zero out all other bits, isoloting the button state(the least significant bit)
    return (*push_button_pointer) & 0x01 ;    
}
    




/* ============================== Lab 3 part f ================================ */
/*
 * int get_sw(void);
 * Reads the status of the 10 toggle switches on the board, no parameter 
 * the return value will be an integer where 10 least significant bits correspond to the state of the switches SW0-SW9 
 * All other bits should be 0 
 */
int get_sw(void){
    // Creating a volatile pointer to the switch hardware address
    volatile int *switch_pointer = (volatile int *) SWITCH_BASE_ADDR;

    // *switch_pointer, is defrencing part which gives the value at the switch address 
    // Applying the mask using & bitwise AND operation, all bits other than 10 least significant bits will be 0 
    // 0x3FF = 0011 1111 1111
    return (*switch_pointer) & 0x3FF; 
}






/* ============================== Lab 3 part e ================================ */
/*
 * set_display writes a value to one of the six 7-segment displays
 * The display hardware uses active-low logic = 0 in a bit position turns the correspoinding segment ON
 * display_numbers corresponds to one of the 7 segment displays the user wants to use 
 * value is the 8 bit pattern to send to the display, the value we want to see on the display 
 * This funciton doesn't have any return value 
 * Calling the function:   set_leds(0, 5);   will display 5 on the first(0) displayer 
 */
void set_display( int display_number, int value){

    static const int sev_seg_map[] = {       // Look up table for the numbers on the 7 segment display 
        0x40, // 0
        0x79, // 1
        0x24, // 2
        0x30, // 3
        0x19, // 4
        0x12, // 5
        0x02, // 6
        0x78, // 7
        0x00, // 8
        0x10, // 9
    };
     

    // If the value is valid, it will look up the digit in the array to find the correct bit pattern 
    // This part also handles cases where the input value is not valid and not a single digit
    int bit_pattern;

    if(value >= 0 && value <= 9){
        bit_pattern = sev_seg_map[value];
    } else {
        // Turning off all the segments for invalid numbers 
        // bit_pattern = 0x7F;    

        // for invalid numbers bigger than 9 or negative numbers show 0 on the display 
        bit_pattern = sev_seg_map[0];            
    }


    // Calculating the address for the specified display 
    // Each display address is offset by 0x10 from the previous one, So it depends which displayer of 6 we want to use (0-5)
    unsigned int displayer_address = SEV_SEG_DISPLAY_BASE_ADDR + (display_number * 0x10);

    // Creating a volatile pointer to the calculated hardware address 
    volatile int *display_pointer = (volatile int *) displayer_address;

    // Writing the bit_pattern of the value to the display's memory-mapped register 
    *display_pointer = bit_pattern; 
}

/* 
// Simplified code code to use just a fixed displayer (0, HEX0) displayer with a fixed number 
void sevenSegDisplay(void){
    volatile int *segm7 = (volatile int *) 0x04000050;
    *segm7 = 0x19;  
}
*/







