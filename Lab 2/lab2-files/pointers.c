/*
 pointers.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

char* text1 = "This is a string.";          
char* text2 = "Yet another thing.";

// 20 integers equals to 80 bytes (each int is 4 bytes)
int list1[20];        // list1: .space 80
int list2[20];        // list2: .space 80

int counter = 0;      // Global variable to count the number of characters copied
                      // counter: .word 0       allocated a 4 byte memory space and put 0 in it 



// function copycodes copies ASCII codes from text to list and updates count 
void copycodes(char* text, int* list, int* count){       // Pointer parameters, text points to a char, list points to an int, count points to an int 
                                                         
  while( *text != '\0'){        // Loop until the null terminator is reached,                 beqz t0, done
                             
    *list = *text;              // Dereferencing the pointers to access the values they point to      lb t0, 0(a0)       load byte from text pointer address
                                // Copy the ASCII code from text to list,                             sw t0, 0(a1)       a0 is text pointer, a1 is list pointer
                                
                                // Incrementing the pointers itselves to point to the next memory address
    text++;                     // Move to the next character in text,                        addi a0, a0, 1     char pointer incremented by 1 byte
    list++;                     // Move to the next position in list,                         addi a1, a1, 4     int pointer incremented by 4 bytes

    int temp = *count;         // Load the current count value into a temporary variable      lw t1, 0(a2)       a2 is count pointer
    temp++;                    // Increment the temporary variable                            addi t1, t1, 1     add 1 to the count
    *count = temp;             // Store the updated count back to the original variable       sw t1, 0(a2)
                               // Incrementing the variable that pointer count points to      (*count)++  would also work here
  }
}


// fucntion work calls copycodes twice to copy two strings text1 and text2
void work(){
  // Passing the address of counter using & operator, so that copycodes can update the original counter variable    
  // This is necessary because counter is a global variable and we want to keep track of the total count across both calls
  // explicitly passing the address makes it clear that we are working with the same counter variable 
  // but for text1 and list1, text2 and list2, we can just pass the pointers directly as they are already pointers to the addresses of the strings and lists

  copycodes(text1, list1, &counter);          // jal copycodes   for a0, a1, a2 
  copycodes(text2, list2, &counter);          // jal copycodes   for a0, a1, a2
}



void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){               // endian_proof takes a pointer to char as parameter
  // This function prints the individual bytes of the integer counter in hexadecimal format
  // This helps to demonstrate the endianness of the system (little-endian or big-endian)
  // In little-endian systems, the least significant byte is stored at the lowest memory address
  // In big-endian systems, the most significant byte is stored at the lowest memory address
  // By printing the bytes in order, we can see how the integer is represented in memory
  
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}



int main(void){
 
    work();                    // jal work
    printf("\nlist1: ");
    printlist(list1);       // Print the first list
    printf("\nlist2: ");
    printlist(list2);       // Print the second list
    printf("\nCount = %d\n" , counter);          // Print the total count of characters copied
 
    endian_proof((char*) &counter);                  

    return 0;                  
}
