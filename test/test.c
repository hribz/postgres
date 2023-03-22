#include <stdio.h>
#include <stdlib.h>
#include "postgres.h"
#include "utils/memutils.h"

int main(void) {
  MemoryContext mcxt = AllocSetContextCreate(NULL,
                                             "MyMemoryContext",
                                             ALLOCSET_DEFAULT_SIZES);
  if (mcxt == NULL) {
    printf("Failed to create memory context.\n");
    exit(1);
  }

  char *str1 = MemoryContextAlloc(mcxt, 10 * sizeof(char));
  if (str1 == NULL) {
    printf("Failed to allocate memory.\n");
    exit(1);
  }
  sprintf(str1, "Hello");
  printf("%s ", str1);

  char *str2 = MemoryContextAlloc(mcxt, 10 * sizeof(char));
  if (str2 == NULL) {
    printf("Failed to allocate memory.\n");
    exit(1);
  }
  sprintf(str2, "world!");
  printf("%s\n", str2);

  MemoryContextDelete(mcxt);

  return 0;
}
