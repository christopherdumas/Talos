#ifndef _INCLUDE_STR_H
#define _INCLUDE_STR_H

typedef const char* string_t;
typedef char* buffer_t;

int buflen(string_t buf);
int atoi(string_t str);
string_t itoa(int number, buffer_t str);

#endif
