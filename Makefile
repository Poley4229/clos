CC      := gcc
LD      := ld
AS      := nasm
 
CFLAGS  := -m32 -nostdlib -nostdinc -fno-builtin -ffreestanding \
		   -fno-stack-protector -fno-pic -fno-pie -nostdlib -Wall -Wextra -O \
		   -Ikernel -nostartfiles -nodefaultlibs -mgeneral-regs-only -std=c2x
ASFLAGS := -f elf32
LDFLAGS := -m elf_i386 -T linker.ld -nostdlib -z noexecstack
 
BUILD   := build
KERNEL  := $(BUILD)/kernel.elf
 
C_SRCS   := $(shell find kernel -name '*.c')
ASM_SRCS := $(shell find kernel -name '*.asm')
OBJS     := $(BUILD)/boot.o \
            $(patsubst kernel/%.c,$(BUILD)/%.o,$(C_SRCS)) \
            $(patsubst kernel/%.asm,$(BUILD)/%_asm.o,$(ASM_SRCS))
 
.PHONY: all run debug clean
 
all: $(KERNEL)
 
$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
 
$(BUILD)/boot.o: boot/boot.asm | $(BUILD)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/%_asm.o: kernel/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/%.o: kernel/%.c
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
