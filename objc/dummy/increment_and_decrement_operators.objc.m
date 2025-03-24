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
 *      Example of increment / decrement operators in Objective-C.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 24, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  The variable we will be playing with.                                 */
    int a = 2;

    /*  Tell the user what we're working with. Print the values.              */
    NSLog(@"a = %i", a);

    /*  Increment before the statement, NSLog sees a = 3.                     */
    NSLog(@"++a = %i", ++a);

    /*  Increment after the statement, NSLog sees a = 3 still.                */
    NSLog(@"a++ = %i", a++);

    /*  a is incremented after the previous statement. a is now 4.            */
    NSLog(@"a = %i", a);

    /*  We can do the same thing with the decrement operator.                 */
    NSLog(@"--a = %i", --a);
    NSLog(@"a-- = %i", a--);
    NSLog(@"a = %i", a);

    [pool drain];
    return 0;
}
