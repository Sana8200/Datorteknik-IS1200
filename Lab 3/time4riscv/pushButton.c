/*
 * get_btn reads the status of teh push button
 * The second(push) button corresponds to bit 1 of the hardware register 
 * This function isolates that bit and returns it as the least significant bit (0 or 1)
 * 0 is when the button is not pushed 
 * 1 is when the button is pushed 
 */


#define PUSH_BUTTON_BASE_ADDR  0x040000d0

int get_btn(void){

    volatile int * push_button_pointer = (volatile int *) PUSH_BUTTON_BASE_ADDR;

    int btn_value = *push_button_pointer  >> 1;   // Second button is at bit 1, so right shift by 1 to move ot to the bit 0 position 

    int result = btn_value & 0x1;     // Masking operation with 0x1 to zero out all other bits, isolating the button state 

    return result;
}


