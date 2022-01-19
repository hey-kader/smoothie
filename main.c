#include <stdio.h>
#include "slib.c"

int main () {
  system("clear");

  if (!has_hole ()) {
    printf("making hole...\n");
  }
  else {
    printf("hole found!\n");
  }

  char c;
  do {
    printf("press enter...\n");
  } while ((c = getc(stdin) != '\n'));

  printf("--> :|");
  do {
    if (c == '\n')
      printf("--> :|");
  } while ((c = getc(stdin)) != EOF);

  return 0;
}
