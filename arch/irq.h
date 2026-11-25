#pragma once

#include "lib/error.h"
#include "lib/stdint.h"

typedef void (*irq_handler_t)(void* ctx);

// ERR_INVAL: Bad line. ERR_BUSY: Already claimed
int irq_register(uint8_t irq, irq_handler_t handler, void* ctx);
void irq_dispatch(uint32_t irq);
