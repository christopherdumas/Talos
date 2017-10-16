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

void serial_config_line(unsigned short com, line_command_t* lc)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), *((unsigned char*) lc));
}

void serial_config_line_default(unsigned short com)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_config_buffer(unsigned short com, fifo_command_t* fc)
{
    outb(SERIAL_FIFO_COMMAND_PORT(com), *((unsigned char*) fc));
}

void serial_config_buffer_default(unsigned short com)
{
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_config_modem(unsigned short com, modem_command_t* mc)
{
    outb(SERIAL_MODEM_COMMAND_PORT(com), *((unsigned char*) mc));
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
    for (int i=0; i < strlen(buf); i++) {
        serial_putc(com, buf[i]);
    }
}

void serial_printn(unsigned short com, int arg, int rad)
{
    char b[12];
    ntoa(arg, rad, b);
    serial_print(com, b);
}
