#ifndef _INCLUDE_S_H
#define _INCLUDE_S_H

#include "string.h"

#define SERIAL_COM1_BASE        0x3F8
#define SERIAL_LINE_ENABLE_DLAB 0x80

#define SERIAL_DATA_PORT(base)           (base)
#define SERIAL_FIFO_COMMAND_PORT(base)   (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)   (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)  (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)    (base + 5)

/* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
 * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
 */
typedef struct modem_command {
    int dtr:1;
    int rts:1;
    int ao1:1;
    int ao2:1;
    int lb:1;
    int af:1;
} __attribute__((packed)) modem_command_t;

/* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Content: | d | b | prty  | s | dl  |
 */
typedef struct line_command {
    int dl:2;
    int s:1;
    int prty:3;
    int b:1;
    int d:1;
} __attribute__((packed)) line_command_t;

/* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
 * Content: | lvl | bs | r | dma | clt | clr | e |
 */
typedef struct fifo_command {
    int ed:1;
    int clr:1;
    int clt:1;
    int dma:1;
    int r:1;
    int bs:1;
    int lvl:2;
} __attribute__((packed)) fifo_command_t;

void serial_config_baud_rate(unsigned short com, unsigned short divisor);

void serial_config_line(unsigned short com, line_command_t* lc);
void serial_config_line_default(unsigned short com);

void serial_config_buffer(unsigned short com, fifo_command_t* bc);
void serial_config_buffer_default(unsigned short com);

void serial_config_modem(unsigned short com, modem_command_t* mc);
void serial_config_modem_default(unsigned short com);

int serial_config_com1_defaults();

void serial_putc(unsigned short com, char c);
void serial_print(unsigned short com, string_t buf);
void serial_printn(unsigned short com, int arg, int rad);

#endif
