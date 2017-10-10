#include "serial.h"
#include "string.h"
#include "io.h"

void serial_config_baud_rate(unsigned short com,
                             unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com),
         SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),
         (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com),
         divisor & 0x00FF);
}

void serial_config_line(unsigned short com,
                        unsigned short dat_len,
                        unsigned short stp_bts,
                        unsigned short prty_bts,
                        unsigned short brk_ctrl,
                        unsigned short dlab)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com),
         dat_len | stp_bts << 2 | prty_bts << 3 | brk_ctrl << 6 | dlab << 7);
}

void serial_config_line_default(unsigned short com)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_config_buffer(unsigned short com,
                          unsigned short fifo_enabled,
                          unsigned short clr_recvr,
                          unsigned short clr_transmn,
                          unsigned short access,
                          unsigned short bufsz,
                          unsigned short store_bytes)
{
    /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
     * Content: | lvl | bs | r | dma | clt | clr | e |
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com),
         fifo_enabled | clr_recvr << 1 | clr_transmn << 2 | access << 3 | 0 << 4 | bufsz << 5 | store_bytes << 6);
}

void serial_config_buffer_default(unsigned short com)
{
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_config_modem(unsigned short com,
                         unsigned short dtr,
                         unsigned short rtt,
                         unsigned short aux_out1,
                         unsigned short aux_out2,
                         unsigned short loopback,
                         unsigned short autoflow)
{
    /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
     * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com),
        dtr | rtt << 1 | aux_out1 << 2 | aux_out2 << 3 | loopback << 4 | autoflow << 5 | 0 << 6 | 0 << 7);
}

void serial_config_modem_default(unsigned short com)
{
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned short com)
{
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

int serial_config_com1_defaults()
{
    serial_config_baud_rate(SERIAL_COM1_BASE, 2);
    serial_config_buffer_default(SERIAL_COM1_BASE);
    serial_config_line_default(SERIAL_COM1_BASE);
    serial_config_modem_default(SERIAL_COM1_BASE);

    return SERIAL_COM1_BASE;
}

void serial_putc(unsigned short com, char c)
{
    while (!serial_is_transmit_fifo_empty(com));

    outb(com, c);
}

void serial_print(unsigned short com, string_t buf)
{
    for (int i=0; i < buflen(buf); i++) {
        serial_putc(com, buf[i]);
    }
}

void serial_printf(unsigned short com, string_t str, ...)
{
    va_list args;
    va_start(args, str);

    int on_flag = 0;
    int len = buflen(str);
    for (int i=0; i < len; i++) {
        char c = str[i];

        switch (c) {
        case '%':
            on_flag = 1;
        default:
            if (on_flag) {
                switch (c) {
                case 'i':
                    serial_print(itoa(va_arg(args, int)));
                    break;
                case 's':
                    serial_print(va_arg(args, const char*));
                    break;
                case 'b':
                    serial_print(va_arg(args, char*));
                    break;
                }
            } else {
                serial_putc(c);
            }
        }
    }
    va_end(args);
}
