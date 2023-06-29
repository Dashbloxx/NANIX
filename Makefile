CC = gcc
LD = ld
AS = as
CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
LDFLAGS = -Tlinker.ld -m elf_i386

SRC_DIR = kernel
OBJ_DIR = $(SRC_DIR)

C_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_FILES))

ASM_FILES := $(wildcard $(SRC_DIR)/*.S)
ASM_OBJ_FILES := $(patsubst $(SRC_DIR)/%.S, $(OBJ_DIR)/%.o, $(ASM_FILES))

all: kernel.bin

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	$(AS) --32 $< -o $@

kernel.bin: $(OBJ_FILES) $(ASM_OBJ_FILES)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o kernel.bin
