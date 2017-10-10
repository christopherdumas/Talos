#ifndef _INCLUDE_FB_H
#define _INCLUDE_FB_H

#include "string.h"

static const int FB_COMMAND_PORT = 0x3D4;
static const int FB_DATA_PORT    = 0x3D5;

static const int FB_HIGH_BYTE_COMMAND = 14;
static const int FB_LOW_BYTE_COMMAND  = 15;

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

void fb_putc(char c);
void fb_print(string_t buf);
void fb_println(string_t buf);
void fb_printf(string_t str, ...);

void fb_clear(color_t color);
void fb_move_cursor(unsigned int x, unsigned int y);
void fb_set_foreground(color_t color);
void fb_set_background(color_t color);

#endif
