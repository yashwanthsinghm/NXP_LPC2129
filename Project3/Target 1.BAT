SET RVCT40INC=C:\Keil\ARM\RV31\INC
SET RVCT40LIB=C:\Keil\ARM\RV31\LIB
SET CPU_TYPE=LPC2129
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00000000
"C:\Keil\ARM\BIN40\ArmAsm" --Via "startup._ia"
"C:\Keil\ARM\BIN40\ArmCC" --Via "task3_ques5.__i"
"C:\Keil\ARM\BIN40\ArmLink" --Via "task3_code3.lnp"
C:\Keil\ARM\BIN40\fromelf.exe "task3_code3.axf" --i32combined --output "task3_code3.hex"
