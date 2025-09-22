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

int mytime = 0x5957;
char textstring[] = "text, more text, and even more text!";

/* Below is the function that will be called when an interrupt is triggered. */
void handle_interrupt(unsigned cause) 
{}

/* Add your code here for initializing interrupts. */
void labinit(void)
{}


void set_leds(int led_mask){
  volatile int *leds = (int *)0x04000000;
  *leds = led_mask;

}

void delay_seconds(int ms){
  volatile int *timer = (int *)0x04000008;
  *timer = ms*1000; // Set the timer for ms milliseconds (assuming 1 tick = 1 microsecond)
  while (*timer > 0); // Wait until the timer counts down to zero
}





/* Your code goes into main as well as any needed functions. */
int main() {

  int led_value = 0;
  

  while (led_value <= 0xF) { // 0xF is hexadecimal for 15
        
        // Update the physical LEDs with the current counter value.
        set_leds(led_value);
        
        // Wait for approximately one second.
        delay_seconds(50000);
        
        // Increment the counter for the next iteration.
        led_value++;
    }


  // Call labinit()
  labinit();

  // Enter a forever loop
  while (1) {
    time2string( textstring, mytime ); // Converts mytime to string
    display_string( textstring ); //Print out the string 'textstring'
    delay(1000);          // Delays 1 sec (adjust this value)
    tick( &mytime );     // Ticks the clock once
  }
}


