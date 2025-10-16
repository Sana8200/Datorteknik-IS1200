
#include "hardware.h"

void set_timer_display(int hours, int minutes, int seconds)
{
  set_display(0, seconds % 10);
  set_display(1, (seconds / 10) % 10);
  set_display(2, minutes % 10);
  set_display(3, (minutes / 10) % 10);
  set_display(4, hours % 10);
  set_display(5, (hours / 10) % 10);
}

// Implementation for the new mytime display function
void set_mytime_display(int time_val)
{
  // Displays the BCD value MM:SS on the first 4 digits
  set_display(0, (time_val & 0xF));  // Second 1
  set_display(1, (time_val >> 4) & 0xF);  // Second 10
  set_display(2, (time_val >> 8) & 0xF);  // Minute 1
  set_display(3, (time_val >> 12) & 0xF); // Minute 10

  // Blank the unused hour displays
  set_display(4, 16);
  set_display(5, 16);
}
