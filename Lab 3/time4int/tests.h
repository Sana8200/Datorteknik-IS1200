
/* tests.h
   Header file for hardware tests
*/

#ifndef TESTS_H
#define TESTS_H

// Runs the initial 16-second LED startup sequence.
void run_start_sequence(void);

// Declares the function for the switch and LED test loop.
void switch_button_test(void);


void run_start_sequence(void);


// --- External Global Variables ---
// These are DEFINED in labmain.c and declared here for access by other files.
extern int mytime;
extern char textstring[];

#endif /* TESTS_H */