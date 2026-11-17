#pragma once

#include "../lib/stdint.h"

void pic_remap(void);
void mask_irq(uint8_t irq);
void unmask_irq(uint8_t irq);
