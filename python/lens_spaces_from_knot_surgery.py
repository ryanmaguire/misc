"""
################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is free software: you can redistribute it and/or modify          #
#   it under the terms of the GNU General Public License as published by       #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   This file is distributed in the hope that it will be useful,               #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with this file.  If not, see <https://www.gnu.org/licenses/>.        #
################################################################################
#   Purpose:                                                                   #
#       Code from the trisector workshop, June 2024.                           #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       2024/06/26                                                     #
################################################################################
"""
# pylint: disable = invalid-name
import math

def diff_is_one(m, p, q):
    """
        Determines if |m - pq| = 1.
    """
    if abs(m - p*q) == 1:
        return True

    return False

def squares_are_equivalent(m, p, q):
    """
        Determines if p^2 = q^2 (mod m).
    """
    psq = p*p % m
    qsq = q*q % m

    if psq == qsq:
        return True

    return False

def lens_condition(m, p, q):
    """
        Checks the lens condition for
        an ordered triple (m, p, q).
    """
    if math.gcd(p, q) != 1:
        return False

    if not diff_is_one(m, p, q):
        return False

    if not squares_are_equivalent(m, p, q):
        return False

    return True

def test_ordered_triples(stopping_number):
    """
        Checks all ordered triples (m, p, q)
        up to "stopping_number" for the lens condition.
    """
    for m in range(1, stopping_number):
        for p in range(2, m + 1):
            for q in range(p + 1, m + 1):
                if lens_condition(m, p, q):
                    print(f"m: {m} p: {p} q: {q}")

if __name__ == "__main__":
    test_ordered_triples(1000)
