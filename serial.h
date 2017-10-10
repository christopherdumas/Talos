#ifndef _INCLUDE_S_H
#define _INCLUDE_S_H

#include "string.h"

static const int SERIAL_COM1_BASE        = 0x3F8;

#define SERIAL_DATA_PORT(base)           (base)
#define SERIAL_FIFO_COMMAND_PORT(base)   (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)   (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)  (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)    (base + 5)

static const int SERIAL_LINE_ENABLE_DLAB = 0x80;

void serial_config_baud_rate(unsigned short com,
                             unsigned short divisor);

void serial_config_line(unsigned short com,
                        unsigned short dat_len,
                        unsigned short stp_bts,
                        unsigned short prty_bts,
                        unsigned short brk_ctrl,
                        unsigned short dlab);
void serial_config_line_default(unsigned short com);

void serial_config_buffer(unsigned short com,
                          unsigned short fifo_enabled,
                          unsigned short clr_recvr,
                          unsigned short clr_transmn,
                          unsigned short access,
                          unsigned short bufsz,
                          unsigned short store_bytes);
void serial_config_buffer_default(unsigned short com);

void serial_config_modem(unsigned short com,
                         unsigned short dtr,
                         unsigned short rtt,
                         unsigned short aux_out1,
                         unsigned short aux_out2,
                         unsigned short loopback,
                         unsigned short autoflow);
void serial_config_modem_default(unsigned short com);


int serial_config_com1_defaults();

void serial_putc(unsigned short com, char c);
void serial_print(unsigned short com, string_t buf);

#endif
