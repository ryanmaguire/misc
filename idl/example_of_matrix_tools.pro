;------------------------------------------------------------------------------;
;                                   LICENSE                                    ;
;------------------------------------------------------------------------------;
;   This file is free software: you can redistribute it and/or modify          ;
;   it under the terms of the GNU General Public License as published by       ;
;   the Free Software Foundation, either version 3 of the License, or          ;
;   (at your option) any later version.                                        ;
;                                                                              ;
;   This file is distributed in the hope that it will be useful,               ;
;   but WITHOUT ANY WARRANTY; without even the implied warranty of             ;
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              ;
;   GNU General Public License for more details.                               ;
;                                                                              ;
;   You should have received a copy of the GNU General Public License          ;
;   along with this file.  If not, see <https://www.gnu.org/licenses/>.        ;
;------------------------------------------------------------------------------;
;   Purpose:                                                                   ;
;       Performs a matrix calculation in two equivalent ways and compares      ;
;       performance. It is much faster to use the built-in operations.         ;
;------------------------------------------------------------------------------;
;   Author:     Ryan Maguire                                                   ;
;   Date:       2018                                                           ;
;------------------------------------------------------------------------------;

; Tells the compiler that integers should be 32 bits, not 16.
COMPILE_OPT IDL2

A = DBLARR(25600, 25600)
B = DBLARR(25600)

T1 = SYSTIME(/SECONDS)
FOR i = 0, 25600 - 1 DO B[i] = TOTAL(A[i, *])
T2 = SYSTIME(/SECONDS)

T3 = SYSTIME(/SECONDS)
B = TOTAL(A, 2)
T4 = SYSTIME(/SECONDS)

PRINT, T2 - T1, T4 - T3
END
