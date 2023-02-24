# lib Makefile

C_SRC=$(shell find . -name "*.c")
C_OBJ=$(patsubst %.c, %.o, $(C_SRC))

TARGET=libk.a

.PHONY: all begin install install-headers clean
all: begin $(TARGET)

begin:
	@echo
	@echo ===========================================
	@echo ========== Start of lib Makefile ==========
	@echo ===========================================
	
$(TARGET): $(C_OBJ)
	@echo
	@echo "Linking lib objects..."
	$(AR) rcs $@ $(C_OBJ)

$(C_OBJ): %.o: %.c
	@echo
	@echo "Compiling lib C code '$<'..."
	$(CC) -MD -c $< -o $@ $(C_FLAGS) -Iinclude

install:
	@echo
	@echo "Installing lib binary..."
	mkdir -p $(LIB_DIR)
	cp $(TARGET) $(LIB_DIR)

install-headers:
	@echo
	@echo "Installing lib headers..."
	cp -R --preserve=timestamps include/. $(INCLUDE_DIR)

clean:
	rm -f $(S_OBJ) $(C_OBJ) $(patsubst %.c, %.d, $(C_SRC)) $(TARGET)
