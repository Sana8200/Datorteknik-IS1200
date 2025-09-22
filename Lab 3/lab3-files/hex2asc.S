  # hexmain.S
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
	.globl hex2asc

hex2asc:
	li	a0, 17		# test number (from 0 to 15)
	
	addi    sp,sp,-4
	sw      ra,0(sp)
	
	jal	hexasc		# call hexasc
	
	li	a7, 11	# write a0 to stdout
	ecall

	lw      ra,0(sp)
	addi    sp,sp,4
	jr      ra	

  # You can write your own code for hexasc here
  
  # keeping only 4 bits of the input
  # if the number < 10 convert to ASCII 0 to 9   add 0x30 or decimal 48 to input 
  # if the number > 10 convert to ASCII A to F   add 0x37 or decimal 55 to input 
  # return ASCII code in a0
  # No Usage of saved registers 
  # 7 lsb of a0 when returning is ASCII code 
  

hexasc:
    andi a0, a0, 0xF            # keeping only 4 lsb in a0, 1 in a0, 00001111
    li   t0, 10                 # loading value 10 into temporary register t0, t0 = 10, used for comparison
    bge  a0, t0, letters        # branch if greater than or equal, if a0 >= t0, jumps to label letters, where the program sees the number should be a digit or a letter 

    addi a0, a0, 0x30           # '0'..'9', add 48 in decimal or 0x30 hex converts the values 0 to 9 to the corresponding ASCII code 
    jr   ra                     # jump register, return control to the caller of the function, return address register 


letters:
    addi a0, a0, 0x37           # 'A'..'F', adds 55 decimal or 0x37 (not 0x41) to a0, becasue ASCII code for A to F are 65 to 70 
    jr   ra                     # returns to the caller, return adddress register  
