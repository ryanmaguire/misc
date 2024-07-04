/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is free software: you can redistribute it and/or modify         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  This file is distributed in the hope that it will be useful,              *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with this file.  If not, see <https://www.gnu.org/licenses/>.       *
 ******************************************************************************
 *  This file shows the size of all data types in C. I found something very   *
 *  similar to this on stackoverflow and glued bits and pieces together to    *
 *  make this run on clang and GCC with all warnings turned on and in C89,    *
 *  C99, and C18 mode.                                                        *
 ******************************************************************************/

/*  size_t is typedef'd here.                                                 */
#include <stdio.h>

/*  time_t is typedef'd here.                                                 */
#include <time.h>

/*  ptrdiff_t is typedef'd here.                                              */
#include <stddef.h>

/*  C99 and higher defined inttypes.h. Check for this.                        */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#endif

/*  Macro for priting basic types, pointers, and function pointers.           */
#define PRINT_TYPE(x) printf("%6u = sizeof(" #x ")\n", (unsigned int)sizeof(x))

/*  Macro for printing structs.                                               */
#define PRINT_STRUCT(x) do {                                                   \
    typedef x mystruct;                                                        \
    printf("%6u = sizeof(" #x ")\n", (unsigned int)sizeof(mystruct));          \
} while (0)

/*  Function for printing the size of all types in C.                         */
int main(void)
{
#ifdef __STDC_VERSION__
    printf("STDC VERSION:\t%ld\n", __STDC_VERSION__);
#else
    puts("__STDC_VERSION__ Macro not defined. This is probably C89/C90.");
#endif

    /* Basic Types                                                            */
    puts("Basic Types:");
    PRINT_TYPE(char);
    PRINT_TYPE(unsigned char);
    PRINT_TYPE(short);
    PRINT_TYPE(unsigned short);
    PRINT_TYPE(int);
    PRINT_TYPE(unsigned int);
    PRINT_TYPE(long);
    PRINT_TYPE(unsigned long);
    PRINT_TYPE(float);
    PRINT_TYPE(double);
    PRINT_TYPE(long double);
    PRINT_TYPE(size_t);
    PRINT_TYPE(ptrdiff_t);
    PRINT_TYPE(time_t);

    /* Pointers.                                                              */
    puts("Pointers:");
    PRINT_TYPE(void *);
    PRINT_TYPE(char *);
    PRINT_TYPE(short *);
    PRINT_TYPE(int *);
    PRINT_TYPE(long *);
    PRINT_TYPE(float *);
    PRINT_TYPE(double *);

    /* Pointers to functions.                                                 */
    puts("Function Pointers:");
    PRINT_TYPE(int (*)(void));
    PRINT_TYPE(double (*)(void));
    PRINT_TYPE(char *(*)(void));

    /* Structures.                                                            */
    puts("Structs:");
    PRINT_STRUCT(struct {char a;});
    PRINT_STRUCT(struct {short a;});
    PRINT_STRUCT(struct {int a;});
    PRINT_STRUCT(struct {long a;});
    PRINT_STRUCT(struct {float a;});
    PRINT_STRUCT(struct {double a;});
    PRINT_STRUCT(struct {char a; double b;});
    PRINT_STRUCT(struct {short a; double b;});
    PRINT_STRUCT(struct {long a; double b;});
    PRINT_STRUCT(struct {char a; char b; short c;});
    PRINT_STRUCT(struct {char a; char b; long c;});
    PRINT_STRUCT(struct {short a; short b;});
    PRINT_STRUCT(struct {char a[3]; char b[3];});
    PRINT_STRUCT(struct {char a[3]; char b[3]; short c;});
    PRINT_STRUCT(struct {long double a;});
    PRINT_STRUCT(struct {char a; long double b;});

    /* C99 integers.                                                          */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    puts("C99 Types:");
    PRINT_TYPE(long long);
    PRINT_TYPE(unsigned long long);
    PRINT_TYPE(uintmax_t);
    PRINT_TYPE(int_least8_t);
    PRINT_TYPE(int_least16_t);
    PRINT_TYPE(int_least32_t);
    PRINT_TYPE(int_least64_t);
    PRINT_TYPE(int_fast8_t);
    PRINT_TYPE(int_fast16_t);
    PRINT_TYPE(int_fast32_t);
    PRINT_TYPE(int_fast64_t);
    PRINT_TYPE(uintptr_t);
#ifdef INT8_MAX
    PRINT_TYPE(int8_t);
#endif
#ifdef INT16_MAX
    PRINT_TYPE(int16_t);
#endif
#ifdef INT32_MAX
    PRINT_TYPE(int32_t);
#endif
#ifdef INT64_MAX
    PRINT_TYPE(int64_t);
#endif
#ifdef INT128_MAX
    PRINT_TYPE(int128_t);
#endif
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    puts("C99 Structs:");
    PRINT_STRUCT(struct {char a; long long b;});
    PRINT_STRUCT(struct {char a; uintmax_t b;});
#endif
    return 0;
}
/*  End of main.                                                              */

