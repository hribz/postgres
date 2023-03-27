#include "postgres.h"

int main() {
	void *a=palloc(10);
  *((char *)a+10)='x';
  return 0;
}
