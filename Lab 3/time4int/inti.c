#include "hardware.h"
#include "timer.h"
#include "lib.h"

/* Add your code here for initializing interrupts. */

/**
 * @brief Initializes hardware, including the timer for interrupt generation.
 */
void labinit(void)
{

    // Set the timer period for 100ms (3,000,000 cycles at 30MHz).
    int period_value = 3000000;
    *TIMER_PERIODL = period_value & 0xFFFF;
    *TIMER_PERIODH = (period_value >> 16) & 0xFFFF;

    // Clear the timer's status register.
    *TIMER_STATUS = 0;

    // Part h assingment 3
    // Enabling the timer to generate the interrupts by configuring the control registers bits 
    // TIMER enable interrupts is controled by 0x1 bit,
    // Timer Control Register value = 0x2 OR 0x4 OR 0x1 = 0111 = 0x7
    *TIMER_CTRL = TIMER_CTRL_CONT | TIMER_CTRL_START | TIMER_CTRL_ITO;

    // This tells the switch hardware to enable interrupts for switch3.
    // Setting bit 3 to '1' enables interrupts for the corresponding port.
    *SWITCH_INTERRUPT_MASK = SWITCH_2_MASK;

    // Part h assignment 3
    // Inside enable_interrupt function enabled interrupts and allowing interrupts from the timer (machine timer and switch interrupt)
    enable_interrupt();
}
