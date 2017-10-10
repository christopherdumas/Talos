#include "framebuffer.h"
#include "string.h"
#include "serial.h"

void kmain(void)
{
    unsigned short com = serial_config_com1_defaults();
    serial_print(com, "Hello serial port!");

    fb_clear(BLACK);

    fb_set_foreground(MAGNETA);
    fb_println("Welcome to TalOS Beta 2");
    fb_set_foreground(WHITE);

    fb_println("TalOS stands for The Awesome Lisp OS");
    fb_println(":)");

    while(1);
    return;
}
