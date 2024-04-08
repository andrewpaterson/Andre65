del *.lst *.obj
del bin\*.bin bin\*.map bin\*.sym  

wdc816as.exe  -g -DUSING_816 -DLARGE Kernel.asm
wdc816cc.exe  -bs -DUSING_816 -ML -so -lt -o Circle.obj Circle.c
wdc816cc.exe  -bs -DUSING_816 -ML -so -lt -o Main.obj Main.c
wdc816cc.exe  -bs -DUSING_816 -ML -so -lt -o Video.obj Video.c

wdcln.exe  -C10000 -D20000 -K40000 -U30000 -g -t -sz -HB -obin\Video.bin Circle.obj Main.obj Video.obj Kernel.obj  -lcl -lml
pause