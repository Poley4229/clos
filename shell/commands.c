#include "commands.h"

#include "../drivers/vga.h"
#include "arch/io.h"
#include "arch/power.h"

static void cmd_clos(int argc, char** argv) {
	(void)argc;
	(void)argv;
	vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
	vga_write("CLOS");
	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	vga_write(", a small, pointless and stupid OS.\n");
}

static void cmd_help(int argc, char** argv) {
	(void)argc;
	(void)argv;
	for (size_t i = 0; i < COMMAND_COUNT; i++) {
		vga_write(COMMANDS[i].name);
		vga_write(": ");
		vga_write(COMMANDS[i].help);
		vga_write("\n");
	}
}

static void cmd_echo(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		vga_write(argv[i]);
		vga_putc(' ');
	}
	vga_putc('\n');
}

static void cmd_clear(int argc, char** argv) {
	(void)argc;
	(void)argv;
	vga_clear();
}

static void cmd_shutdown(int argc, char** argv) {
	(void)argc;
	(void)argv;
	power_shutdown();
}

static void cmd_reboot(int argc, char** argv) {
	(void)argc;
	(void)argv;
	power_reboot();
}

const struct command COMMANDS[] = {
	{"clos", "about this OS", cmd_clos},
	{"help", "list commands", cmd_help},
	{"echo", "writes arguments", cmd_echo},
	{"clear", "clears the terminal", cmd_clear},
	{"shutdown", "shutdown the pc (only works on VMs)", cmd_shutdown},
	{"reboot", "reboots the pc", cmd_reboot},
};

const size_t COMMAND_COUNT = sizeof(COMMANDS) / sizeof(COMMANDS[0]);
