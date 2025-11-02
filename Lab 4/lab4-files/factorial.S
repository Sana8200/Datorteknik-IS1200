# Assignment 5 Lab 4 
# Factorial Function Implementation n!

.text
.global main

main:
    addi t0, zero, 0      # Initializing t0 which is input value n, the number 4 can change for different number    
    addi t2, zero, 1      # t2 will hold the output value, the result of n!
    
    # special cases for 0! and 1!
    addi t1, zero, 1      # t1 = 1, for comparison
    beq t0, zero, stop    # if n == 0 , jump to done, t2 wil be 1  
    beq t0, t1, stop      # if n == 1 , jump to done, t2 will be 1 
    
outer_loop:
    # Instead of using mul instruction, we nested loop and use add for the multiplication process 
    addi ra, zero,0       # ra Temporary accumlator for the multiplication 
    add t1, t0, zero      # t1 counter for the multipliation (add) loop
    
mul_loop:
    # Nested loop for repeated addition
    beq t1, zero, mul_done    # Checking that multiplication counter is 0
    
    add ra, ra, t2        # ra = ra + t2 
    addi t1, t1, -1       # decrementing the multiplication counter 
    
    beq zero, zero, mul_loop      # Unconditional jump to jump back to the start of the multiplication loop 
    
mul_done:
    add t2, ra, zero     # We get the multiplication result which is in ra and copy this to our final result register t2, t2 = ra
    addi t0, t0, -1      # Decrementing the outer loop counter 
    
    # Checking if we are done with the factorial calculation
    addi t1, zero, 1  
    beq t0, t1, stop    # If n == 1, we are finished, since we loop until n == 1
    
    beq zero, zero, outer_loop  # If we are not done, jump back  to the start of the outer loop 
    
stop:
   beq zero, zero, stop      # loop that jumps to itself forever 
    