#ifndef _INCLUDE_FB_H
#define _INCLUDE_FB_H

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGNETA       5
#define BROWN         6
#define LIGHT_GREY    7
#define DARK_GREY     8
#define LIGHT_BLUE    9
#define LIGHT_GREEN   10
#define LIGHT_CYAN    11
#define LIGHT_RED     12
#define LIGHT_MAGNETA 13
#define LIGHT_BROWN   14
#define WHITE         15

int buflen(const char* buf);
void fb_putc(char c);
void fb_print(const char* buf);
void fb_println(const char *buf);
void fb_clear(unsigned char color);
void fb_move_cursor(unsigned int x, unsigned int y);

#endif
