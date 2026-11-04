#include "kmain.h"
#include "drivers/vga.h"

void kmain() {
	vga_init();
	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	vga_write("Welcome to ");
	vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
	vga_write("CLOS");
	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	vga_write("!\n");
	vga_write("No files, no commands, no input, no problem.\n");
}
