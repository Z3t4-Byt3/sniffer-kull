#include <stdio.h>
#include <stdlib.h>
#include "kcolor.h"

void setcolor (int atributo, int cor) {
  printf ("%c[%d;%dm", 0x1B, atributo, cor);
}

void nocolor (void) {
  printf ("%c[%dm", 0x1B, 0);
}

void printf_color (int atributo, int cor, char* msg) {
  setcolor (atributo, cor);
  printf ("%s", msg);
  nocolor ();
}

void print_error (char* msg) {
  fprintf (stderr, "%c[%d;%dm%s\n%c[%dm", 0x1B, OFF, 
      RED, msg, 0x1B, 0);
  exit (EXIT_FAILURE);
}

