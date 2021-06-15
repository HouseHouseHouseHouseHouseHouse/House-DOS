SRCDIR := src/inc/

CC := i686-elf-gcc
AS := i686-elf-as
LD := i686-elf-ld

CFILES 	:= $(shell find $(SRCDIR) -type f -name "*.c")
SFILES 	:= $(shell find $(SRCDIR) -type f -name "*.s")

OBJS 	:= $(patsubst %.c, %.o, $(CFILES))
OBJS	+= $(patsubst %.s, %_s.o, $(SFILES))

CCFLAGS 	:= -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASFLAGS 	:= 

.PHONY: all setup sys clean debug

all: setup sys clean

setup:
	rm -rf bin/
	mkdir bin/
	mkdir bin/kernel/

sys: $(OBJS) src/init.s src/sys.c src/linker.ld
	$(AS) $(ASFLAGS) -c src/init.s -o bin/kernel/init.o
	$(CC) $(CCFLAGS) -c src/sys.c -o bin/kernel/main.o
	$(CC) $(CCFLAGS) -T src/linker.ld -o bin/sys -nostdlib $(OBJS) bin/kernel/*.o -lgcc

clean:
	rm -rf $(OBJS) bin/kernel/

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

%_s.o: %.s
	$(AS) $(ASFLAGS) -c $< -o $@
