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
 *      Hello world in C using the printf function with error checking.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 3, 2026                                                 *
 ******************************************************************************/

/*  printf function (which stands for "print format") found here.             */
#include <stdio.h>

/*  EXIT_SUCCESS and EXIT_FAILURE macros provided here.                       */
#include <stdlib.h>

/*  We can check if printf succeeded by examining how many characters were    *
 *  written. sizeof returns the size of the underlying char array that is     *
 *  used to store the string literal, and this includes the NULL terminator,  *
 *  '\0'. For a constant string literal, we may compute the string length     *
 *  by subtracting 1 from the output of sizeof.                               */
#define STRING_LENGTH (sizeof("Hello, World!\n") - 1)

/*  Classic "Hello, World!" with an emphasis on safety.                       */
int main(void)
{
    /*  The printf function is outlined in section 7.9.6.3 of the original    *
     *  ANSI C draft (C89), and in section 7.23.6.3 of the more recent C23    *
     *  draft. The description for the printf function is identical in both   *
     *  versions, and states that printf returns the number of characters     *
     *  written to stdout, or a negative integer should a write error occur.  *
     *  The output is an int. Write "Hello, World!" and check for errors.     *
     *  Note, unlike the puts function, printf does not append a new line     *
     *  character to the end. We must add one manually using '\n'.            */
    const int characters_written = printf("%s", "Hello, World!\n");

    /*  For such a simple program, it is highly unlikely that printf failed.  *
     *  To be on the safe side, check. The macros EXIT_FAILURE and            *
     *  EXIT_SUCCESS are described in section 7.10 of the C89 draft, and in   *
     *  7.21.7.9 of the C23 draft. They may be used to indicate if a program  *
     *  terminated successfully or if an error occurred.                      */
    if (characters_written != STRING_LENGTH)
        return EXIT_FAILURE;

    /*  Otherwise, "Hello, World!" is now displayed on the screen.            *
     *  Return EXIT_SUCCESS to conclude.                                      */
    return EXIT_SUCCESS;
}
/*  End of main.                                                              */
