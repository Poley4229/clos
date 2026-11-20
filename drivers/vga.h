#pragma once

#include "../lib/stdint.h"

enum vga_color {
	VGA_BLACK = 0,
	VGA_BLUE,
	VGA_GREEN,
	VGA_CYAN,
	VGA_RED,
	VGA_MAGENTA,
	VGA_BROWN,
	VGA_LIGHT_GREY,
	VGA_DARK_GREY,
	VGA_LIGHT_BLUE,
	VGA_LIGHT_GREEN,
	VGA_LIGHT_CYAN,
	VGA_LIGHT_RED,
	VGA_LIGHT_MAGENTA,
	VGA_YELLOW,
	VGA_WHITE,
};

typedef enum vga_color vga_color;

// Clears screen and resets cursor
void vga_init(void);
// Returns is vga is available
bool vga_avail(void);
// Handles individual chars
void vga_putc(char c);
// Write a string to the screen
void vga_write(const char* s);
// Sets the colours of the terminal
void vga_set_color(vga_color fg, vga_color bg);
// Clears all chars off of the screen
void vga_clear();

