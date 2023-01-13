#include "defines.h"

struct IDT_ptr idtp;
struct IDT idt[32];

void idt_set(uint8_t num, uint32_t base, uint16_t segsel, uint8_t flags){
    idt[num].base0 = (base & 0xFFFF);
    idt[num].base1 = (base >> 16) & 0xFFFF;
    idt[num].segsel = segsel;
    idt[num].res = 0;
    idt[num].flags = flags | 0x60;
}

void idt_init(){
    idtp.limit = (sizeof(struct IDT) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    for (int i = 0; i < 32; i++){
        idt_set(i, 0x0, 0x08, 0x8E);
    }

    __asm__ volatile ("lidt %0" : : "m"(idtp));
    __asm__ volatile ("sti");
}