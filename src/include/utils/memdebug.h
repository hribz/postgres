/*-------------------------------------------------------------------------
 *
 * memdebug.h
 *	  Memory debugging support.
 *
 * Currently, this file either wraps <valgrind/memcheck.h> or substitutes
 * empty definitions for Valgrind client request macros we use.
 *
 *
 * Portions Copyright (c) 1996-2023, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/utils/memdebug.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef MEMDEBUG_H
#define MEMDEBUG_H

#ifdef USE_VALGRIND
#include <valgrind/memcheck.h>

#elif defined(USE_ASAN)
#include "/home/xiaoyu/gradDesign/llvm-project-postgres/build/lib/clang/13.0.1/include/sanitizer/asan_interface.h"
#define VALGRIND_MAKE_MEM_DEFINED(addr, size) \
 ASAN_UNPOISON_MEMORY_REGION(addr, size)

#define VALGRIND_MAKE_MEM_NOACCESS(addr, size) \
 ASAN_POISON_POST_REGION(addr, size)

#define VALGRIND_MAKE_MEM_UNDEFINED(addr, size) \
 ASAN_UNPOISON_MEMORY_REGION(addr, size)

#define VALGRIND_CHECK_MEM_IS_DEFINED(addr, size) do {} while (0)
#define VALGRIND_CREATE_MEMPOOL(context, redzones, zeroed) do {} while (0)
#define VALGRIND_DESTROY_MEMPOOL(context) do {} while (0)
#define VALGRIND_MEMPOOL_ALLOC(context, addr, size) \
 ASAN_UNPOISON_MEMORY_REGION(addr, size); \
 ASAN_MEMPOOL_ALLOC(addr, size);

#define VALGRIND_MEMPOOL_FREE(context, addr) \
 ASAN_POISON_MEMORY_REGION(addr, size)
#define VALGRIND_MEMPOOL_CHANGE(context, optr, nptr, size) do {} while (0)
#define VALGRIND_MEMPOOL_REALLOC(context, addr, size) \
 ASAN_UNPOISON_MEMORY_REGION(addr, size); \
 ASAN_MEMPOOL_REALLOC(addr, size);

#else
#define VALGRIND_CHECK_MEM_IS_DEFINED(addr, size)			do {} while (0)
#define VALGRIND_CREATE_MEMPOOL(context, redzones, zeroed)	do {} while (0)
#define VALGRIND_DESTROY_MEMPOOL(context)					do {} while (0)
#define VALGRIND_MAKE_MEM_DEFINED(addr, size)				do {} while (0)
#define VALGRIND_MAKE_MEM_NOACCESS(addr, size)				do {} while (0)
#define VALGRIND_MAKE_MEM_UNDEFINED(addr, size)				do {} while (0)
#define VALGRIND_MEMPOOL_ALLOC(context, addr, size)			do {} while (0)
#define VALGRIND_MEMPOOL_FREE(context, addr)				do {} while (0)
#define VALGRIND_MEMPOOL_CHANGE(context, optr, nptr, size)	do {} while (0)
#define VALGRIND_MEMPOOL_REALLOC(context, optr, nptr, size) do {} while (0)
#endif


#ifdef CLOBBER_FREED_MEMORY

/* Wipe freed memory for debugging purposes */
static inline void
wipe_mem(void *ptr, size_t size)
{
	VALGRIND_MAKE_MEM_UNDEFINED(ptr, size);
	memset(ptr, 0x7F, size);
	VALGRIND_MAKE_MEM_NOACCESS(ptr, size);
}

#ifdef USE_ASAN
/* Wipe freed memory for debugging purposes */
static inline void
wipe_mem_free(void *ptr, size_t size)
{
	// VALGRIND_MAKE_MEM_UNDEFINED(ptr + 16, size);
	// memset(ptr + 16, 0x7F, size);
	// VALGRIND_MAKE_MEM_NOACCESS(ptr, size);
	__interceptor_pfree(ptr, size);
}
#endif

#endif							/* CLOBBER_FREED_MEMORY */

#ifdef MEMORY_CONTEXT_CHECKING

static inline void
set_sentinel(void *base, Size offset)
{
	char	   *ptr = (char *) base + offset;

	VALGRIND_MAKE_MEM_UNDEFINED(ptr, 1);
	*ptr = 0x7E;
	VALGRIND_MAKE_MEM_NOACCESS(ptr, 1);
}

static inline bool
sentinel_ok(const void *base, Size offset)
{
	const char *ptr = (const char *) base + offset;
	bool		ret;

	VALGRIND_MAKE_MEM_DEFINED(ptr, 1);
	ret = *ptr == 0x7E;
	VALGRIND_MAKE_MEM_NOACCESS(ptr, 1);

	return ret;
}

#endif							/* MEMORY_CONTEXT_CHECKING */

#ifdef RANDOMIZE_ALLOCATED_MEMORY

void		randomize_mem(char *ptr, size_t size);

#endif							/* RANDOMIZE_ALLOCATED_MEMORY */


#endif							/* MEMDEBUG_H */
