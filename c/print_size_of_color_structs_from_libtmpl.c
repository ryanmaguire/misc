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
 *      Prints the sizes of the various color structs implemented in libtmpl. *
 *      Used to test how a compiler pads certain structs and bit-fields.      *
 ******************************************************************************/
#include <stdio.h>
#include <libtmpl/include/tmpl_color.h>

int main(void)
{
    puts("Colors:");
    printf("%zu\n", sizeof(tmpl_RGB));
    printf("%zu\n", sizeof(tmpl_RGB24));
    printf("%zu\n", sizeof(tmpl_RGB30));
    printf("%zu\n\n", sizeof(tmpl_RGB48));

    puts("Colors w/Alpha:");
    printf("%zu\n", sizeof(tmpl_RGBA));
    printf("%zu\n", sizeof(tmpl_RGBA24));
    printf("%zu\n", sizeof(tmpl_RGBA30));
    printf("%zu\n\n", sizeof(tmpl_RGBA48));

    puts("Color Pointers:");
    printf("%zu\n", sizeof(tmpl_RGB *));
    printf("%zu\n", sizeof(tmpl_RGB24 *));
    printf("%zu\n", sizeof(tmpl_RGB30 *));
    printf("%zu\n\n", sizeof(tmpl_RGB48 *));

    puts("Color w/Alpha Pointers:");
    printf("%zu\n", sizeof(tmpl_RGBA *));
    printf("%zu\n", sizeof(tmpl_RGBA24 *));
    printf("%zu\n", sizeof(tmpl_RGBA30 *));
    printf("%zu\n\n", sizeof(tmpl_RGBA48 *));
    return 0;
}
