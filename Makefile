CC      := gcc
LD      := ld
AS      := nasm
 
CFLAGS  := -m32 -nostdlib -nostdinc -fno-builtin -ffreestanding \
		   -fno-stack-protector -fno-pic -fno-pie -nostdlib -Wall -Wextra -O \
		   -Ikernel -nostartfiles -nodefaultlibs
ASFLAGS := -f elf32
LDFLAGS := -m elf_i386 -T linker.ld -nostdlib -z noexecstack
 
BUILD   := build
KERNEL  := $(BUILD)/kernel.elf
 
C_SRCS := $(shell find kernel -name '*.c')
OBJS   := $(BUILD)/boot.o $(patsubst kernel/%.c,$(BUILD)/%.o,$(C_SRCS))
 
.PHONY: all run debug clean
 
all: $(KERNEL)
 
$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
 
$(BUILD)/boot.o: boot/boot.asm | $(BUILD)
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
