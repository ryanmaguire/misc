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
;   Author:     Ryan Maguire                                                   ;
;   Date:       2018                                                           ;
;------------------------------------------------------------------------------;

; Tells the compiler that integers should be 32 bits, not 16.
COMPILE_OPT IDL2

; Import NAIF Leap Second counter.
CSPICE_FURNSH, 'naif0012.tls'

; Create Transformation matrix from B2950 to J2000
CSPICE_PXFORM, 'B1950', 'J2000', 0.0, MATRIX

; Saturn's Pole in 1981 had RA=38.409 and DEC=83.324 in the B1950 system.
; Create a unit vector pointing in the direction of Saturn's pole.
CSPICE_RADREC, 1.0, 38.409*CSPICE_RPD(), 83.324*CSPICE_RPD(), NHAT

; Get unit vector in the J2000 coordinates.
NHAT2 = MATRIX##NHAT

; Make nhat2 into a vector.
NHAT2 = reform(NHAT2)

; Convert unit vector to RA and DEC in J2000.
CSPICE_RECRAD, NHAT2, R, RA, DEC

END
