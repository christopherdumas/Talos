#ifndef _INCLUDE_GDT_H
#define _INCLUDE_GDT_H

typedef struct gdt_entry {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed)) gdt_entry_t;

gdt_entry_t gdt[3];

void setup_gdt();
extern void set_gdt(unsigned int address, unsigned short size);

#endif
