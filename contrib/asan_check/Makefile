# contrib/asan_check/Makefile

MODULES = asan_check
PGFILEDESC = "asan_check - asan as memory error detector test"

EXTENSION = asan_check
DATA = asan_check--0.0.1.sql
REGRESS = asan_check buffer_overflow double_free

# PG_CFLAGS = "-shared-libasan"
# PG_LIBS = "/home/xiaoyu/gradDesign/llvm-project-postgres/build/lib/clang/13.0.1/lib/linux"

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
	make check REGRESS=asan_check EXTRA_REGRESS_OPTS="--outputdir=asan_check_log"
	make check REGRESS=buffer_overflow EXTRA_REGRESS_OPTS="--outputdir=buffer_overflow_log"
	make check REGRESS=double_free EXTRA_REGRESS_OPTS="--outputdir=double_free_log"
	make check REGRESS=use_after_free EXTRA_REGRESS_OPTS="--outputdir=use_after_free_log"

asan_clean:
	make clean
	rm -rf ./*_log