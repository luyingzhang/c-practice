/*
(C) OOMusou 2007 http://oomusou.cnblogs.com

Filename    : int2str_sprintf.cpp
Compiler    : Visual C++ 8.0 / ANSI C
Description : Demo the how to convert int to const char *
Release     : 01/06/2007 1.0
*/
#include "stdio.h"

void int2str(int , char *);

int tmain() {
  int i = 123;
  char s[64];
  int2str(i, s);
  puts(s);
}

void int2str(int i, char *s) {
  sprintf(s,"%d",i);
}
