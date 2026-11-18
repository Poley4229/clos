#pragma once

#include "../lib/stddef.h"

struct command {
	const char* name;
	const char* help;
	void (*run)(int argc, char** argv);
};

extern const struct command COMMANDS[];
extern const size_t COMMAND_COUNT;
