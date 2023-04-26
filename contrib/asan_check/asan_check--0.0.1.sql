--complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION asan_check" to load this file. \quit

CREATE OR REPLACE FUNCTION asan_check() RETURNS int
AS 'MODULE_PATHNAME', 'asan_check'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION buffer_overflow() RETURNS int
AS 'MODULE_PATHNAME', 'buffer_overflow'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION double_free() RETURNS int
AS 'MODULE_PATHNAME', 'double_free'
LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION use_after_free() RETURNS int
AS 'MODULE_PATHNAME', 'use_after_free'
LANGUAGE C IMMUTABLE STRICT;