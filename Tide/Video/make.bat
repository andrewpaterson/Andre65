del *.lst *.obj
del bin\*.bin bin\*.map bin\*.sym  

wdc816as.exe  -g -l -DUSING_816 -DLARGE Start.asm
wdc816as.exe  -g -l -DUSING_816 -DLARGE Graphics.asm
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Heap.obj Heap.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Circle.obj Circle.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Main.obj Main.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Video.obj Video.c

wdcln.exe  -C10000 -D80000 -g -t -sz -HB -obin\Video.bin Heap.obj Circle.obj Main.obj Video.obj Start.obj Graphics.obj -lcl -lml
pause