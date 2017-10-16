#include "gdt.h"

/*
GDT[0] = {.base=0, .limit=0, .type=0};                     // Selector 0x00 cannot be used
GDT[1] = {.base=0, .limit=0xffffffff, .type=0x9A};         // Selector 0x08 will be our code
GDT[2] = {.base=0, .limit=0xffffffff, .type=0x92};         // Selector 0x10 will be our data
GDT[3] = {.base=&myTss, .limit=sizeof(myTss), .type=0x89}; // You can use LTR(0x18)
*/

void gdt_set_gate(int num,
                  unsigned long base,
                  unsigned long limit,
                  unsigned char access,
                  unsigned char gran)
{
	/* Setup the descriptor base access */
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	/* Setup the descriptor limits */
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void setup_gdt()
{
    /* Our NULL descriptor */
	gdt_set_gate(0, 0, 0, 0, 0);

	/* The second entry is our Code Segment.  The base address
	 * is 0, the limit is 4 gigabytes, it uses 4 kilobyte
	 * granularity, uses 32-bit opcodes, and is a Code Segment
	 * descriptor.  Please check the table above in the tutorial
	 * in order to see exactly what each value means */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	/* The third entry is our Data Segment.  It's exactly the
	 * same as our code segment, but the descriptor type in
	 * this entry's access byte says it's a Data Segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	/* Install the user mode segments into the GDT */
	// gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	// gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    set_gdt((unsigned int) &gdt[0], (sizeof (gdt_entry_t) * 4) - 1);
}
