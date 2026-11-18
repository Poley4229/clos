global irq1_stub
extern ps2_irq_handler

section .text

irq1_stub:
        pusha 
        cld   
        call  ps2_irq_handler
        popa  
        iret  

