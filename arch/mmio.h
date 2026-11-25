#pragma once

#include "lib/stdint.h"

static inline uint32_t mmio_read32(volatile void* base, uint32_t off) {
	return *(volatile uint32_t*)((volatile uint8_t*)base + off);
}

static inline void mmio_write32(volatile void* base, uint32_t off,
								uint32_t value) {
	*(volatile uint32_t*)((volatile uint8_t*)base + off) = value;
}
