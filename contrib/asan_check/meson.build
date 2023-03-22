# Copyright (c) 2022-2023, PostgreSQL Global Development Group

auth_delay_sources = files(
  'asan_check.c',
)

if host_system == 'windows'
  asan_check_sources += rc_lib_gen.process(win32ver_rc, extra_args: [
    '--NAME', 'asan_check',
    '--FILEDESC', 'asan_check - asan as memory error detector test',])
endif

autoinc = shared_module('asan_check',
  asan_check_sources,
  kwargs: contrib_mod_args,
)
contrib_targets += autoinc
