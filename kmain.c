#include "framebuffer.h"

void kmain(void)
{
    fb_clear(BLACK);
    fb_print("Hello world!");
    while(1);
    return;
}
