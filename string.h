#ifndef _INCLUDE_STR_H
#define _INCLUDE_STR_H

typedef const char* string_t;

int strlen(string_t buf);
int atoi(string_t str);
void ntoa(int number, int base, char str[]);

#endif
