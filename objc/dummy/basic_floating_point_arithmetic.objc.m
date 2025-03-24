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
 *      Example of basic floating point arithmetic in Objective-C.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 24, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  The variables we will be playing with.                                */
    const float a = 3.0F;
    const float b = 4.0F;

    /*  The basic arithmetic operators are the same in Objective-C as they    *
     *  in C (or C++, for that matter).                                       */
    const float sum = a + b;
    const float diff = a - b;
    const float prod = a * b;
    const float quot = a / b;

    /*  NSLog behaves similarly to printf. We use format specifiers and then  *
     *  use a comma-separated list of variables we wish to print.             */
    NSLog(@"a = %f", a);
    NSLog(@"b = %f", b);
    NSLog(@"a + b = %f", sum);
    NSLog(@"a - b = %f", diff);
    NSLog(@"a * b = %f", prod);
    NSLog(@"a / b = %f", quot);

    [pool drain];
    return 0;
}
