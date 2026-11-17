#include "kmain.h"
#include "arch/idt.h"
#include "arch/pic.h"
#include "drivers/ps2.h"
#include "drivers/vga.h"
#include "shell/shell.h"

void process_kbd(void) {
	char c;
	while (kbd_read(&c)) {
		shell_input(c);
	}
}

void kmain(void) {
	vga_init();
	pic_remap();
	idt_init();
	ps2_setup();
	__asm__ volatile("sti");

	shell_init();

	for (;;) {
		process_kbd();
		__asm__ volatile("hlt");
	}
}
