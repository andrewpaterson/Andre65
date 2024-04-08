ca65 --cpu 65c02 -I D:\Software\6502\CC65\include putch.s 

cc65 -t none -I C:\CC65\include -I D:\Software\6502\CC65\include -O main.c
ca65 --cpu 65c02 -I C:\CC65\asminc main.s
ld65 --cfg-path C:\CC65\CFG -L D:\Software\6502\CC65\os_kernel\lib -C SF1.cfg -m main.map putch.o  main.o SFNV.lib
pause