/*
Copyright (c) 2012, Guillermo "Tordek" Freschi
Copyright (c) 2013, Sampsa "Tuplanolla" Kiiskinen
All rights reserved.

The full license can be found in the LICENSE file.
*/

#ifndef CHEAT_H
	#error "the header file \"cheat.h\" is not included"
#endif

#ifndef CHEATS_H
#define CHEATS_H

#include <math.h>
#include <string.h>

#ifdef CHEAT_MODERN
#include <complex.h>
#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#endif

/*
#ifdef CHEAT_MODERN
#define CHEAT_POINTER_FORMAT "%td"
#define CHEAT_POINTER_TYPE(size) \
	(size)
#else
#define CHEAT_POINTER_FORMAT "%ld"
#define CHEAT_POINTER_TYPE(size) \
	((long int )(size))
#endif

etc

CHEAT_GENERATE_INTEGER(size, size_t, CHEAT_SIZE_FORMAT)
CHEAT_GENERATE_INTEGER(ptrdiff, ptrdiff_t, CHEAT_POINTER_FORMAT)
CHEAT_GENERATE_INTEGER(time, time_t, CHEAT_TIME_FORMAT)
CHEAT_GENERATE_INTEGER(clock, clock_t, CHEAT_CLOCK_FORMAT)
*/

/*
This evaluates to the maximum of two constant expressions.
*/
#define CHEAT_MAXIMUM(x, y) \
	((x) > (y) ? (x) : (y))

/*
This computes an upper bound for the string length of a floating point type.
*/
#ifdef CHEAT_MODERN
#define CHEAT_FLOATING_LENGTH(type) \
	(3 + CHEAT_MAXIMUM(DBL_MANT_DIG - DBL_MIN_EXP, DBL_MAX_EXP))
#else
#define CHEAT_FLOATING_LENGTH(type) \
	(CHEAT_LIMIT) /* This is based on the assumption that
		the preprocessor can convert floating point numbers into strings. */
#endif

#define CHEAT_GENERATE_INTEGER(name, type, specifier) \
	__attribute__ ((__io__, __nonnull__, __unused__)) \
	static void cheat_check_##name(struct cheat_suite* const suite, \
			type const actual, type const expected, \
			char const* const file, size_t const line) { \
		if (actual != expected) { \
			char* expression; \
\
			suite->outcome = CHEAT_FAILED; \
\
			expression = CHEAT_CAST(char*) cheat_allocate_total(3, \
					CHEAT_INTEGER_LENGTH(actual), \
					CHEAT_INTEGER_LENGTH(expected), (size_t )5); \
			if (expression == NULL) \
				cheat_death("failed to allocate memory", errno); \
\
			if (cheat_print_string(expression, \
						specifier " == " specifier, \
						2, actual, expected) < 0) \
				cheat_death("failed to build a string", errno); \
\
			cheat_print_failure(suite, expression, file, line); \
		} \
	}

CHEAT_GENERATE_INTEGER(char, char, "%c")
CHEAT_GENERATE_INTEGER(short_int, short int, "%hd")
CHEAT_GENERATE_INTEGER(short_unsigned_int, short unsigned int, "%hu")
CHEAT_GENERATE_INTEGER(int, int, "%d")
CHEAT_GENERATE_INTEGER(unsigned_int, unsigned int, "%u")
CHEAT_GENERATE_INTEGER(long_int, long int, "%ld")
CHEAT_GENERATE_INTEGER(long_unsigned_int, long unsigned int, "%lu")

#define cheat_assert_char(actual, expected) \
	cheat_check_char(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_short_int(actual, expected) \
	cheat_check_short_int(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_short_unsigned_int(actual, expected) \
	cheat_check_short_unsigned_int(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int(actual, expected) \
	cheat_check_int(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_unsigned_int(actual, expected) \
	cheat_check_unsigned_int(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_long_int(actual, expected) \
	cheat_check_long_int(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_long_unsigned_int(actual, expected) \
	cheat_check_long_unsigned_int(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define CHEAT_GENERATE_FLOATING(name, type, abs, specifier) \
	__attribute__ ((__io__, __nonnull__, __unused__)) \
	static void cheat_check_##name(struct cheat_suite* const suite, \
			type const actual, type const expected, type const tolerance, \
			char const* const file, size_t const line) { \
		if (abs(actual - expected) > tolerance) { \
			char* expression; \
\
			suite->outcome = CHEAT_FAILED; \
\
			expression = CHEAT_CAST(char*) cheat_allocate_total(3, \
					CHEAT_FLOATING_LENGTH(actual), \
					CHEAT_FLOATING_LENGTH(expected), (size_t )5); \
			if (expression == NULL) \
				cheat_death("failed to allocate memory", errno); \
\
			if (cheat_print_string(expression, \
						specifier " ~= " specifier, \
						2, actual, expected) < 0) \
				cheat_death("failed to build a string", errno); \
\
			cheat_print_failure(suite, expression, file, line); \
		} \
	}

CHEAT_GENERATE_FLOATING(double, double, fabs, "%g")

#define cheat_assert_double(actual, expected) \
	cheat_check_double(&cheat_suite, actual, expected, __FILE__, __LINE__)

#ifdef CHEAT_MODERN

CHEAT_GENERATE_INTEGER(long_long_int, long long int, "%lld")
CHEAT_GENERATE_INTEGER(long_long_unsigned_int, long long unsigned int, "%llu")

#define cheat_assert_long_long_int(actual, expected) \
	cheat_check_long_long_int(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_long_long_unsigned_int(actual, expected) \
	cheat_check_long_long_unsigned_int(&cheat_suite, actual, expected, __FILE__, __LINE__)

CHEAT_GENERATE_FLOATING(float, float, fabsf, "%hg")
CHEAT_GENERATE_FLOATING(long_double, long double, fabsl, "%lg")

#define cheat_assert_float(actual, expected) \
	cheat_check_float(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_long_double(actual, expected) \
	cheat_check_long_double(&cheat_suite, actual, expected, __FILE__, __LINE__)

CHEAT_GENERATE_INTEGER(int8, int8_t, "%" PRId8)
CHEAT_GENERATE_INTEGER(uint8, uint8_t, "%" PRIu8)
CHEAT_GENERATE_INTEGER(int16, int16_t, "%" PRId16)
CHEAT_GENERATE_INTEGER(uint16, uint16_t, "%" PRIu16)
CHEAT_GENERATE_INTEGER(int32, int32_t, "%" PRId32)
CHEAT_GENERATE_INTEGER(uint32, uint32_t, "%" PRIu32)
CHEAT_GENERATE_INTEGER(int64, int64_t, "%" PRId64)
CHEAT_GENERATE_INTEGER(uint64, uint64_t, "%" PRIu64)
CHEAT_GENERATE_INTEGER(int_fast8, int_fast8_t, "%" PRIdFAST8)
CHEAT_GENERATE_INTEGER(uint_fast8, uint_fast8_t, "%" PRIuFAST8)
CHEAT_GENERATE_INTEGER(int_fast16, int_fast16_t, "%" PRIdFAST16)
CHEAT_GENERATE_INTEGER(uint_fast16, uint_fast16_t, "%" PRIuFAST16)
CHEAT_GENERATE_INTEGER(int_fast32, int_fast32_t, "%" PRIdFAST32)
CHEAT_GENERATE_INTEGER(uint_fast32, uint_fast32_t, "%" PRIuFAST32)
CHEAT_GENERATE_INTEGER(int_fast64, int_fast64_t, "%" PRIdFAST64)
CHEAT_GENERATE_INTEGER(uint_fast64, uint_fast64_t, "%" PRIuFAST64)
CHEAT_GENERATE_INTEGER(int_least8, int_least8_t, "%" PRIdLEAST8)
CHEAT_GENERATE_INTEGER(uint_least8, uint_least8_t, "%" PRIuLEAST8)
CHEAT_GENERATE_INTEGER(int_least16, int_least16_t, "%" PRIdLEAST16)
CHEAT_GENERATE_INTEGER(uint_least16, uint_least16_t, "%" PRIuLEAST16)
CHEAT_GENERATE_INTEGER(int_least32, int_least32_t, "%" PRIdLEAST32)
CHEAT_GENERATE_INTEGER(uint_least32, uint_least32_t, "%" PRIuLEAST32)
CHEAT_GENERATE_INTEGER(int_least64, int_least64_t, "%" PRIdLEAST64)
CHEAT_GENERATE_INTEGER(uint_least64, uint_least64_t, "%" PRIuLEAST64)
CHEAT_GENERATE_INTEGER(intmax, intmax_t, "%" PRIdMAX)
CHEAT_GENERATE_INTEGER(uintmax, uintmax_t, "%" PRIuMAX)
CHEAT_GENERATE_INTEGER(intptr, intptr_t, "%" PRIdPTR)
CHEAT_GENERATE_INTEGER(uintptr, uintptr_t, "%" PRIuPTR)

#define cheat_assert_int8(actual, expected) \
	cheat_check_int8(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint8(actual, expected) \
	cheat_check_uint8(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int16(actual, expected) \
	cheat_check_int16(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint16(actual, expected) \
	cheat_check_uint16(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int32(actual, expected) \
	cheat_check_int32(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint32(actual, expected) \
	cheat_check_uint32(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int64(actual, expected) \
	cheat_check_int64(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint64(actual, expected) \
	cheat_check_uint64(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int_fast8(actual, expected) \
	cheat_check_int_fast8(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint_fast8(actual, expected) \
	cheat_check_uint_fast8(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int_fast16(actual, expected) \
	cheat_check_int_fast16(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint_fast16(actual, expected) \
	cheat_check_uint_fast16(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int_fast32(actual, expected) \
	cheat_check_int_fast32(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint_fast32(actual, expected) \
	cheat_check_uint_fast32(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int_fast64(actual, expected) \
	cheat_check_int_fast64(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint_fast64(actual, expected) \
	cheat_check_uint_fast64(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int_least8(actual, expected) \
	cheat_check_int_least8(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint_least8(actual, expected) \
	cheat_check_uint_least8(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int_least16(actual, expected) \
	cheat_check_int_least16(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint_least16(actual, expected) \
	cheat_check_uint_least16(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int_least32(actual, expected) \
	cheat_check_int_least32(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint_least32(actual, expected) \
	cheat_check_uint_least32(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_int_least64(actual, expected) \
	cheat_check_int_least64(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uint_least64(actual, expected) \
	cheat_check_uint_least64(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_intmax(actual, expected) \
	cheat_check_intmax(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uintmax(actual, expected) \
	cheat_check_uintmax(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_intptr(actual, expected) \
	cheat_check_intptr(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_uintptr(actual, expected) \
	cheat_check_uintptr(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define CHEAT_GENERATE_COMPLEX(name, type, abs, real, imag, specifier) \
	__attribute__ ((__io__, __nonnull__, __unused__)) \
	static void cheat_check_##name(struct cheat_suite* const suite, \
			type complex const actual, type complex const expected, \
			type const tolerance, char const* const file, size_t const line) { \
		if (abs(actual - expected) > tolerance) { \
			char* expression; \
\
			suite->outcome = CHEAT_FAILED; \
\
			expression = CHEAT_CAST(char*) cheat_allocate_total(3, \
					CHEAT_FLOATING_LENGTH(real(actual)), \
					CHEAT_FLOATING_LENGTH(imag(actual)), \
					CHEAT_FLOATING_LENGTH(real(expected)), \
					CHEAT_FLOATING_LENGTH(imag(expected)), (size_t )9); \
			if (expression == NULL) \
				cheat_death("failed to allocate memory", errno); \
\
			if (cheat_print_string(expression, \
						specifier "+" specifier "i" \
						" ~= " specifier "+" specifier "i", \
						4, real(actual), imag(actual), \
						real(expected), imag(expected)) < 0) \
				cheat_death("failed to build a string", errno); \
\
			cheat_print_failure(suite, expression, file, line); \
		} \
	}

CHEAT_GENERATE_COMPLEX(float_complex, float, cabsf, crealf, cimagf, "%g")
CHEAT_GENERATE_COMPLEX(double_complex, double, cabs, creal, cimag, "%g")
CHEAT_GENERATE_COMPLEX(long_double_complex, long double,
		cabsl, creall, cimagl, "%lg")

#define cheat_assert_float_complex(actual, expected) \
	cheat_check_float_complex(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_double_complex(actual, expected) \
	cheat_check_double_complex(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_long_double_complex(actual, expected) \
	cheat_check_long_double_complex(&cheat_suite, actual, expected, __FILE__, __LINE__)

CHEAT_GENERATE_INTEGER(signed_char, signed char, "%hhd")
CHEAT_GENERATE_INTEGER(unsigned_char, unsigned char, "%hhu")

#else

CHEAT_GENERATE_INTEGER(signed_char, signed char, "%hd")
CHEAT_GENERATE_INTEGER(unsigned_char, unsigned char, "%hu")

#endif

#define cheat_assert_signed_char(actual, expected) \
	cheat_check_signed_char(&cheat_suite, actual, expected, __FILE__, __LINE__)

#define cheat_assert_unsigned_char(actual, expected) \
	cheat_check_unsigned_char(&cheat_suite, actual, expected, __FILE__, __LINE__)

__attribute__ ((__io__, __nonnull__, __unused__))
static void cheat_check_string(struct cheat_suite* const suite,
		char const* const actual, char const* const expected,
		char const* const file, size_t const line) {
	if (actual != expected) {
		char* expression;

		suite->outcome = CHEAT_FAILED;

		expression = CHEAT_CAST(char*) cheat_allocate_total(3,
				strlen(actual), strlen(expected), (size_t )9);
		if (expression == NULL)
			cheat_death("failed to allocate memory", errno);

		if (cheat_print_string(expression, "\"%s\" == \"%s\"",
					2, actual, expected) < 0)
			cheat_death("failed to build a string", errno);

		cheat_print_failure(suite, expression, file, line);
	}
}

#define cheat_assert_string(actual, expected) \
	cheat_check_string(&cheat_suite, actual, expected, __FILE__, __LINE__)

#endif