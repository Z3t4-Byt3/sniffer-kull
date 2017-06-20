#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <bsd/stdlib.h>
#include <string.h>
#include <regex.h>
#include "kurl.h"

void init_string (struct string *str) {

  str-> len = 0;
  str-> data = malloc (str-> len+1);

  if (str-> data == NULL) {
    fprintf (stderr, "malloc() failed\n");
    exit (EXIT_FAILURE);
  }

  str-> data[0] = '\0';

}

size_t writefunc (void *ptr, size_t size, size_t nmemb, struct string *str) {

  size_t new_len = str-> len + size*nmemb;
  str-> data = reallocarray (str-> data, new_len+1, 1);

  if (str-> data == NULL) {
    fprintf (stderr, "realloc() failed\n");
    exit (EXIT_FAILURE);
  }

  memcpy (str-> data + str-> len, ptr, size*nmemb);
  str-> data[new_len] = '\0';
  str-> len = new_len;

  return size*nmemb;

}

void regex_error (int return_i, regex_t reg) {

  size_t length;
  char* buffer = NULL;

  length = regerror (return_i, &reg, NULL, 0);
  if (( buffer = (char *) malloc (length)) == NULL) {
    fprintf (stderr, "error: malloc buffer\n");
    exit (EXIT_FAILURE);
  }

  regerror (return_i, &reg, buffer, length);
  fprintf (stderr, "error: %s\n", buffer);

  free (buffer);
  exit (EXIT_FAILURE);

}

char* regex_custom_grep (char *exp, char *string) {

  regex_t reg;
  regmatch_t *array;
  char* return_s;
  int return_i, i, j = 0;

  return_i = regcomp (&reg, exp, REG_EXTENDED);
  if (return_i)
    regex_error (return_i, reg);

  array = malloc (sizeof(regmatch_t));

  return_i = regexec (&reg, string, 1, array, REG_EXTENDED);
  if (!return_i) {
    return_s = malloc (strlen (string) * sizeof(char));
    for ( i=array[0].rm_so ; i<array[0].rm_eo ; ++i ) {
      if (string[i] == '\n') {
        break;
      }
      return_s[j] = string[i];
      ++j;
    }
    return_s[j-1] = '\0';
    regfree (&reg);
    return (return_s);
  }
  else
    regex_error (return_i, reg);

  regfree (&reg);
  return ("error");

}

