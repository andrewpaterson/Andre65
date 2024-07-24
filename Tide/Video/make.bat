call clean.bat
cls
@echo %time%

wdc816as.exe  -g -l -DUSING_816 -DLARGE -o StartASM.obj Start.asm || exit /b
wdc816as.exe  -g -l -DUSING_816 -DLARGE -o UploadASM.obj Upload.asm || exit /b
wdc816as.exe  -g -l -DUSING_816 -DLARGE -o GraphicsASM.obj Graphics.asm || exit /b
wdc816as.exe  -g -l -DUSING_816 -DLARGE -o StandardASM.obj Standard.asm || exit /b
wdc816as.exe  -g -l -DUSING_816 -DLARGE -o FontASM.obj Font.asm || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Heap.obj Heap.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Image.obj Image.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Circle.obj Circle.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Polygon.obj Polygon.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Font.obj Font.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o ColourTest.obj ColourTest.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Splatter.obj Splatter.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -lt -pb -pp -px -o Random.obj Random.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Main.obj Main.c || exit /b
wdc816cc.exe  -bs -DUSING_816 -ml -wr -wu -so -sp -lt -pb -pp -px -o Font5x7.obj Font5x7.c || exit /b
wdcln.exe -C20000,00000 -g -t -sz -HB -obin\VideoUpload.bin UploadASM.obj Heap.obj Image.obj Circle.obj Polygon.obj Font.obj Random.obj Splatter.obj ColourTest.obj Font5x7.obj Main.obj GraphicsASM.obj StandardASM.obj FontASM.obj -lcl -lml || exit /b
wdcln.exe -C20000 -g -t -sz -HIE -obin\VideoRom.hex Heap.obj Image.obj Circle.obj Polygon.obj Font.obj Random.obj Splatter.obj ColourTest.obj Font5x7.obj Main.obj StartASM.obj GraphicsASM.obj StandardASM.obj FontASM.obj -lcl -lml || exit /b
srec_cat.exe Graphics.sft -binary -offset=0x30000 -o bin/Graphics.hex -intel
srec_cat.exe -IGnore-Checksums bin/VideoRom.hex -Intel Mult.hex -Intel bin/Graphics.hex -Intel -o bin/Rom.hex -Intel
