CC = gcc
CFLAGS = -O3

FUNC := average_div
SIZE := 1000
REPEAT := 1000
OUT := main

main: force
	$(CC) $(CFLAGS) -D FUNC=$(FUNC) -D SIZE=$(SIZE) main.c -o $(OUT).out

perf: main
	perf stat --repeat $(REPEAT) ./main.out

asm: 
	$(CC) $(CFLAGS) -D FUNC=$(FUNC) -D SIZE=$(SIZE) -S main.c -o $(OUT).s
force:

clean:
	rm -rf *.o *.out *.s
