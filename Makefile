# --- Project details -------------------------------------------------

PROJ    := insertBin
TARGET  := $(PROJ)

COBJS   := main.o

DEBUG := 0

# --- Build defines ---------------------------------------------------

CC      := gcc
LD      := gcc

ifeq ($(DEBUG), 0)
CFLAGS  := -Os -s -Wall
else
CFLAGS	:= -ggdb -O0 -Wall
endif


.PHONY : build clean run

# --- Build -----------------------------------------------------------
# Build process starts here!

build: $(TARGET).exe


# Compile (step 1)

$(PROJ).exe: $(COBJS)
	$(CC) $^ $(CFLAGS) -o $@

$(COBJS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@




# --- Clean -----------------------------------------------------------

clean : 

	@rm -fv *.dll
	@rm -fv *.wcx
	@rm -fv *.o
	@rm -fv *.exe

# --- Run -----------------------------------------------------------
# Run app
run: 
	-./$(PROJ) patch.bin target.bin -o 20 -s 2A -f FF


# --- Debug -----------------------------------------------------------

debug : 

	gdb -silent --args $(PROJ) patch.bin target.bin -o 20 -s 28 -f
	

#EOF
