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
 *      Example of basic integer arithmetic in Objective-C (works with GCC).  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 23, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  The variables we will be playing with.                                */
    const int a = 1;
    const int b = 2;

    /*  The basic arithmetic operators are the same in Objective-C as they    *
     *  in C (or C++, for that matter).                                       */
    const int sum = a + b;
    const int diff = a - b;
    const int prod = a * b;

    /*  Integer division rounds the result, so 1 / 2 will produce 0.          */
    const int quot = a / b;
    const int rem = a % b;

    /*  NSLog behaves similarly to printf. We use format specifiers and then  *
     *  use a comma-separated list of variables we wish to print.             */
    NSLog(@"a = %i", a);
    NSLog(@"b = %i", b);
    NSLog(@"a + b = %i", sum);
    NSLog(@"a - b = %i", diff);
    NSLog(@"a * b = %i", prod);
    NSLog(@"a / b = %i", quot);

    /*  Modulus uses the percent symbol which is reserved. To print it we use *
     *  two percent symbols in a row.                                         */
    NSLog(@"a %% b = %i", rem);

    [pool drain];
    return 0;
}
