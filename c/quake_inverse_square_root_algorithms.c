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
 *      Dabbles with the legendary "Quake Inverse Square Root."               *
 ******************************************************************************/

/*  sqrtf function provided here.                                             */
#include <math.h>

/*  Input / Output routines. printf is declared here.                         */
#include <stdio.h>

/*  malloc and free are given here.                                           */
#include <stdlib.h>

/*  Routines for timing how long a computation takes.                         */
#include <time.h>

#if 1

/*  Semi-Legal equivalent of the Quake code using a Union.                    */
static float inverse_square_root(float number)
{
    const float x2 = number * 0.5F;
    const float threehalfs = 1.5F;

    /*  Type-punning a 32-bit float with a 32-bit int using a union. This     *
     *  assumes unsigned int is 32 bits, and that float is given by the       *
     *  IEEE-754 specification for 32-bit single precision floating points.   *
     *  Both of these assumptions are almost always true for modern computers.*
     *  And by "modern" I mean anything build after the 1990s.                */
    union {
        float f;
        unsigned int n;
    } pun;

    /*  Set the float part of the union to the input number.                  */
    pun.f = number;

    /*  Type-punning. Treat the bits of the float as an integer.              */
    pun.n = 0x5F3759DF - (pun.n >> 1);

    /*  Treat the new bits as a float again and perform Newton's method.      */
    pun.f *= threehalfs - (x2 * pun.f * pun.f);

    return pun.f;
}

#else

/*  The original Quake code and original comments.                            */
static float inverse_square_root(float number)
{
    int i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = *(int *) &y;                     // evil floating point bit level hacking
    i  = 0x5f3759df - (i >> 1);           // what the fuck?
    y  = *(float *) &i;
    y  = y * (threehalfs - (x2 * y * y)); // 1st iteration
//  y  = y * (threehalfs - (x2 * y * y)); // 2nd iteration, this can be removed

    return y;
}

#endif

/*  Time and accuracy test of the Quake code against math.h (libm).           */
int main(void)
{
    float x;
    size_t n;
    const size_t N = (size_t)(1E7);
    const float dx = 100.0F / (float)N;

    float * const y0 = malloc(sizeof(*y0) * N);
    float * const y1 = malloc(sizeof(*y1) * N);
    float max, temp;
    clock_t t1, t2;

    x = dx;
    t1 = clock();

    for (n=0; n<N; ++n)
    {
        y0[n] = inverse_square_root(x);
        x += dx;
    }

    t2 = clock();
    printf("Quake Time:         %E\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    x = dx;
    t1 = clock();

    for (n=0; n<N; ++n)
    {
        y1[n] = 1.0F / sqrtf(x);
        x += dx;
    }

    t2 = clock();
    printf("math.h Time:        %E\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    max = 0.0F;

    for (n=0; n<N; ++n)
    {
        temp = fabsf(y0[n] - y1[n]) / y1[n];

        if (max < temp)
            max = temp;
    }

    printf("Max Relative Error: %E\n", (double)max);
    free(y0);
    free(y1);
    return 0;
}
