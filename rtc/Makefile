
.PHONE:clean

TARGET		:= arm
BIN  		:= $(TARGET).bin	
LDADD		:= 0x50000000
ASM		:= start.o
OBJS		:= entry.o lib.o
OBJS		+= mmu.o vector.o do_excep.o
OBJS		+= irq.o
OBJS		+= rtc.o
CROSS_COMPILE	:= arm-linux-
CC		:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)ld
OBJCOPY		:= $(CROSS_COMPILE)objcopy
NM		:= $(CROSS_COMPILE)nm
OBJDUMP		:= $(CROSS_COMPILE)objdump
LDFLAGS		:= -lgcc -L/opt/FriendlyARM/toolschain/4.5.1/lib/gcc/arm-none-linux-gnueabi/4.5.1/

all:$(TARGET)
	$(OBJCOPY) -O binary $< $(BIN)
$(TARGET):$(ASM) $(OBJS)
	$(LD) $(ASM) $(OBJS) -Ttext=$(LDADD) $(LDFLAGS) -o $@

%.o:%.S
	$(CC) -c $^
%.o:%.c
	$(CC) -c $^ -Iinclude -Wall -fno-builtin

clean:
	rm -f *.o $(BIN) $(TARGET)


	
