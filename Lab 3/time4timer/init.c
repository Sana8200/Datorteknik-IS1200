#include "timer.h"

/* Add your code here for initializing interrupts. */

/*
 * labinit
 * sets up the timer to generate a timeout event every 100 ms
 */
void labinit(void){
  // DTEK-V board clock frequency is 30 MHz = 30,000,000 Hz
  // The timeout interval that we want is 100 ms = 0.1 seconds
  // Calculating Period value :   Period = freqeuncy * interval = 30,000,000 * 0.1 = 3,000,000

  // The timer (hardware counter) will count from 0 up to this value 
  int period_value = 3000000;   


  // Setting the timer's period by writing to the two 16-bit period registers.
  *TIMER_PERIODL = period_value & 0xFFFF;          // lower 16 bits
  *TIMER_PERIODH = (period_value >> 16) & 0xFFFF;  // upper 16 bits


  // Clearing the timeout flag (TO) in the status register to ensure a clean start, sefety step. 
  *TIMER_STATUS = 0;


  // Starting the timer in continuous mode.
  // Control value = (Continuous Bit) | (Start Bit) = 0x2 | 0x4 = 0x6.
  *TIMER_CTRL = TIMER_CTRL_CONT | TIMER_CTRL_START;
}
