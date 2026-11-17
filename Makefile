CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS  = -mcpu=cortex-a8 -O2 -g -Wall -Iinc
LDFLAGS = -T src/memmap.ld

SRCS = src/startup.s \
       src/main.c \
       src/set_gpio.c \
       src/set_clock.c \
	   src/set_blink.c \
	   src/watchdog.c \
	   src/uart.c     \
	   src/timer.c \
	   src/Interruption.c \
	   src/init.c \
	   src/mecanicas.c \
	   src/sprites.c \
	   src/joystick.c \
	   src/jogo.c \
	   src/mapas.c

OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
OBJS := $(OBJS:.s=.o)

TARGET = bin/app_baremetal
DESTINY = /srv/tftpboot/ 


all: $(TARGET).bin

obj:
	mkdir -p obj

bin:
	mkdir -p bin

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/%.s | obj
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS) | bin
	$(LD) $(LDFLAGS) $^ -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f obj/*.o bin/*.dump bin/*.elf bin/*.bin

copy:
	cp $(TARGET).bin $(DESTINY)
