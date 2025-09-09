# standalone_time_converter
# A simplified program to test the time2string function once.

.data
test_time:  .word   0x1234      # The hardcoded time value we want to convert (12:34)
timstr:     .space  8           # Reserve 8 empty bytes in memory for the output string "12:34\0"

.text
.globl main

# The main program entry point. Runs once and then exits.
main:
    # --- Step 1: Prepare the arguments for time2string ---
    la      a0, timstr          # Load the memory ADDRESS of our empty string buffer into a0.
    lw      a1, test_time       # Load the VALUE from test_time (0x1234) into a1.

    # --- Step 2: Call your conversion function ---
    # << SET A BREAKPOINT HERE to see the initial state of a0 and a1 >>
    jal     time2string         # Jump to your function to perform the conversion.
    # << After stepping through time2string, the memory at 'timstr' will be filled >>

    # --- Step 3: Print the result to verify it worked ---
    la      a0, timstr          # a0 must again hold the address of the string to be printed.
    li      a7, 4               # Service call 4 is for "print string".
    ecall                       # Execute the print. You should see "12:34" in the Run I/O.

    # --- Step 4: Exit the program ---
    li      a7, 10              # Service call 10 is for "exit".
    ecall                       # End 




# time2string: Converts a 16-bit NBCD time value into a "MM:SS" string.
time2string:
    # --- Prologue: Save registers ---
    addi sp, sp, -12
    sw   ra, 8(sp)
    sw   s0, 4(sp)
    sw   s1, 0(sp)

    # --- Body: Prepare and process the time value ---
    mv   s0, a0         # s0 = address of timstr
    mv   s1, a1         # s1 = 0x1234

    # 1. Process M1 ('1')
    srli a0, s1, 12
    jal  hexasc
    sb   a0, 0(s0)

    # 2. Process M2 ('2')
    srli a0, s1, 8
    jal  hexasc
    sb   a0, 1(s0)

    # 3. Add the colon ':'
    li   t0, 0x3A
    sb   t0, 2(s0)

    # 4. Process S1 ('3')
    srli a0, s1, 4
    jal  hexasc
    sb   a0, 3(s0)

    # 5. Process S2 ('4')
    mv   a0, s1
    jal  hexasc
    sb   a0, 4(s0)

    # 6. Add the null terminator '\0'
    li   t0, 0x00
    sb   t0, 5(s0)

    # --- Epilogue: Restore registers ---
    lw   s1, 0(sp)
    lw   s0, 4(sp)
    lw   ra, 8(sp)
    addi sp, sp, 12
    jr   ra

# hexasc: Converts a 4-bit number (0-15) to its ASCII hex character.
hexasc:
    andi a0, a0, 0xF
    li   t0, 10
    bge  a0, t0, letters

    addi a0, a0, 0x30
    jr   ra

letters:
    addi a0, a0, 0x37
    jr   ra