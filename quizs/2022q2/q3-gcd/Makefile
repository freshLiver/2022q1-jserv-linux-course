CC		= gcc
CFLAGS	= 

FUNC	:= gcd64_loop
START	:= 0
END		:= 1000
REPEAT	:= 10

force:

main: force
	$(CC) $(CFLAGS) -D FUNC=$(FUNC) -D S=$(START) -D E=$(END) main.c -o main.out

perf: main
	perf stat -r $(REPEAT) ./main.out

clean:
	rm -rf *.out *.o