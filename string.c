#include "string.h"

int strlen(string_t buf)
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

void ntoa(int number, int base, char str[])
{
    char rstr[12];
    int i = 0, n = number, j = 0;

    while (n > 0) {
        rstr[i++] = "0123456789abcdef"[n % base];
        n /= base;
    }

    for (j = 0; j < 12; j++) {
        str[j] = rstr[(i--)-1];
    }

    if (number < 0) {
        // Shift over
        for (int j=1; j < i; j++)
            str[j] = str[j - 1];
        // Add sign
        str[0] = '-';
    }

    // Add terminator
    str[j] = '\0';
}
