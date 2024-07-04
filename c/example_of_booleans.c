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

/*  The original C standard does not have Booleans. The next standards, C99   *
 *  and higher, do have Booleans. For portability we can define Booleans as   *
 *  follows. This works with any compiler supporting any of the C standards.  */
#define BOOL char
#define FALSE 0
#define TRUE 1

int main()
{
    /*  Declare two Booleans two test some code on.                           */
    BOOL x, y;

    /*  Use the macros above to set the values to false and true.             */
    x = FALSE;
    y = TRUE;

    /*  Print the values to the terminal.                                     */
    printf("False: %d\n", x);
    printf("True: %d\n", y);

    return 0;
}
