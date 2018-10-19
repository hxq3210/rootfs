
.PHONY : clean

TARGET 	:= led
BIN	:= $(TARGET).bin
ASMS	:= start.o
OBJS	:= lib.o led.o 
OBJS	+= app.o

LDADD	:= 0x50000000

CROSS_COMPILE	:= arm-linux-
CC		:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)ld
OBJCOPY		:= $(CROSS_COMPILE)objcopy
OBJDUMP		:= $(CROSS_COMPILE)objdump
NM		:= $(CROSS_COMPILE)nm

###################################

$(BIN) : $(TARGET)
	$(OBJCOPY) -O binary $< $@;
	$(NM) $(TARGET) > $(TARGET).map;

$(TARGET) : $(ASMS)  $(OBJS)
	$(LD) $(ASMS) $(OBJS) -Ttext=$(LDADD) -o $@

%.o : %.S
	$(CC) -c $< -o $@
%.o : %.c
	$(CC) -c $^ -Iinclude -o $@

clean:
	rm -f $(TARGET) $(BIN) *.o $(TARGET).map
