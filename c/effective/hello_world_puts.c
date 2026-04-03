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
 *      Hello world in C using the puts function with error checking.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 3, 2026                                                 *
 ******************************************************************************/

/*  puts function (which stands for "put string") found here.                 */
#include <stdio.h>

/*  EXIT_SUCCESS and EXIT_FAILURE macros provided here.                       */
#include <stdlib.h>

/*  Classic "Hello, World!" with an emphasis on safety.                       */
int main(void)
{
    /*  The puts function is outlined in section 7.9.7.10 of the original     *
     *  ANSI C draft (C89), and in section 7.23.7.9 of the more recent C23    *
     *  draft. The description for the puts function is identical in both     *
     *  versions, and states that puts return EOF should a write error occur, *
     *  otherwise puts returns a non-negative integer. Write Hello, World,    *
     *  but check to see if puts failed.                                      */
    const int status = puts("Hello, World!");

    /*  For such a simple program, it is highly unlikely that puts failed.    *
     *  To be on the safe side, check. The macros EXIT_FAILURE and            *
     *  EXIT_SUCCESS are described in section 7.10 of the C89 draft, and in   *
     *  7.21.7.9 of the C23 draft. They may be used to indicate if a program  *
     *  terminated successfully or if an error occurred.                      */
    if (status == EOF)
        return EXIT_FAILURE;

    /*  Otherwise, "Hello, World!" is now displayed on the screen.            *
     *  Return EXIT_SUCCESS to conclude.                                      */
    return EXIT_SUCCESS;
}
/*  End of main.                                                              */
