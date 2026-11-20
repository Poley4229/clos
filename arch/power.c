#include "power.h"
#include "drivers/vga.h"
#include "io.h"

void power_shutdown(void) {
	// QEMU (new)
	outw(0x604, 0x2000);
	// QEMU (old)
	outw(0xB004, 0x2000);

	// Failed
	if (vga_avail()) vga_write("Shutdown failed. Halting indefinitely\n");

	for (;;) {
		__asm__ volatile("cli; hlt");
	}
}
