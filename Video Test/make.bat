del *.lst *.obj
del bin\*

wdc816cc.exe  -bs -DUSING_816 -ML -so -lt -o C:\Work\Andre65\Tide\Video\Circle.obj C:\Work\Andre65\Tide\Video\Circle.c
wdc816cc.exe  -bs -DUSING_816 -ML -so -lt -o C:\Work\Andre65\Tide\Video\Main.obj C:\Work\Andre65\Tide\Video\Main.c
wdc816cc.exe  -bs -DUSING_816 -ML -so -lt -o C:\Work\Andre65\Tide\Video\Video.obj C:\Work\Andre65\Tide\Video\Video.c
wdc816as.exe  -g -DUSING_816 -DM_LARGE -l C:\Work\Andre65\Tide\Video\Kernel.asm

wdcln.exe  -C10000 -D20000 -K40000 -U30000 -g -t -sz -HB -oC:\Work\Andre65\Tide\Video\bin\Video.bin C:\Work\Andre65\Tide\Video\Circle.obj C:\Work\Andre65\Tide\Video\Main.obj C:\Work\Andre65\Tide\Video\Video.obj C:\Work\Andre65\Tide\Video\Kernel.obj c0l.obj  -lcl -lml
pause