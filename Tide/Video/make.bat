del *.lst *.obj
del bin\*.bin bin\*.map bin\*.sym bin\*.hex

wdc816as.exe  -g -l -DUSING_816 -DLARGE -o StartASM.obj Start.asm
wdc816as.exe  -g -l -DUSING_816 -DLARGE -o GraphicsASM.obj Graphics.asm 
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Heap.obj Heap.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Image.obj Image.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Circle.obj Circle.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Polygon.obj Polygon.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o ColourTest.obj ColourTest.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Splatter.obj Splatter.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -lt -pb -pp -px -o Random.obj Random.c
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Main.obj Main.c
wdcln.exe -C10000 -D20000 -g -t -sz -HIE -obin\Video.hex Heap.obj Image.obj Circle.obj Polygon.obj Random.obj Splatter.obj ColourTest.obj Main.obj StartASM.obj GraphicsASM.obj -lcl -lml
srec_cat.exe -IGnore-Checksums bin\Video.hex -Intel mult.hex -Intel -o bin/Rom.hex -Intel
