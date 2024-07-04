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
 *      Shows some of the basic syntax in C.                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2021                                                          *
 ******************************************************************************/
#include <stdio.h>

/*  Computes the nth Fibonacci number via F_n = F_{n-1} + F_{n-2}.            */
static unsigned long int fib(unsigned long int n)
{
    if (n < 2UL)
        return n;

    return fib(n - 1UL) + fib(n - 2UL);
}

int main(void)
{
    const unsigned long n = 6UL;
    const unsigned long Fn = fib(n);
    printf("fib(%lu) = %lu\n", n, Fn);
    return 0;
}
