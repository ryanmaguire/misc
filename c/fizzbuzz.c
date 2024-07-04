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
 *      The famous FizzBuzz test.                                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       2021                                                          *
 ******************************************************************************/
#include <stdio.h>

int main(void)
{
    int n = 100;
    int i;
    int imod3, imod5;

    for (i = 1; i <= n; ++i)
    {
        imod3 = (i % 3);
        imod5 = (i % 5);

        if (imod3 == 0)
            printf("Fizz");

        if (imod5 == 0)
            printf("Buzz");

        if ((imod3 != 0) && (imod5 != 0))
            printf("%d", i);

        printf("\n");
    }

    return 0;
}
