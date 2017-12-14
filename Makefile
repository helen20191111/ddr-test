
PATH=/home/sv/sv-ds03-system/sources/linux-x86/toolchain/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/bin:$PATH
CROSS_COMPILE := arm-linux-gnueabihf-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
LD := $(CROSS_COMPILE)ld
FLAG := -L${SDK_PATH}/${TARGET_SYS}/usr/lib

testing-ddr: testing-ddr.c
	$(CC) testing-ddr.c -o testing-ddr $(FLAG) 

