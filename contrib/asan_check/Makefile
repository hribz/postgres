# contrib/asan_check/Makefile

MODULES = asan_check
PGFILEDESC = "asan_check - asan as memory error detector test"

# EXTENSION = asan_check

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/asan_check
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
asan:
	make
	$(CC) asan_check.o $(CFLAGS) $(LDFLAGS) $(LDFLAGS_EX) $(LIBS) -o a.out