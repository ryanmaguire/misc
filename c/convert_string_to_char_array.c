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
 *      Converts a string into a char array, printing it to the screen.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 29, 2025                                              *
 ******************************************************************************/
#include <stdio.h>

#define WRAP_WIDTH 75

static const char *string = "Hello, World!\nIt's me!\n";

static void print_string_as_char_array(const char *str)
{
    size_t line_len = 0;
    printf("{\n    ");

    while (*str)
    {
        if (line_len + 5 > WRAP_WIDTH)
        {
            printf("\n    ");
            line_len = 0;
        }

        switch (*str)
        {
            case '\n':
                printf("'\\n', ");
                line_len += 6;
                break;

            case '\t':
                printf("'\\t', ");
                line_len += 6;
                break;

            case '\r':
                printf("'\\r', ");
                line_len += 6;
                break;

            case '\'':
                printf("'\\'', ");
                line_len += 6;
                break;

            default:
                printf("'%c', ", *str);
                line_len += 5;
        }

        ++str;
    }

    if (line_len + 5 > WRAP_WIDTH)
        printf("\n    ");

    printf("'\\0'\n};\n");
}

int main(void)
{
    print_string_as_char_array(string);
    return 0;
}
