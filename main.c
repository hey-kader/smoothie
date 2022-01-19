#include "slib.c"

int main () {

  system("clear");
  //int d = broadcast_setup("192.168.1.152");
  //printf("%d", d);

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
