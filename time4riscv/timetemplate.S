# timetemplate.S
# Written 2015 by F Lundevall
# Ported 2024/06 by W Szczerek (from MIPS to RISC-V)
# Copyright abandonded - this file is in the public domain.

#############################################################
# Choose the macro syntax for RARS or DTEK-V board.         #
# The syntax for RARS is probably due to its MIPS heritage. #
#############################################################
###################
# Macros for RARS #
###################
#.macro	PUSH (%reg)
#	addi	sp,sp,-4
#	sw	%reg,0(sp) 
#.end_macro

#.macro	POP (%reg)
#	lw	%reg,0(sp)
#	addi	sp,sp,4
#.end_macro


###################
# Macros for DTEK #
###################
.macro	PUSH reg
	addi sp,sp,-4
	sw \reg,0(sp) 
.endm

.macro	POP reg
	lw	\reg,0(sp)
	addi	sp,sp,4
.endm
#############################################################

	.data
	.align 2
mytime:	.word 	0x0000
timstr:	.asciz 	"text more text lots of text\0"
	.text
	.globl timetemplate, tick, time2string, delay, hexasc

# Function for displaying a string with a newline at the end	
display_string:	
	li a7,4
	ecall
	li a0, 10
	li a7,11
	ecall
	jr ra
	
timetemplate:
	la	a0, timstr
	jal     display_string
	
	# wait a little
	li	a0, 6000		# ms, 1000, or 3000, this is for getting the delay, a0 which will used in delay subroutine 
	jal	delay
	
	# call tick
	la 	a0, mytime
	jal	tick
	
	# call your function time2string
	la	a0, timstr
	la	t0, mytime
	lw	a1, 0(t0)
	jal	time2string
	
	# go back and do it all again
	j	timetemplate

	
# tick: update time pointed to by $a0
tick:	lw	t0, 0(a0)	# get time
	addi	t0, t0, 1	# increase
	andi	t1, t0, 0xf	# check lowest digit
	sltiu	t2, t1, 0xa	# if digit < a, okay
	bnez	t2, tiend
	addi	t0, t0, 0x6	# adjust lowest digit
	
	andi	t1, t0, 0xf0	# check next digit
	sltiu	t2, t1, 0x60	# if digit < 6, okay
	bnez	t2, tiend
	addi	t0, t0, 0xa0	# adjust digit
	
	li	t3, 0xF
	slli	t3, t3, 0x8
	and	t1, t0, t3	# check minute digit
	addi	t3, x0, 0xA
	slli	t3, t3, 0x8
	slt	t2, t1, t3	# if digit < a, okay
	bnez	t2, tiend
	addi	t0, t0, 0x600	# adjust digit - this one's okay, it's lower than 0x7FF 
	
	li	t3, 0xF
	slli	t3, t3, 0xC
	and	t1, t0, t3	# check last digit
	addi	t3, x0, 0x6
	slli	t3, t3, 0xC
	slt	t2, t1, t3	# if digit < 6, okay
	bnez	t2, tiend
	
	li	t3, 0xA
	slli	t3, t3, 0xC
	add	t0, t0, t3	# adjust last digit
tiend:	sw	t0,0(a0)	# save updated result
	jr	ra		# return

#########################################################
# Place for your functions: time2string, hex2asc, delay.#
#########################################################


# time2string : converts 16-bit NBCD time value into a M1M2:S1S2 \0 ASCII string
# a0 memory address where the output string will be stored , a1 16-bit time value , no return value 
  
                                     
time2string:
       addi sp, sp, -12       # Save ra, s0, s1 on stack, saving registers that will used and modify 
       sw ra, 8(sp)           
       sw s0, 4(sp)           
       sw s1, 0(sp)           
       
       
       mv s0, a0              # s0 = string address 
       mv s1, a1              # s1 = time value 
       
       srli a0, s1, 12        # M1    
       jal hexasc             
       sb a0, 0(s0)           
       
       srli a0, s1, 8         # M2
       jal hexasc             
       sb a0, 1(s0)           
       
       li t0, 0x3A            # ':'   
       sb t0, 2(s0)           
       
       srli a0, s1, 4         # S1   
       jal hexasc             
       sb a0, 3(s0)          
       
       mv a0, s1              # S2   
       jal hexasc         
       sb a0, 4(s0)            
             
### suprise assignment 
       
       andi t0, s1, 1         # isolate the least nibble of s1 which is the last digit, since we want to compare that number to see if it's even or odd 
       beqz t0, even          # brach if equal to zero, if in the binary form of t0, the last bit is 0 it means it's even and if it's 1 it means it's odd
                              # otherwise it will continue to the odd because the lsb is not 0 and the number is odd 
             
odd: 
       li t0, 0x44            # ASCII value for D
       sb t0, 5(s0)           # Storing D at the end of the time string 
       j end                     
                                
even:    
       li t0, 0x45            # ASCII value for E   
       sb t0, 5(s0)           # Storing E at the end of the time string (s0)
         
end:    
       li t0, 0x00            # '\0'
       sb t0, 6(s0)           
       
###       
       lw s1, 0(sp)           # Restore ra, s0, s1 ( in reverse order )       
       lw s0, 4(sp)
       lw ra, 8(sp) 
       addi sp, sp, 12        
       
       jr ra                 
       
       

hexasc:
    andi a0, a0, 0xF           # keep 4 low nibble 
    li   t0, 10                 
    bge  a0, t0, letters         

    addi a0, a0, 0x30          # 0-9
    jr   ra                    

letters:
    addi a0, a0, 0x37          # A-F  
    jr   ra                    
    



delay:
    blez a0, exit_delay          # If ms <= 0 , branch back to exit delay, return 
                                                                                              
while_loop:                                                                                                                                                                 
    li t1, 2535                  # constant upper limit t1, loop count
    li t0, 0                     # i = t0 = 0
    
for_loop:                        
    addi t0, t0, 1               # i = i + 1 
    blt t0, t1, for_loop         # if t0 < t1 ( i < limit ) continue looping 

    addi a0, a0, -1              # ms = ms - 1

    bgtz a0, while_loop          # if ms > 0 continure the while loop 
    


exit_delay:                     
    jr ra                      

