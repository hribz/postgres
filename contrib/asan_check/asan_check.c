#include "postgres.h"

#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include "archive/archive_module.h"
#include "common/int.h"
#include "miscadmin.h"
#include "storage/copydir.h"
#include "storage/fd.h"
#include "utils/guc.h"
#include "utils/memutils.h"

PG_MODULE_MAGIC;

int main()
{
	MemoryContextInit();
	void *a=palloc(10);
	// void *a=MemoryContextAlloc(TopMemoryContext, 10);
	*((char *)a)='x';
}
