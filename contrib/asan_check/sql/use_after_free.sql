CREATE EXTENSION asan_check;
SELECT use_after_free();
