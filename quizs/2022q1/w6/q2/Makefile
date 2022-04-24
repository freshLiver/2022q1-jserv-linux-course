.PHONY: all clean
TARGET = test-hashmap
all: $(TARGET)

include common.mk

CFLAGS = -I.
CFLAGS += -O2 -g
CFLAGS += -std=gnu11 -Wall
# CFLAGS += -fsanitize=address

LDFLAGS = -lpthread
# LDFLAGS += -fsanitize=address

BENCHMARK = false
DEFINE_FLAGS = 
ifeq ($(BENCHMARK), true)
DEFINE_FLAGS += -DBENCHMARK
endif

# standard build rules
.SUFFIXES: .o .c
.c.o:
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CC) $(DEFINE_FLAGS) -o $@ $(CFLAGS) -c -MMD -MF $@.d $<

OBJS = \
	free_later.o \
	hashmap.o \
	test-hashmap.o

deps += $(OBJS:%.o=%.o.d)

$(TARGET): $(OBJS)
	$(VECHO) "  LD\t$@\n"
	$(Q)$(CC) -o $@ $^ $(LDFLAGS)

check: $(TARGET)
	./$^

clean:
	$(VECHO) "  Cleaning...\n"
	$(Q)$(RM) $(TARGET) $(OBJS) $(deps)

-include $(deps)