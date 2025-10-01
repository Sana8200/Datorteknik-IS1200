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

  // Lab 3 part e 
  set_display(0, 5);


  // Lab 3 part d, this will show that how many seconds has elapsed since the program started 
  // The program stpes when the first 4 LEDs are on (4 leds = 1111 = 15 = 0xF), 
  // The program runs for 16 seconds (0-15)
  for(int led_counter = 0 ; led_counter <= 15 ; led_counter++){

    time2string( textstring, mytime ); // Converts mytime to string
    display_string( textstring ); //Print out the string 'textstring'


    set_leds(led_counter);

    
    delay(3000);          // Delays 1 sec (adjust this value)
    tick( &mytime );     // Ticks the clock once

  }


  // Call labinit()
  labinit();



  // Enter a forever loop
  while (1) {
    
    
  }
}



