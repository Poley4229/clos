CC      := gcc
LD      := ld
AS      := nasm
 
CFLAGS  := -m32 -nostdlib -nostdinc -fno-builtin -ffreestanding \
		   -fno-stack-protector -fno-pic -fno-pie -Wall -Wextra -O \
		   -Ikernel -nostartfiles -nodefaultlibs -mgeneral-regs-only -I. -std=c2x
ASFLAGS := -f elf32
LDFLAGS := -m elf_i386 -T linker.ld -nostdlib -z noexecstack
 
BUILD   := build
KERNEL  := $(BUILD)/kernel.elf
 
C_SRCS   := $(shell find . -name '*.c')
ASM_SRCS := $(shell find . -name '*.asm')
OBJS     := $(patsubst %.c,$(BUILD)/%.o,$(C_SRCS)) \
            $(patsubst %.asm,$(BUILD)/%_asm.o,$(ASM_SRCS))
 
.PHONY: all run debug clean
 
all: $(KERNEL)
 
$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
 
$(BUILD)/%_asm.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)
 
run: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL)
 
debug: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL) -s -S
 
clean:
	rm -rf $(BUILD)
