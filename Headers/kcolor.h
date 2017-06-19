#ifndef KCOLOR_H
#define KCOLOR_H

#define OFF 0
#define BOLD 1
#define UNDERSCORE 4
#define BLINK 5

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

void setcolor (int atributo, int cor);
void nocolor (void);
void printf_color (int atributo, int cor, char* msg);
void print_error (char* msg);

#endif

