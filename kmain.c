#include "framebuffer.h"
#include "string.h"
#include "serial.h"
#include "interrupt.h"
#include "keyboard.h"
#include "gdt.h"

extern void call_keyboard_handler(char eflags, char cs, char eip, char error_code_maybe);

void keyboard_handler()
{
    pic_acknowledge(KEYBOARD);
    fb_putc(pollc());
}

void ksetup(void)
{
    fb_clear(BLACK);
    fb_println_log(SUCCESS, "Interrupt setup!");
    setup_gdt();
    setup_idt();
}

void kmain(void)
{
    register_idt(KEYBOARD, (unsigned int) call_keyboard_handler, 0x08, 0x8E);
    // Intro!
    fb_set_foreground(MAGNETA);
    fb_println("Welcome to TalOS Beta 0.3");
    fb_set_foreground(WHITE);
    fb_println("TalOS stands for The Awesome Lisp OS");
    fb_putc('>');

    while (1);
    return;
}
