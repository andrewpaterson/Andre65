del *.lst *.obj
del bin\*.bin bin\*.map bin\*.sym  

wdc816as.exe  -g -l -DUSING_816 -DLARGE -o StartASM.obj Start.asm
wdc816as.exe  -g -l -DUSING_816 -DLARGE -o GraphicsASM.obj Graphics.asm 
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Heap.obj Heap.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Image.obj Image.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Circle.obj Circle.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Main.obj Main.c

wdcln.exe  -C10000 -D80000 -g -t -sz -HB -obin\Video.bin Heap.obj Image.obj Circle.obj Main.obj StartASM.obj GraphicsASM.obj -lcl -lml
pause