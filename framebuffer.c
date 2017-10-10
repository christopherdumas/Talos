#include "io.h"
#include "framebuffer.h"

volatile char* video = (volatile char*) 0xB8000;

unsigned int cursor_x = 0;
unsigned int cursor_y = 0;

unsigned int foreground = WHITE;
unsigned int background = BLACK;

int buflen(string_t buf)
{
    char c = buf[0];
    int tally = 0;

    while (c != '\0')
        c = buf[tally++];

    return tally;
}

void fb_set_foreground(color_t color)
{
    foreground = color;
}

void fb_set_background(color_t color)
{
    background = color;
}

void fb_putc(char c)
{
    unsigned int attrs = (background << 4) | foreground;
    unsigned int cursor_pos = (80 * cursor_y * 2) + cursor_x * 2;

    switch (c) {
    case '\n':
        cursor_y += 1;
        break;

    default:
        video[cursor_pos] = c;
        video[cursor_pos + 1] = attrs;

        cursor_x += 1;
        break;
    }
}

void fb_print(string_t buf)
{
    for (int i = 0; i < buflen(buf); i++) {
        fb_putc(buf[i]);
    }
}

void fb_println(string_t buf)
{
    fb_print(buf);
    cursor_y += 1;
    cursor_x = 0;
}

void fb_clear(color_t color)
{
    unsigned int b = background;
    background = color;
    cursor_x = 0;
    cursor_y = 0;
    for (int i=0; i < 32000; i++) {
        fb_putc(' ');
    }
    cursor_x = 0;
    cursor_y = 0;
    background = b;
}

void fb_move_cursor(unsigned int x, unsigned int y)
{
    cursor_x = x;
    cursor_y = y;

    unsigned int cursor_pos = y * 80 + x;

    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    cursor_pos >> 8);

    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    cursor_pos);
}
