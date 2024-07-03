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

; Create array of 1000 ephemeris times with step size
; of 10 hours, starting July 1, 2005.
CSPICE_STR2ET, 'July 1, 2005', START
ET = FINDGEN(1000)*36000.0 + START

; Retrieve the state vectors and corresponding light times for Mars to Earth
; at each ET in the J2000 frame using the LT+S aberration correction.
CSPICE_SPKEZR, 'Earth', ET, 'J2000', 'LT+S', 'MARS', STATE, LTIME

; Access the ith state 6-vector corresponding to the ith et.
STATE_I = STATE[*, i]

; Convert the et vector from the previous example to UTC calendar strings.
FORMAT = 'C'
PREC = 3
CSPICE_ET2UTC, ET, FORMAT, PREC, UTCSTR

; Access the ith string of utcstr.
UTCSTR_I = UTCSTR[i]

; Convert position components of the N state vectors to latitudinal coordinates.
; This returns three double precision variables: radius, latitude, longitude.
CPSICE_RECLAT, STATE[0:2, *], RADIUS, LATITUDE, LONGITUDE
END
