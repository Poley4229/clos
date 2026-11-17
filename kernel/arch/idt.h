#pragma once

#include "../lib/stdint.h"

void idt_init(void);
void idt_set_gate(uint8_t n, uint32_t handler);
