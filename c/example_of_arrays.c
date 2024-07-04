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

int main(void)
{
    /*  Syntax for an array of 7 integers.                                    */
    int myarray[7];

    /*  Integer for indexing over the elements of the array.                  */
    int i;

    /*  Loop through the elements of the array and edit them.                 */
    for (i = 0; i < 7; ++i)
    {
        /*  Set the ith element to 10(i + 1) and print the value.             */
        myarray[i] = 10*(i + 1);
        printf("myarray[%d] = %d\n", i, myarray[i]);
    }

    printf("Have a Great Day!\n");
    return 0;
}
