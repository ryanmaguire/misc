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
 *      Example of using structs in Objective-C.                              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 26, 2025                                                *
 ******************************************************************************/
#import <Foundation/Foundation.h>

struct budget {
    const char * foreignCurrencyName;
    double dollarToForeignRate;
    double dollars;
    double foreignCurrencyValue;
};

struct budget initBudget(const double initialBudget)
{
    struct budget wallet;
    wallet.foreignCurrencyName = "euro";
    wallet.dollarToForeignRate = 0.93;
    wallet.dollars = initialBudget;
    wallet.foreignCurrencyValue = wallet.dollars * wallet.dollarToForeignRate;
    return wallet;
}

int main(void)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    struct budget wallet = initBudget(100.0);

    NSLog(
        @"You are starting with %.2f %ss.",
        wallet.foreignCurrencyValue,
        wallet.foreignCurrencyName
    );

    [pool drain];
    return 0;
}
