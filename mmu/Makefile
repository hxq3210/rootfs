
.PHONE:clean

TARGET		:= arm
BIN  		:= $(TARGET).bin	
LDADD		:= 0x50000000
ASM		:= start.o
OBJS		:= entry.o lib.o
OBJS		+= mmu.o
CROSS_COMPILE	:= arm-linux-
CC		:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)ld
OBJCOPY		:= $(CROSS_COMPILE)objcopy
NM		:= $(CROSS_COMPILE)nm
OBJDUMP		:= $(CROSS_COMPILE)objdump

all:$(TARGET)
	$(OBJCOPY) -O binary $< $(BIN)
$(TARGET):$(ASM) $(OBJS)
	$(LD) $(ASM) $(OBJS) -Ttext=$(LDADD) -o $@

%.o:%.S
	$(CC) -c $^
%.o:%.c
	$(CC) -c $^ -Iinclude -Wall -fno-builtin

clean:
	rm -f *.o $(BIN) $(TARGET)


	
