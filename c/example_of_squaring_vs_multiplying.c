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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2021                                                          *
 ******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <time.h>

/*  Number of iterations to test the computation on.                          */
static const unsigned int num_iters = 10000000U;

/*  Computes the square function using pow from math.h.                       */
static double square(double x)
{
    clock_t t1, t2;
    unsigned int n;

    /*  A good compiler will see that y is never used and optimize this       *
     *  entire function away. Declaring y to be volatile prevents this.       */
    volatile double y;

    t1 = clock();

    /*  Interestingly, a good compiler with optimizations on will skip the    *
     *  call to the pow function and set the instruction to y = x*x. You can  *
     *  see this in the assembly code with the -S option (GCC or clang).      */
    for (n = 0U; n < num_iters; ++n)
        y = pow(x, 2);

    t2 = clock();
    return (double)(t2 - t1) / (double)(CLOCKS_PER_SEC);
}

/*  Computes the square using y = x*x.                                        */
static double square2(double x)
{
    clock_t t1, t2;
    unsigned int n;

    /*  Same preventative measure as before. Declare y to be volatile.        */
    volatile double y;

    t1 = clock();

    /*  Without optimizations, this method is significantly faster.           */
    for (n = 0U; n < num_iters; ++n)
        y = x*x;

    t2 = clock();
    return (double)(t2 - t1) / (double)(CLOCKS_PER_SEC);
}

int main(void)
{
    printf("%f\n", square(1.414));
    printf("%f\n", square2(1.414));
    return 0;
}
