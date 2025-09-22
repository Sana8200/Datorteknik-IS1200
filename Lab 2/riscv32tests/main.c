/* main.c

   This file written 2015 by F Lundevall, David Broman and Artur Podobas

   Latest update 2024-07-27 by Artur Podobas

   For copyright and licensing, see file COPYING */

extern void print(const char*);
extern void print_dec(unsigned int);
extern void print_hex32 ( unsigned int x);

void handle_interrupt(void) {}


// Takes a string and a pointer. It print the string, the memoery address the pointer holds, and the 4 byte integer value at that address. 
void print_word (const char *str, void *ptr)
{
  print(str);
  print(" : address=");
  print_hex32((unsigned int) ptr);
  print(" : value=");
  print_dec(*((unsigned int*)ptr));
  print("\n");
}



// Does the same as print_word, but for a single byte (char).
void print_byte (const char *str, char *ptr)
{
  print(str);
  print(" : address=");
  print_hex32((unsigned int) ptr);
  print(" : value=");
  print_dec(*((unsigned char*)ptr));
  print("\n");
}


// Global variables, accessible from all functions, they go to the data segment. 
int gv;      /* Uninitiallized, goes to .bss section */
int in = 3;  /* Initialized, goes to .data section */



// A function that takes one integer arument and returns nothing, it does some operations with the argument and global values. 
void fun(int param)
{
  // Creating a local variable of param, it goes to the stack. Pass by value
  param++;    /* Incrementing the local copy only, the original value in main is unaffected.*/
  print_word( "AF1: param", &param );
  gv = param;    /* Change the value of a global variable, 
                 /* A side effect of the function. */
}




// The main function, Execution flow
int main()
{
  /* Local variables. */
  int m;    
  int * p; /* Declare p as pointer, so that p can hold an address. */
  char cs[ 9 ] = "Bonjour!";   /* An array of 9 characters, 8 characters for the string plus null terminator */
  char * cp = cs; /* Declare cp as pointer, initialise cp to point to cs */
                                                                                                                                                                                             
  /* Do some calculation. */                                                                                                                                                                
  gv = 4;                                                                                                                                                                                    
  m = gv + in;
  
  /* Check the addresses and values of some variables and stuff */    
  // The & operator gives the address of a variable.                                                                                                                       
  print_word( "AM1: gv", &gv );        // .bss section                                                                                                                                                        
  print_word( "AM2: in", &in );        // .data section
  print_word( "AM3: fun", &fun );      // .text section (code)
  print_word( "AM4: main", &main );    // .text section (code)

  // Playing with pointers 

  p = &m;     /* Let p point to m, i.e., assign the address of m to p */

  /* Check p and m */
  print_word( "AM5: p", &p );
  print_word( "AM6: m", &m );

  /* Change *p */

  *p = *p + 1;       /* Derefrencing */

  /* Check p and m */
  print_word( "AM7: p", &p );
  print_word( "AM8: m", &m );

  p = (int*)cp;   /* Casting a char pointer to an integer pointer */

  print_word( "AM9: p", &p );

  print_byte( "AM10: cs[0]", &cs[0] );
  print_byte( "AM11: cs[1]", &cs[1] );
  print_byte( "AM12: cs[2]", &cs[2] );
  print_byte( "AM13: cs[3]", &cs[3] );

  *p = 0x1234abcd; /* It starts to get interesting... */

  print_byte( "AM14: cs[0]", &cs[0] );
  print_byte( "AM15: cs[1]", &cs[1] ); 
  print_byte( "AM16: cs[2]", &cs[2] );
  print_byte( "AM17: cs[3]", &cs[3] );

  fun(m);

  /* Re-check the addresses and values of m and gv */
  print_word( "AM18: m", &m );
  print_word( "AM19: gv", &gv );

}
