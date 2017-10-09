OBJECTS := loader.o out.o framebuffer.o kmain.o

CC      := ~/.local/bin/bin/i386-elf-gcc-7.2.0
CFLAGS  := -m32 -nostdinc -fno-builtin -nostdlib -nostartfiles -nodefaultlibs -fno-stack-protector \
         -Wall -Wextra -Werror -std=c11 -c

LD      := ~/.local/bin/i386-elf/bin/ld
LDFLAGS := -T link.ld -melf_i386 -nostdlib -nostartfiles -nodefaultlibs

AS      := nasm
ASFLAGS := -f elf32

all: kernel.elf

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	mkisofs -R                          \
		-b boot/grub/stage2_eltorito    \
		-no-emul-boot                   \
		-boot-load-size 4               \
		-A os                           \
		-input-charset utf8             \
		-quiet                          \
		-boot-info-table                \
		-o os.iso                       \
		iso

run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso
