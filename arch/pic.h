#pragma once

#include "lib/stdint.h"

#define PIC_VECTOR_BASE 0x20

void pic_remap(void);
void mask_irq(uint8_t irq);
void unmask_irq(uint8_t irq);
void pic_eoi(uint8_t irq);
