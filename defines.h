#pragma once
#include <stdint.h>

/*
    STRUCTURES
*/

// GDT Definitions
struct GDT_ptr{
    uint16_t limit;
    uint32_t base;
};

struct GDT{
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t access;
    uint8_t gran;
    uint8_t base2;
}__attribute__((packed));

// IDT Definitions
struct IDT_ptr{
    uint16_t limit;
    uint32_t base;
};

struct IDT{
    uint16_t base0;
    uint16_t segsel;
    uint8_t res;
    uint8_t flags;
    uint16_t base1;
}__attribute__((packed));

/*
    FUNCTIONS
*/

// Writing everywhere
void terminal_writestring(const char* data);

// Converts integer to string
char* itoa(int res);

// I/O Stuff
static inline void outb(uint16_t port, uint8_t val){
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port){
    uint8_t ret;
    asm volatile ( "inb %1, %0": "=a"(ret): "Nd"(port) );
    return ret;
}

// GDT Stuff
void gdt_set(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_init();

// Interrupt Stuff
void idt_set(uint8_t num, uint32_t base, uint16_t segsel, uint8_t flags);
void idt_init();
void exception_handler(uint8_t id);
void pic_acknowledge(uint32_t interrupt);
uint8_t read_scan_code();