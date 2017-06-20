#ifndef KURL_H
#define KURL_H

#include <regex.h>

struct string {
  char* data;
  size_t len;
};

void init_string (struct string *str);
size_t writefunc (void *ptr, size_t size, size_t nmemb, struct string *str);

void regex_error (int return_i, regex_t reg);
char* regex_custom_grep (char *exp, char* string);

#endif
