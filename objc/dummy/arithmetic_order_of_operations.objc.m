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
    const int a = 2;
    const int b = 3;
    const int c = 5;

    /*  Objective-C (like most languages) respects the usual order of         *
     *  operations. The symbols * and / have precedance over + and -.         */
    const int noParentheses = a * b + c;
    const int withParentheses = a * (b + c);
    const int redundantParentheses = (a * b) + c;

    /*  Print the results. noParentheses and redundantParentheses will have   *
     *  the same value, withParentheses will be different.                    */
    NSLog(@"a = %i", a);
    NSLog(@"b = %i", b);
    NSLog(@"c = %i", c);
    NSLog(@"a * b + c = %i", noParentheses);
    NSLog(@"a * (b + c) = %i", withParentheses);
    NSLog(@"(a * b) + c = %i", redundantParentheses);

    [pool drain];
    return 0;
}
