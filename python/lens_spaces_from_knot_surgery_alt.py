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
#   Date:       2024/06/27                                                     #
################################################################################
"""
# pylint: disable = invalid-name
import math

def diff_is_one(m, a, b):
    """
        Determines if |m - pq| = 1.
    """
    if abs(m - a*b) == 1:
        return True

    return False

def quartic_is_good(m, b):
    """
        Determines if b^2 and b^4 are
        equal to 1 or -1, mod m.
    """
    bsq = b*b % m
    bqt = bsq*bsq % m

    m_list = [1, m - 1]

    if bsq in m_list or bqt in m_list:
        return True

    return False

def rational_inequality(n, a, b):
    """
        Inequality the ordered triples must satisfy.
    """
    # Older inequality:
    #   if 67*n > 30*(a*a - 1)*(b*b - 1):
    # New inequality.
    if 4*n > 43*(a*b - a - b):
        return False

    return True

def even_rule(n, a, b):
    """
        Determines if a == 2, or n == 2*b + 1.
        Both of these conditions are to be excluded.
    """
    if a == 2 and n == 2*b + 1:
        return False

    return True

def lens_condition(m, a, b):
    """
        Checks the lens condition for
        an ordered triple (m, p, q).
    """
    if math.gcd(a, b) != 1:
        return False

    if not rational_inequality(m, a, b):
        return False

    if not diff_is_one(m, a, b):
        return False

    if not quartic_is_good(m, b):
        return False

    if not even_rule(m, a, b):
        return False

    return True

def test_ordered_triples(stopping_number):
    """
        Checks all ordered triples (m, p, q)
        up to "stopping_number" for the lens condition.
    """
    for m in range(1, stopping_number):
        for a in range(2, (m // 2) + 3):
            for b in range(a + 1, (m // a) + 3):
                if lens_condition(m, a, b):
                    print(f"m: {m} a: {a} b: {b}")

if __name__ == "__main__":
    test_ordered_triples(10000)
