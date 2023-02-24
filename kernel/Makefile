# kernel Makefile

S_SRC=$(shell find . -name "*.S")
S_OBJ=$(patsubst %.S, %.o, $(S_SRC))

C_SRC=$(shell find . -name "*.c")
C_OBJ=$(patsubst %.c, %.o, $(C_SRC))

LINKER=$(ARCH)/linker.ld

TARGET=SteinsOS.kernel

.PHONY: all begin install install-headers clean 
all: begin $(TARGET)

begin:
	@echo
	@echo ==============================================
	@echo ========== Start of kernel Makefile ==========
	@echo ==============================================

$(TARGET): $(S_OBJ) $(C_OBJ)
	@echo
	@echo "Linking kernel objects..."
	$(CC) -T $(LINKER) $(S_OBJ) $(C_OBJ) -o $@ $(C_FLAGS) $(LINKER_FALGS)

$(S_OBJ): %.o: %.S
	@echo
	@echo "Compiling kernel assembly '$<'..."
	$(AS) $< -o $@ $(AS_FLAGS)

$(C_OBJ): %.o: %.c
	@echo
	@echo "Compiling kernel C code '$<'..."
	$(CC) -MD -c $< -o $@ $(C_FLAGS)

install: $(TARGET)
	@echo
	@echo "Installing kernel binary..."
	mkdir -p $(BOOT_DIR)
	cp $(TARGET) $(BOOT_DIR)

install-headers:
	@echo
	@echo "Installing kernel headers..."
	cp -R --preserve=timestamps include/. $(INCLUDE_DIR)

clean:
	rm -f $(S_OBJ) $(C_OBJ) $(patsubst %.c, %.d, $(C_SRC)) $(TARGET)
