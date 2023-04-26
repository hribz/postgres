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

static int max_size = 8192 * 2 + 1;

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(asan_check);
PG_FUNCTION_INFO_V1(buffer_overflow);
PG_FUNCTION_INFO_V1(double_free);
PG_FUNCTION_INFO_V1(use_after_free);

Datum
asan_check(PG_FUNCTION_ARGS)
{
	void *a;
	for(int i=1;i<max_size;i++){
		a=palloc(i);
		for(int j=0;j<i;j++)
			*((char *)a+j)='x';
		a=repalloc(a, max_size - i);
		for(int j=0;j<max_size - i;j++)
			*((char *)a+j)='x';
	}
	MemoryContextReset(CurrentMemoryContext);
	a=palloc(8);

	PG_RETURN_INT32(0);
}

Datum
buffer_overflow(PG_FUNCTION_ARGS)
{
	void *a=palloc(10);
	*((char *)a+17)='x';
	pfree(a);

	PG_RETURN_INT32(0);
}

Datum
double_free(PG_FUNCTION_ARGS)
{
	void *a=palloc(10);
	pfree(a);
	pfree(a);

	PG_RETURN_INT32(0);
}

Datum
use_after_free(PG_FUNCTION_ARGS)
{
	void *a=palloc(10);
	pfree(a);
	*((char *)a)='x';

	PG_RETURN_INT32(0);
}
