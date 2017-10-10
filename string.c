#include "string.h"

int buflen(string_t buf)
{
    char c = buf[0];
    int tally = 0;

    while (c != '\0')
        c = buf[tally++];

    return tally;
}

int atoi(string_t str)
{
    int res = 0;
    for (int i=0; str[i] != '\0'; i++)
        res = res*10 + str[i]-'0';
    return res;
}

string_t itoa(int number, buffer_t str)
{
    int x, i = 0;
    if (number < 0)
        x = -number;
    else
        x = number;

    while (x > 0) {
        int digit = x % 10;
        str[i++] = digit + '0';
        x /= 10;
    }

    if (number < 0)
        str[i++] = '-';

    int len = i - 1;
    for (int j = len; j > 0; j--) {
        str[j] = str[len-j];
    }

    return str;
}
