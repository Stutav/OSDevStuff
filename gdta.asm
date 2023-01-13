gdtr: .word 0
      .long 0

.global GDTSet
GDTSet:
    movw 4(%esp), %ax
    movw %ax, (gdtr)
    movl 8(%esp), %eax
    movl %eax, (gdtr + 2)
    lgdt (gdtr)
    ret

.global loadGDT
loadGDT:
    jmp $0x08,$.reload_CS

.reload_CS:
    mov $0x10, %ax
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
    ret
