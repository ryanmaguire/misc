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

;Load the following kernels.
CSPICE_FURNSH, 'naif0012.tls'
CSPICE_FURNSH, 'de421.bsp'
CSPICE_FURNSH, 'pck00010.tpc'
CSPICE_FURNSH, '030201AP_SK_SM546_T45.bsp'

;Define the number of divisions of the time interval and the time interval.
STEP = 10000
UTC = ['Jun 20, 2004', 'Dec 1, 2005']
CSPICE_STR2ET, utc, et
TIMES = FINDGEN(STEP) * (ET[1] - ET[0]) / STEP + ET[0]
CSPICE_SPKPOS, 'Cassini', TIMES, 'J2000', 'NONE', 'SATURN BARYCENTER', POS, LTIME

;Plot the resulting trajectory.
X = POS[0, *]
Y = POS[1, *]
Z = POS[2, *]
IPLOT, X, Y, Z
CSPICE_KCLEAR

TC_GEO = RDCOL(GEOFILE_TC, 1, 99999999, [1:18])
T_OET_SPM_TC      = TC_GEO[0,*]
T_RET_SPM_TC      = TC_GEO[1,*]
T_SET_SPM_TC      = TC_GEO[2,*]
RHO0_KM_TC        = TC_GEO[3,*]
PHI_RL_DEG_TC     = TC_GEO[4,*]
PHI_ORA_DEG_TC    = TC_GEO[5,*]
B_DEG_TC          = TC_GEO[6,*]
D_KM_TC           = TC_GEO[7,*]
RHO0_DOT_KMS_TC   = TC_GEO[8,*]
PHI_RL_DOT_DPS_TC = TC_GEO[9,*]
F_KM_TC           = TC_GEO[10,*]
R_IMP_KM_TC       = TC_GEO[11,*]
R_SC_X_KM_TC      = TC_GEO[12,*]
R_SC_Y_KM_TC      = TC_GEO[13,*]
R_SC_Z_KM_TC      = TC_GEO[14,*]
R_SC_DOT_X_KMS_TC = TC_GEO[15,*]
R_SC_DOT_Y_KMS_TC = TC_GEO[16,*]
R_SC_DOT_Z_KMS_TC = TC_GEO[17,*]

END
