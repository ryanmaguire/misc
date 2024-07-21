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
FUNCTION MANDELBROT, XCENTER, YCENTER, RADIUS, IMAGE_SIZE, MAX_ITER

   ; Tells the compiler that integers should be 32 bits, not 16.
   COMPILE_OPT IDL2

   ; Set default size to 128 if nothing is set.
   IF N_ELEMENTS(IMAGE_SIZE) EQ 0 THEN BEGIN
      IMAGE_SIZE = 128
   ENDIF

   ; The maximum number of iterations does not need to be large.
   IF N_ELEMENTS(MAX_ITER) EQ 0 THEN BEGIN
      MAX_ITER = 64
   ENDIF

   ; Step size between samples.
   DX = RADIUS * 2.0 / IMAGE_SIZE

   ; Starting points for the x and y axes.
   XSTART = XCENTER - RADIUS
   YSTART = YCENTER - RADIUS

   ; The data for the Mandelbrot set is stored here.
   RESULT = LONARR(IMAGE_SIZE, IMAGE_SIZE)

   ; Pass the variables to the C function.
   C_CALL = CALL_EXTERNAL( $
      "./mandelbrot.so",   $
      "mandelbrot",        $
      LONG(IMAGE_SIZE),    $
      LONG(IMAGE_SIZE),    $
      DOUBLE(XSTART),      $
      DOUBLE(YSTART),      $
      DOUBLE(DX),          $
      DOUBLE(DX),          $
      LONG(MAX_ITER),      $
      RESULT               $
   )

   RETURN, RESULT
END
