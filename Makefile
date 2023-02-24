# top level Makefile

export ARCH=arch/i386
export HOST=i686-elf

export AR=$(HOST)-ar
export AS=$(HOST)-as
export CC=$(HOST)-gcc --sysroot=$(SYSROOT) -isystem=/usr/include

export SYSROOT=$(shell pwd)/sysroot
export BOOT_DIR=$(SYSROOT)/boot
export USR_DIR=$(SYSROOT)/usr
export INCLUDE_DIR=$(USR_DIR)/include/.
export LIB_DIR=$(USR_DIR)/lib/.

export C_FLAGS=-g -O2 -Wall -Wextra -std=gnu11 -ffreestanding
export AS_FLAGS=
export LINKER_FALGS=-nostdlib -lk -lgcc 

.PHONY: all install-headers install clean
all: install-headers
	cd libc/ && make all && make install
	cd kernel/ && make all && make install

install-headers:
	mkdir -p $(INCLUDE_DIR)
	cd libc/ && make install-headers
	cd kernel/ && make install-headers

clean:
	cd libc/ && make clean
	cd kernel/ && make clean
	rm -rf $(SYSROOT)
