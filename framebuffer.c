#include "io.h"
#include "framebuffer.h"

char *framebuf = (char *) 0x000B8000;

unsigned int cursor_x = 0;
unsigned int cursor_y = 0;


unsigned int buflen(const char* buf)
{
    char c = buf[0];
    unsigned int tally = 0;
    while (c != '\0') {
        tally++;
        c = buf[tally];
    }
    return tally+1;
}

void fb_write_char(unsigned int x, unsigned int y,
                   char c, unsigned char fg, unsigned char bg)
{
    unsigned int pos = (y * 80) + x;
    framebuf[pos] = c;
    framebuf[pos + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_write(unsigned int x, unsigned int y,
              const char* buf, unsigned char fg, unsigned char bg)
{
    for (unsigned int i = 0; i < buflen(buf); i++) {
        fb_write_char(x+i, y, buf[i], fg, bg);
    }
}

void fb_move_cursor(unsigned int x, unsigned int y)
{
    cursor_x = x;
    cursor_y = y;

    unsigned int pos = (y * 80) + x;
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);

    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
}

void fb_print(const char *buf)
{
    fb_write(cursor_x, cursor_y, buf, WHITE, BLACK);

    unsigned int nx = cursor_x + buflen(buf) % 25;
    unsigned int ny = nx / 25;
    fb_move_cursor(nx, ny);
}

void fb_println(const char *buf)
{
    fb_print(buf);
    cursor_y++;
}
