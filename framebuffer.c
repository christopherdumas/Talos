#include "io.h"
#include "framebuffer.h"

volatile char* video = (volatile char*) 0xB8000;

unsigned int cursor_pos = 0;

unsigned int foreground = WHITE;
unsigned int background = BLACK;

int buflen(const char* buf)
{
    char c = buf[0];
    unsigned int tally = 0;
    while (c != '\0') {
        tally++;
        c = buf[tally];
    }
    return tally+1;
}

void fb_putc(char c)
{
    unsigned int attrs = (background << 4) | foreground;

    switch (c) {
    case '\n':
        cursor_pos += 160;
        break;

    default:
        video[cursor_pos] = c;
        video[cursor_pos + 1] = attrs;

        cursor_pos += 2;
        break;
    }
}

void fb_print(const char* buf)
{
    for (int i = 0; i < buflen(buf); i++) {
        fb_putc(buf[i]);
    }
}

void fb_println(const char *buf)
{
    fb_print(buf);
    cursor_pos += 160;
}

void fb_clear(unsigned char color)
{
    unsigned int b = background;
    background = color;
    cursor_pos = 0;
    for (int i=0; i < 32000; i++) {
        fb_putc(' ');
    }
    cursor_pos = 0;
    background = b;
}

void fb_move_cursor(unsigned int x, unsigned int y)
{
    char pos = y * 80 + x;
    cursor_pos = pos;

    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos >> 8);

    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos);
}
