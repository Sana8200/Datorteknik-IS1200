#include "hardware.h"
#include "timer.h"
#include "lib.h"

extern int timeoutcount;
extern int mytime; // mytime = 0x5959
int hours = 0;
int minutes = 0;
int seconds = 0;
int display_mode = 0;

/**
 * This function is automatically called by the processor every time the
 * hardware timer generates an interrupt (every 100ms). It must be very fast.
 */

void handle_interrupt(unsigned cause)
{

    // Suprise Assignment
    if (cause == 17)
    {
        print("switch triggerred\n");
        // Acknowledging interrupt by resetting switch flag
        *SWITCH_EDGECAPTURE = 0;
        if (get_sw() & SWITCH_2_MASK)
        {
            print("SWitch ON\n");
            display_mode = 1;
            /*
            tick(&mytime);
            tick(&mytime);
            set_mytime_display(mytime);
            */
        }
        else
        {
            print("Switch OFF\n");
            display_mode = 0;
        }
        delay(500);
    }

    // Part (e): Acknowledge the interrupt by resetting the timer's timeout flag.
    *TIMER_STATUS = 0;

    set_leds(timeoutcount);

    // --- Clock Logic ---
    timeoutcount++; // Incrementing the timeout counter

    if (timeoutcount >= 10)
    { // If the timeout counter reached 10 (if 10 interrupts happend), start incrementing the time and applying the clock logic
        timeoutcount = 0;



        if (display_mode)
        {
            tick(&mytime);
            tick(&mytime);
            tick(&mytime);
            set_mytime_display(mytime);
            delay(50);
        }



        else
        {
            seconds++;
            if (seconds >= 60)
            {
                seconds = 0;
                minutes++;
            }
            if (minutes >= 60)
            {
                minutes = 0;
                hours++;
            }
            if (hours >= 24)
            {
                hours = 0;
            }
        }

        // Part (d): Update displays and call tick().
        // Part (f): calling the display and tick functions once every 10 interrupts, it means once per second
        if (!display_mode)
        {
            set_timer_display(hours, minutes, seconds);
            tick(&mytime);
        }
    }
}