UNAME_S := $(shell uname -s)                                                                                                                                  
ifeq ($(UNAME_S),Darwin)
    PRINTF = printf
else
    PRINTF = env printf
endif

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @$(PRINTF)
endif