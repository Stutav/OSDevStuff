all:
	~/opt/cross/bin/i686-elf-as boot.asm -o boot.o
	~/opt/cross/bin/i686-elf-as gdta.asm -o gdta.o
	nasm -felf32 idta.asm -o idta.o
	~/opt/cross/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -g
	~/opt/cross/bin/i686-elf-gcc -c gdt.c -o gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -g
	~/opt/cross/bin/i686-elf-gcc -c idt.c -o idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -g
	~/opt/cross/bin/i686-elf-gcc -c isr.c -o isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -g
	~/opt/cross/bin/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib isr.o idt.o idta.o boot.o gdt.o gdta.o kernel.o -lgcc -g
	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir