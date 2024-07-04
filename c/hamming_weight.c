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
 *  Purpose:                                                                  *
 *      Provides several algorithms for the Hamming weight of a number.       *
 ******************************************************************************/
#include <stdio.h>

/*  Four algorithms provided, two of which are compiler-specific.             */
#define KR 0
#define NAIVE 1
#define GCC 2
#define MSVC 3

/*  The choice of algorithm.                                                  */
#define ALG 2

/*  The algorithm found in K&R "The C Programming Language."                  */
#if ALG == KR

static unsigned int hamming_weight(unsigned int val)
{
    unsigned int count = 0U;
    for (; val; ++count)
        val &= val - 1;

    return count;
}

/*  The naive "by-hand" algorithm, counting the individual bits.              */
#elif ALG == NAIVE
static
static unsigned int hamming_weight(unsigned int val)
{
    unsigned int result = 0U;

    while(val != 0U)
    {
        result += val & 1U;
        val = val >> 1U;
    }

    return result;
}

/*  GCC built-in function, popcount, computes the Hamming weight.             */
#elif ALG == GCC

static unsigned int hamming_weight(unsigned int val)
{
    return __builtin_popcount(val);
}

/*  MSVC equivalent of the GCC __builtin_popcount function.                   */
#elif ALG == MSVC

#include <intrin.h>

static unsigned int hamming_weight(unsigned int val)
{
    return __popcnt(val);
}

/*  The user chose an illegal value for the algorithm.                        */
#else
#error "Illegal ALG value."
#endif

/*  Simple test. The Hamming weight of 7 is 3. 7 = 111_2, three 1's.          */
int main(void)
{
    printf("%u\n", hamming_weight(7U));
    return 0;
}
