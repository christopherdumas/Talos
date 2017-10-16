#include "interrupt.h"
#include "framebuffer.h"
#include "io.h"

void register_idt(pic_t id, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[id].base_lo = base & 0x0000ffff;
    idt[id].base_hi = (base & 0xffff0000) >> 16;

    idt[id].flags = flags;
    idt[id].sel = sel;
    idt[id].always0 = 0;
    clear_irq_mask(id);
}

void remap_pic(int offset1, int offset2)
{
    // save masks
	unsigned char
        a1 = inb(PIC1_DATA),
        a2 = inb(PIC2_DATA);

    // start the initialization sequence (in cascade mode)
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);

	outb(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
	outb(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
	outb(PIC1_DATA, 4);       // ICW3: tell Master PIC that there is a slave PIC at IRQ2
	outb(PIC2_DATA, 2);       // ICW3: tell Slave PIC its cascade identity

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, a1); // restore saved masks.
	outb(PIC2_DATA, a2);
}

void setup_idt()
{
    idt_ptr_t idtp;
    remap_pic(0x20, 0x28);

    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    fb_println_log(SUCCESS, "interrupt limit set");

    idtp.base = (unsigned long) &idt;
    fb_println_log(SUCCESS, "interrupt base set");

    // Points the processor's internal register to the new IDT
    load_idt(&idtp);
    fb_println_log(SUCCESS, "interrupts fully set up");
}

void pic_acknowledge(unsigned int interrupt)
{
    outb(PIC1_COMMAND, PIC_ACK);

    if (interrupt > PIC2_START_INTERRUPT)
        outb(PIC2_COMMAND, PIC_ACK);
}

void set_irq_mask(unsigned char line)
{
    unsigned short port;
    unsigned char value;

    if (line < 40)
        port = PIC1_DATA;
    else {
        port = PIC2_DATA;
        line -= 40;
    }
    value = inb(port) | (1 << line);
    outb(port, value);
}

void clear_irq_mask(unsigned char line)
{
    unsigned short port;
    unsigned char value;

    if (line < 40)
        port = PIC1_DATA;
    else {
        port = PIC2_DATA;
        line -= 40;
    }
    value = inb(port) & ~(1 << line);
    outb(port, value);
}
