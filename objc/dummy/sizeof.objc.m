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
 *      Shows how to use the sizeof operator in Objective-C.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 24, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

/*  Simple class with some data and methods.                                  */
@interface MyObject: NSObject
    {
        double *data;
        size_t length;
    }
    + (double) myFunction: (double)x;
    + (double) myOtherFunction: (double)x;
@end

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    /*  Print the size of a few data types, including an Objective-C class.   */
    NSLog(@"sizeof(char)           = %zu", sizeof(char));
    NSLog(@"sizeof(unsigned char)  = %zu", sizeof(unsigned char));
    NSLog(@"sizeof(short)          = %zu", sizeof(short));
    NSLog(@"sizeof(unsigned short) = %zu", sizeof(unsigned short));
    NSLog(@"sizeof(int)            = %zu", sizeof(int));
    NSLog(@"sizeof(unsigned int)   = %zu", sizeof(unsigned int));
    NSLog(@"sizeof(long)           = %zu", sizeof(long));
    NSLog(@"sizeof(unsigned long)  = %zu", sizeof(unsigned long));
    NSLog(@"sizeof(float)          = %zu", sizeof(float));
    NSLog(@"sizeof(double)         = %zu", sizeof(double));
    NSLog(@"sizeof(long double)    = %zu", sizeof(long double));
    NSLog(@"sizeof(MyObject)       = %zu", sizeof(MyObject));

    [pool drain];
    return 0;
}
