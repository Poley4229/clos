#include "irq.h"
#include "idt.h"
#include "pic.h"

#define IRQ_COUNT 16
#define IRQ_CASCADE 2

struct irq_slot {
	irq_handler_t fn;
	void* ctx;
};

static struct irq_slot slots[IRQ_COUNT];

extern void (*const irq_stub_table[IRQ_COUNT])(void);

int irq_register(uint8_t irq, irq_handler_t handler, void* ctx) {
	if (irq >= IRQ_COUNT || irq == IRQ_CASCADE || !handler) return ERR_INVAL;
	if (slots[irq].fn) return ERR_BUSY;

	slots[irq].ctx = ctx;
	slots[irq].fn = handler;
	idt_set_gate(PIC_VECTOR_BASE + irq, (uint32_t)irq_stub_table[irq]);
	unmask_irq(irq);
	return 0;
}

void irq_dispatch(uint32_t irq) {
	if (irq < IRQ_COUNT && slots[irq].fn) slots[irq].fn(slots[irq].ctx);
	pic_eoi((uint8_t)irq);
}
