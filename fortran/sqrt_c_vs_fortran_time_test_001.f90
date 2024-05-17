!------------------------------------------------------------------------------!
!                                   LICENSE                                    !
!------------------------------------------------------------------------------!
!   This file is free software: you can redistribute it and/or modify          !
!   it under the terms of the GNU General Public License as published by       !
!   the Free Software Foundation, either version 3 of the License, or          !
!   (at your option) any later version.                                        !
!                                                                              !
!   This file is distributed in the hope that it will be useful,               !
!   but WITHOUT ANY WARRANTY; without even the implied warranty of             !
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              !
!   GNU General Public License for more details.                               !
!                                                                              !
!   You should have received a copy of the GNU General Public License          !
!   along with this file.  If not, see <https://www.gnu.org/licenses/>.        !
!------------------------------------------------------------------------------!
!   Purpose:                                                                   !
!       Time test C vs Fortran with something simple. Computes sqrt(x) for a   !
!       large set of real numbers at double precision.                         !
!------------------------------------------------------------------------------!
!   Author:     Ryan Maguire                                                   !
!   Date:       2023/10/08                                                     !
!------------------------------------------------------------------------------!
PROGRAM MAIN
    IMPLICIT NONE
    REAL, ALLOCATABLE :: X(:)
    REAL, ALLOCATABLE :: Y(:)
    INTEGER :: ARRAY_SIZE
    REAL :: DX
    INTEGER :: N

    ! Number of elements in the array.
    ARRAY_SIZE = 1E8

    ! Step size between sample points.
    DX = 1.0E-6

    ! Create the arrays for the x and y components.
    ALLOCATE(X(ARRAY_SIZE))
    ALLOCATE(Y(ARRAY_SIZE))

    ! Modern Fortran syntax, creates an array of samples.
    X = [(DX*N, N = 0, ARRAY_SIZE-1)]

    ! Compute the square root of the input array.
    Y = SQRT(X)

    ! Avoid the compiler optimizing everything away. Print the max of Y.
    PRINT *, MAXVAL(Y)

    ! Free all allocated memory.
    DEALLOCATE(X)
    DEALLOCATE(Y)
END PROGRAM MAIN
