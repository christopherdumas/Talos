#include "keyboard.h"
#include "io.h"
#include "interrupt.h"

unsigned char read_kbd(void)
{
    return inb(KBD_DATA_PORT);
}

char getc()
{
    unsigned char sc;
    while ((sc = read_kbd()) == 0 || inb(0x64) & 0x01);

    return us_keyboard_scancodes[(int) sc];
}

char pollc()
{
    unsigned char sc;
    if ((sc = read_kbd()) != 0 && inb(0x64) & 0x01)
        return us_keyboard_scancodes[sc];
    return '\0';
}
