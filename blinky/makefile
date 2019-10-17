###################################################
PROJ_NAME=blinky

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2 -Wall -T"../compilation/lpc1115.ld"
CFLAGS += -nostdlib -Xlinker -Map="../compilation/lpc1115.map" -Xlinker --gc-sections -Xlinker -print-memory-usage
CFLAGS += -mthumb -mcpu=cortex-m0 --specs=nosys.specs

LPCXPRESSO_DIR = /usr/local/lpcxpresso_8.2.0_647/lpcxpresso/bin
TARGET = LPC1115/303
FLASH_DRIVER = LPC11_12_13_64K_8K.cfx

DEBUGGER_ID = 0471:0xdf55
BOOT_IMAGE_NAME = LPCXpressoWIN.enc
###################################################

vpath %.c src

ROOT=$(shell pwd)

SRCS = src/main.c \
../compilation/src/system_LPC11xx.c \
../compilation/startup_lpc11xx.c

OBJS = $(SRCS:.c=.o)

###################################################

.PHONY: proj

all: proj

proj: 	$(PROJ_NAME).axf

$(PROJ_NAME).axf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -I"inc/" -I"../compilation/inc"
	$(OBJCOPY) -O ihex $(PROJ_NAME).axf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).axf $(PROJ_NAME).bin

clean:
	rm -f $(PROJ_NAME).axf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	
bootFlash:
	dfu-util -d 0x$(DEBUGGER_ID) -c 0 -t 2048 -R -D $(LPCXPRESSO_DIR)/$(BOOT_IMAGE_NAME)
	$(LPCXPRESSO_DIR)/crt_emu_cm_redlink -p$(TARGET) -vendor=NXP -flash-load-exec "(PROJ_NAME).axf" -flash-driver=$(FLASH_DRIVER)

flash:
	$(LPCXPRESSO_DIR)/crt_emu_cm_redlink -p$(TARGET) -vendor=NXP -flash-load-exec "$(PROJ_NAME).axf" -flash-driver=$(FLASH_DRIVER)
