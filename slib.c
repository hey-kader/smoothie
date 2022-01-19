#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int has_hole (void);

int has_hole () {
  FILE *fp = fopen ("hole", "r");
  if (fp == NULL) {
      mkdir ("hole", S_IRWXU);
      return 0;
  }
  else
    return 1;
}
