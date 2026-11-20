#include "vga.h"

#include "../arch/io.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA 0x3D5
#define VGA_TAB_WIDTH 4

static size_t cursor_row;
static size_t cursor_col;
static uint8_t current_color = (VGA_BLACK << 4) | VGA_LIGHT_GREY;

static bool available = false;

static uint16_t make_entry(char c, uint8_t color) {
	return (uint16_t)(uint8_t)c | ((uint16_t)color << 8);
}

static void update_hw_cursor(void) {
	uint16_t pos = (uint16_t)(cursor_row * VGA_WIDTH + cursor_col);
	outb(VGA_CRTC_INDEX, 0x0F);
	outb(VGA_CRTC_DATA, (uint8_t)(pos & 0xFF));
	outb(VGA_CRTC_INDEX, 0x0E);
	outb(VGA_CRTC_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

static void scroll(void) {
	volatile uint16_t* buf = VGA_MEMORY;

	for (size_t i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {
		buf[i] = buf[i + VGA_WIDTH];
	}
	for (size_t i = 0; i < VGA_WIDTH; i++) {
		buf[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = make_entry(' ', current_color);
	}
	cursor_row = VGA_HEIGHT - 1;
}

static void newline(void) {
	cursor_col = 0;
	if (++cursor_row >= VGA_HEIGHT) scroll();
}

void vga_clear(void) {
	volatile uint16_t* buf = VGA_MEMORY;
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		buf[i] = make_entry(' ', current_color);
	}
	cursor_row = 0;
	cursor_col = 0;
	update_hw_cursor();
}

void vga_init(void) {
	vga_clear();
	available = true;
}

bool vga_avail(void) {
	return available;
}

void vga_set_color(enum vga_color fg, enum vga_color bg) {
	current_color = (uint8_t)((bg << 4) | fg);
}

static void put_char_no_cursor(char c) {
	switch (c) {
	case '\n': newline(); break;
	case '\r': cursor_col = 0; break;
	case '\t': do { put_char_no_cursor(' ');
		} while (cursor_col % VGA_TAB_WIDTH != 0);
		break;
	case '\b':
		if (cursor_col > 0) {
			cursor_col--;
		}
		else if (cursor_row > 0) {
			cursor_row--;
			cursor_col = VGA_WIDTH - 1;
		}
		VGA_MEMORY[cursor_row * VGA_WIDTH + cursor_col] =
			make_entry(' ', current_color);
		break;
	default:
		VGA_MEMORY[cursor_row * VGA_WIDTH + cursor_col] =
			make_entry(c, current_color);
		if (++cursor_col >= VGA_WIDTH) newline();
		break;
	}
}

void vga_putc(char c) {
	put_char_no_cursor(c);
	update_hw_cursor();
}

void vga_write(const char* s) {
	while (*s)
		put_char_no_cursor(*s++);
	update_hw_cursor();
}
