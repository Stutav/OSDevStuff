#include "defines.h"

struct GDT_ptr gp;
struct GDT gdt[5];

extern void GDTSet(uint16_t limit, uint32_t base);
extern void loadGDT();

void gdt_set(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt[num].base0 = (base & 0xFFFF);
	gdt[num].base1 = (base >> 16) & 0xFF;
	gdt[num].base2 = (base >> 24) & 0xFF;
	gdt[num].limit0 = (limit & 0xFFFF); // Shouldn't this be 0xFFFFF?
	gdt[num].gran =	(limit >> 16) & 0X0F;
	gdt[num].gran |= (gran & 0xF0);
	gdt[num].access = access;
}

void gdt_init(){
    terminal_writestring("Loading GDT...");
    gp.limit = (sizeof(struct GDT) * 5) - 1;
    gp.base = (uint32_t)&gdt;

    gdt_set(0, 0, 0, 0, 0);
    gdt_set(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // KCode
    gdt_set(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // KData
    gdt_set(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // UCode
    gdt_set(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // UData

    GDTSet(gp.limit, gp.base);
    loadGDT();
}