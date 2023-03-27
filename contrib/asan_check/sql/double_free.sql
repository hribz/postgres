CREATE EXTENSION asan_check;
SELECT double_free();
