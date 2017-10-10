#include "framebuffer.h"

void kmain(void)
{
    fb_clear(BLACK);
    fb_println("Welcome to TalOS Beta 2");
    fb_println("TalOS stands for The Awesome Lisp OS");
    fb_println(":)");
    while(1);
    return;
}
