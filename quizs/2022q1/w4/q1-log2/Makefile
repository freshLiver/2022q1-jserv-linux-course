OPT_LV = 0
DEF_ARGS = 111

TARGET = const_log2

main: force
	gcc -g main.c -o main.out

const_log2: force
	gcc -O$(OPT_LV) const_log2.c -o const_log2.out


test: $(TARGET)
	./$(TARGET).out $(DEF_ARGS)

force:

clean:
	rm -f *.o *.out
