#ifndef _INCLUDE_INT_H
#define _INCLUDE_INT_H

#include "idt.h"

#define PIC1		    0x20	/* IO base address for master PIC */
#define PIC2		    0xA0	/* IO base address for slave PIC */

#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)

#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7

#define ICW1_ICW4	    0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	    0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	    0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	    0x10		/* Initialization - required! */

#define ICW4_8086	    0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	    0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	    0x10		/* Special fully nested (not) */

#define PIC_ACK         0x20
#define KBD_DATA_PORT   0x60

typedef enum pic {
    // PIC 1
    TIMER = PIC1_START_INTERRUPT,
    KEYBOARD,
    PIC2_LINK,
    COM2,
    COM1,
    LPT2,
    FLOPPY_DISK,
    LPT1,
    // PIC 2
    REALTIME_CLOCK,
    GENERAL_IO1,
    GENERAL_IO2,
    GENERAL_IO3,
    GENERAL_IO4,
    COPROCESSOR,
    IDE_BUS1,
    IDE_BUS2
} pic_t;

typedef void (*interrupt_callback_t)(cpu_state_t cpu, stack_state_t stack);

static const unsigned char us_keyboard_scancodes[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	// 9
  '9', '0', '-', '=', '\b',	// Backspace
  '\t',			// Tab
  'q', 'w', 'e', 'r',	// 19
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	// Enter key
    0,			// 29   - Control
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	// 39
 '\'', '`',   0,		// Left shift
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			// 49
  'm', ',', '.', '/',   0,				// Right shift
  '*',
    0,	// Alt
  ' ',	// Space bar
    0,	// Caps lock
    0,	// 59 - F1 key ... >
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	// < ... F10
    0,	// 69 - Num lock
    0,	// Scroll Lock
    0,	// Home key
    0,	// Up Arrow
    0,	// Page Up
  '-',
    0,	// Left Arrow
    0,
    0,	// Right Arrow
  '+',
    0,	// 79 - End key
    0,	// Down Arrow
    0,	// Page Down
    0,	// Insert Key
    0,	// Delete Key
    0,   0,   0,
    0,	// F11 Key
    0,	// F12 Key
    0,	// All other keys are undefined
};
idt_entry_t idt[256];

void register_idt(pic_t id, unsigned long base, unsigned short sel, unsigned char flags);
void setup_idt();
void pic_acknowledge(pic_t interrupt);
void send_interrupt();
void set_irq_mask(unsigned char line);
void clear_irq_mask(unsigned char line);
//extern void send_interrupt(pic_t interrupt);

#endif
