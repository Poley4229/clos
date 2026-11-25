global irq_stub_table
extern irq_dispatch

section .text

%macro IRQ_STUB 1
irq%1_stub:
        pusha 
        cld   
        push  dword %1
        call  irq_dispatch
        add   esp, 4
        popa  
        iret  
%endmacro

        IRQ_STUB 0
        IRQ_STUB 1
        IRQ_STUB 2
        IRQ_STUB 3
        IRQ_STUB 4
        IRQ_STUB 5
        IRQ_STUB 6
        IRQ_STUB 7
        IRQ_STUB 8
        IRQ_STUB 9
        IRQ_STUB 10
        IRQ_STUB 11
        IRQ_STUB 12
        IRQ_STUB 13
        IRQ_STUB 14
        IRQ_STUB 15

section .rodata

irq_stub_table:
 dd irq0_stub, irq1_stub, irq2_stub, irq3_stub
 dd irq4_stub, irq5_stub, irq6_stub, irq7_stub
 dd irq8_stub, irq9_stub, irq10_stub, irq11_stub
 dd irq12_stub, irq13_stub, irq14_stub, irq15_stub

