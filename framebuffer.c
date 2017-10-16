#include "io.h"
#include "framebuffer.h"

volatile char* video = (volatile char*) 0xB8000;

unsigned int cursor_x = 0, cursor_y = 0;

unsigned int foreground = WHITE, background = BLACK;

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
    unsigned int cursor_pos = (80 * cursor_y) + cursor_x;

    switch (c) {
    case '\n':
        cursor_y += 2;
        cursor_x = 0;
        break;

    default:
        video[cursor_pos] = c;
        video[cursor_pos + 1] = attrs;

        cursor_x += 2;
        break;
    }
}

void fb_print(string_t buf)
{
    int len = strlen(buf)-1;
    for (int i = 0; i < len; i++) {
        fb_putc(buf[i]);
    }
}

void fb_println(string_t buf)
{
    fb_print(buf);
    cursor_y += 2;
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
    cursor_x = x*2;
    cursor_y = y*2;

    unsigned int cursor_pos = cursor_y * 80 + cursor_x;

    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    cursor_pos >> 8);

    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    cursor_pos);
}


void fb_printn(int arg, int rad)
{
    char b[12];
    ntoa(arg, rad, b);
    fb_print(b);
}

void fb_print_log(log_level_t ll, string_t str)
{
    fb_print("[ ");
    switch (ll)
    {
    case SUCCESS:
        fb_set_foreground(GREEN);
        fb_print(" ok ");
        break;
    case WARNING:
        fb_set_foreground(BROWN);
        fb_print("warn");
        break;
    case DANGER:
        fb_set_foreground(RED);
        fb_print("err ");
        break;
    }
    fb_set_foreground(WHITE);
    fb_print(" ] ");
    fb_print(str);
}

void fb_println_log(log_level_t ll, string_t str)
{
    fb_print_log(ll, str);
    cursor_y += 2;
    cursor_x = 0;
}
