#include "shell.h"
#include "../drivers/vga.h"
#include "../lib/string.h"
#include "commands.h"

#define SHELL_LINE_MAX 128
#define SHELL_MAX_ARGS 8

static char line[SHELL_LINE_MAX];
static size_t line_len;

static void prompt(void) {
	vga_write("> ");
}

static int tokenize(char* s, char** argv) {
	int argc = 0;
	// Splits based on spaces
	while (*s && argc < SHELL_MAX_ARGS) {
		while (*s == ' ')
			*s++ = '\0';
		if (!*s) break;
		argv[argc++] = s;
		while (*s && *s != ' ')
			s++;
	}
	return argc;
}

static void execute(void) {
	char* argv[SHELL_MAX_ARGS];
	int argc = tokenize(line, argv);
	if (argc == 0) return;

	for (size_t i = 0; i < COMMAND_COUNT; i++) {
		if (strcmp(argv[0], COMMANDS[i].name) == 0) {
			COMMANDS[i].run(argc, argv);
			return;
		}
	}
	vga_write("unknown command: ");
	vga_write(argv[0]);
	vga_write("\n");
}

void shell_init(void) {
	line_len = 0;

	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	vga_write("Welcome to ");
	vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
	vga_write("CLOS");
	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	vga_write("!\n");
	vga_write("MASSIVE SECURITY FLAW JUST ADD (it is input)\n");

	prompt();
}

void shell_input(char c) {
	if (c == '\n') {
		vga_putc('\n');
		line[line_len] = '\0';
		execute();
		line_len = 0;
		prompt();
	}
	else if (c == '\b') {
		if (line_len > 0) {
			line_len--;
			vga_putc('\b');
		}
	}
	else if (line_len < SHELL_LINE_MAX - 1) {
		line[line_len++] = c;
		vga_putc(c);
	}
}
