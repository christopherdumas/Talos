#ifndef _INCLUDE_FB_H
#define _INCLUDE_FB_H

#include "string.h"

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

typedef enum colors {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGNETA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGNETA,
    LIGHT_BROWN,
    WHITE
} color_t;

typedef enum log_level {
    SUCCESS,
    WARNING,
    DANGER
} log_level_t;

unsigned int cursor_x, cursor_y;

void fb_putc(char c);
void fb_print(string_t buf);
void fb_println(string_t buf);
void fb_printn(int arg, int rad);

void fb_clear(color_t color);
void fb_move_cursor(unsigned int x, unsigned int y);
void fb_set_foreground(color_t color);
void fb_set_background(color_t color);
void fb_print_log(log_level_t ll, string_t str);
void fb_println_log(log_level_t ll, string_t str);

#endif
