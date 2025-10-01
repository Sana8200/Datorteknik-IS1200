/* main.c

   This file written 2024 by Artur Podobas and Pedro Antunes

   For copyright and licensing, see file COPYING */


/* Below functions are external and found in other files. */
extern void print(const char*);
extern void print_dec(unsigned int);
extern void display_string(char*);
extern void time2string(char*,int);
extern void tick(int*);
extern void delay(int);
extern int nextprime( int );


// Calling the functions writting Lab 3 part c 
extern void set_leds(int led_mask);
extern void set_display(int display_number, int value);
extern int get_sw(void);
extern int get_btn(void);


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

  // Enter a forever loop
   while (1) {
    
    // Get the state of all inputs
    int switch_state = get_sw();
    int push_btn_state = get_btn();


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



