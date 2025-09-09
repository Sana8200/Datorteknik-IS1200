
# --------------------------------------------------------------------------
# INCORRECT DELAY FUNCTION 
# --------------------------------------------------------------------------
# The following version of the delay function is NOT correct. It has been commented out to explain the common logical errors.
# IT's exactly equal to the C code ( the order of code ) but this order doesn't work in assembly 
# --------------------------------------------------------------------------

# delay:
#    li t0, 0

# while_loop:
#    bge x0, a0, exit_delay
#    addi a0, a0, -1

# for_loop:
#    li t1, 4711
#    addi t0, t0, 1
#    blt t0, t1, for_loop

#    bne a0, x0, while_loop

# exit_delay:
#    ret

# --------------------------------------------------------------------------
# WHY IT IS INCORRECT:
# 1. The inner loop counter 't0' is never reset. It is set to 0 only once before the 'while_loop' starts. After the first millisecond, 't0' will
#    be 4711. For all subsequent milliseconds, the inner 'for_loop' will run only once, making the total delay much too short.

# 2. The inner loop limit 't1' is reloaded constantly. The 'li t1, 4711' is inside the 'for_loop', meaning it runs 4711 times during the first
#    millisecond. This is very inefficient.


# --------------------------------------------------------------------------
# CORRECT DELAY FUNCTION
# --------------------------------------------------------------------------
# This is the correct implementation of the delay function.
# It directly translates the logic from the C code.

delay:
    # C Code Check: while(ms > 0)
    # First, check if there is any delay to perform. If 'ms' (a0) is
    # zero or negative, we don't need to do anything, so we jump
    # straight to the end of the function.
    blez a0, exit_delay

# This is the outer loop, corresponding to the C 'while' loop.
# It runs once for each millisecond we need to wait.
while_loop:
    # C Code: for( i = 0; i < 4711; i = i + 1 )
    #
    # Setup for the inner loop. For EACH millisecond, we must reset
    # our inner loop counter 'i' (t0) back to 0 and set the limit.
    li t1, 4711                 # Set the limit '4711' into register t1.
    li t0, 0                    # Reset the counter 'i' (t0) to 0.

# This is the inner loop, corresponding to the C 'for' loop.
# Its only job is to run for a specific number of cycles to waste time.
for_loop:
    # C Code: i = i + 1
    # Increment the inner loop counter.
    addi t0, t0, 1

    # C Code Check: i < 4711
    # If the counter 'i' (t0) is still less than the limit (t1),
    # branch back to the start of the 'for_loop'.
    blt t0, t1, for_loop

    # -- End of the 'for' loop --
    # At this point, about 1 millisecond of time has passed.

    # C Code: ms = ms - 1;
    # Decrement the main millisecond counter 'ms' (a0) by one.
    addi a0, a0, -1

    # C Code Check: while( ms > 0 )
    # If 'ms' (a0) is still greater than zero, we branch back to the
    # 'while_loop' to wait for another millisecond.
    bgtz a0, while_loop

# This is the exit point for the function.
exit_delay:
    # Return to the function that called 'delay'.
    jr ra
    # ret 

