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
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

static unsigned int urand(unsigned int max)
{
    const int n_rand = rand();
    return (unsigned int)n_rand % max;
}

int main(void)
{
    double average = 0.0;
    unsigned int counter, old;
    unsigned int l, m, n;
    const unsigned int N = 10000U;
    const unsigned int max = 100000U;
    const unsigned int iters = 100U;
    unsigned int * const x = malloc(sizeof(*x) * N);

    if (!x)
        return -1;

    for (l = 0U; l < iters; ++l)
    {
        printf("%u\n", l);
        counter = 0U;
        old = 0U;

        for (n = 0U; n < N; ++n)
            x[n] = urand(max);

        for (m = 0U; m < max; ++m)
        {
            for (n = 0U; n < N; ++n)
            {
                if (x[n] == m)
                    ++counter;
            }

            if (counter - old == 1)
                counter = old;
            else
                old = counter;
        }

        average += counter;
    }

    average /= iters;

    printf("Average Value: %f\n", average);
    free(x);
    return 0;
}
