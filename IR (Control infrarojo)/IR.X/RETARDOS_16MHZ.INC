;************************* Librería "RETARDOS_16MHZ.INC"******************************
;
;      Librería de retardos para oscilador de 16 MHz.
;
;      Web: http://electronica-pic.blogspot.com
;
;*************************************************************************************

; Delay = 0.0005 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.0005 seconds = 2000 cycles
; Error = 0 %

	cblock
	r1
	r2
	endc
RETARDO_500MICROS_16:  ;1993 cycles
	movlw	0x8E
	movwf	r1
	movlw	0x02
	movwf	r2
RETARDO_500MICROS_16_0:
	decfsz	r1, f
	goto	$+2
	decfsz	r2, f
	goto	RETARDO_500MICROS_16_0 ;3 cycles
	goto	$+1
	nop		;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.0002 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.0002 seconds = 800 cycles
; Error = 0 %

	cblock
	r3
	r4
	endc

Retardo_200micros
			;793 cycles
	movlw	0x9E
	movwf	r3
	movlw	0x01
	movwf	r4
Retardo_200micros_0
	decfsz	r3, f
	goto	$+2
	decfsz	r4, f
	goto	Retardo_200micros_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.0001 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.0001 seconds = 400 cycles
; Error = 0 %

	cblock
	r5
	endc

RETARDO_100MICROS_16:	;394 cycles
	movlw	0x83
	movwf	r5
RETARDO_100MICROS_16_0:
	decfsz	r5, f
	goto	RETARDO_100MICROS_16_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 5e-05 seconds
; Clock frequency = 16 MHz

; Actual delay = 5e-05 seconds = 200 cycles
; Error = 0 %

	cblock
	r6
	endc

RETARDO_50MICROS_16:   ;196 cycles
	movlw	0x41
	movwf	r6
RETARDO_50MICROS_16_0:
	decfsz	r6, f
	goto	RETARDO_50MICROS_16_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 2e-05 seconds
; Clock frequency = 16 MHz

; Actual delay = 2e-05 seconds = 80 cycles
; Error = 0 %

	cblock
	r7
	endc

RETARDO_20MICROS_16:
			;76 cycles
	movlw	0x19
	movwf	r7
RETARDO_20MICROS_16_0:
	decfsz	r7, f
	goto	RETARDO_20MICROS_16_0

			;4 cycles (including call)
	return
	
	
;----------------------------------------------------------------------------------------

; Delay = 2e-05 seconds
; Clock frequency = 16 MHz

; Actual delay = 2e-05 seconds = 80 cycles
; Error = 0 %

	cblock
	r53
	endc

RETARDO_13MICROS_16:
			;49 cycles
	movlw	0xE
	movwf	r53
RETARDO_13MICROS_16_0:
	decfsz	r53, f
	goto	RETARDO_13MICROS_16_0

			;4 cycles (including call)
	return
	
;----------------------------------------------------------------------------------------
	
	; Delay = 2e-05 seconds
; Clock frequency = 16 MHz

; Actual delay = 2e-05 seconds = 80 cycles
; Error = 0 %

;	cblock
;	r54
;	endc
;
;RETARDO_10MICROS_16:
;			;49 cycles
;	movlw	0xC
;	movwf	r54
;RETARDO_10MICROS_16_0:
;	    decfsz	r54, f
;	goto	RETARDO_10MICROS_16_0
;
;			;4 cycles (including call)
;	return
	
;----------------------------------------------------------------------------------------
	
; Delay = 2e-05 seconds
; Clock frequency = 16 MHz

; Actual delay = 2e-05 seconds = 80 cycles
; Error = 0 %

	cblock
	R55
	R56
	endc

RETARDO_1686MICROS_16:	;49 cycles
	MOVLW D'10'
	MOVWF R55
BUCLE_1:
	MOVLW D'255'
	MOVWF R56
BUCLE_2:
	DECFSZ R56,1
	GOTO BUCLE_2
	DECFSZ R55,1
	GOTO BUCLE_1
	RETURN

;----------------------------------------------------------------------------------------

; Delay = 0.2 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.2 seconds = 800000 cycles
; Error = 0 %

	cblock
	r8
	r9
	r10
	endc

Retardo_200ms
			;799993 cycles
	movlw	0x6C
	movwf	r8
	movlw	0xBF
	movwf	r9
	movlw	0x02
	movwf	r10
Retardo_200ms_0
	decfsz	r8, f
	goto	$+2
	decfsz	r9, f
	goto	$+2
	decfsz	r10, f
	goto	Retardo_200ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.1 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.1 seconds = 400000 cycles
; Error = 0 %

	cblock
	r11
	r12
	r13
	endc

Retardo_100ms
			;399992 cycles
	movlw	0x35
	movwf	r11
	movlw	0xE0
	movwf	r12
	movlw	0x01
	movwf	r13
Retardo_100ms_0
	decfsz	r11, f
	goto	$+2
	decfsz	r12, f
	goto	$+2
	decfsz	r13, f
	goto	Retardo_100ms_0

			;4 cycles
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.05 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.05 seconds = 200000 cycles
; Error = 0 %

	cblock
	r14
	r15
	endc

Retardo_50ms
			;199993 cycles
	movlw	0x3E
	movwf	r14
	movlw	0x9D
	movwf	r15
Retardo_50ms_0
	decfsz	r14, f
	goto	$+2
	decfsz	r15, f
	goto	Retardo_50ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.02 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.02 seconds = 80000 cycles
; Error = 0 %

	cblock
	r16
	r17
	endc

Retardo_20ms
			;79993 cycles
	movlw	0x7E
	movwf	r16
	movlw	0x3F
	movwf	r17
Retardo_20ms_0
	decfsz	r16, f
	goto	$+2
	decfsz	r17, f
	goto	Retardo_20ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.01 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.01 seconds = 40000 cycles
; Error = 0 %

	cblock
	r18
	r19
	endc

Retardo_10ms
			;39993 cycles
	movlw	0x3E
	movwf	r18
	movlw	0x20
	movwf	r19
Retardo_10ms_0
	decfsz	r18, f
	goto	$+2
	decfsz	r19, f
	goto	Retardo_10ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.005 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.005 seconds = 20000 cycles
; Error = 0 %

	cblock
	r20
	r21
	endc

RETARDO_5MS_16:
			;19993 cycles
	movlw	0x9E
	movwf	r20
	movlw	0x10
	movwf	r21
RETARDO_5MS_16_0:
	decfsz	r20, f
	goto	$+2
	decfsz	r21, f
	goto	RETARDO_5MS_16_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.002 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.002 seconds = 8000 cycles
; Error = 0 %

	cblock
	r22
	r23
	endc

Retardo_2ms
			;7993 cycles
	movlw	0x3E
	movwf	r22
	movlw	0x07
	movwf	r23
Retardo_2ms_0
	decfsz	r22, f
	goto	$+2
	decfsz	r23, f
	goto	Retardo_2ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.001 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.001 seconds = 4000 cycles
; Error = 0 %

	cblock
	r24
	r25
	endc

Retardo_1ms
			;3993 cycles
	movlw	0x1E
	movwf	r24
	movlw	0x04
	movwf	r25
Retardo_1ms_0
	decfsz	r24, f
	goto	$+2
	decfsz	r25, f
	goto	Retardo_1ms_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 20 seconds
; Clock frequency = 16 MHz

; Actual delay = 20 seconds = 80000000 cycles
; Error = 0 %

	cblock
	r26
	r27
	r28
	endc

Retardo_20s
			;79999995 cycles
	movlw	0xDA
	movwf	r26
	movlw	0x63
	movwf	r27
	movlw	0xAF
	movwf	r28
Retardo_20s_0
	decfsz	r26, f
	goto	$+2
	decfsz	r27, f
	goto	$+2
	decfsz	r28, f
	goto	Retardo_20s_0

			;1 cycle
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 10 seconds
; Clock frequency = 16 MHz

; Actual delay = 10 seconds = 40000000 cycles
; Error = 0 %

	cblock
	r29
	r30
	r31
	endc

Retardo_10s
			;39999993 cycles
	movlw	0x6C
	movwf	r29
	movlw	0x32
	movwf	r30
	movlw	0x58
	movwf	r31
Retardo_10s_0
	decfsz	r29, f
	goto	$+2
	decfsz	r30, f
	goto	$+2
	decfsz	r31, f
	goto	Retardo_10s_0

			;3 cycles
	goto	$+1
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 5 seconds
; Clock frequency = 16 MHz

; Actual delay = 5 seconds = 20000000 cycles
; Error = 0 %

	cblock
	r32
	r33
	r34
	endc

Retardo_5s
			;19999992 cycles
	movlw	0xB5
	movwf	r32
	movlw	0x99
	movwf	r33
	movlw	0x2C
	movwf	r34
Retardo_5s_0
	decfsz	r32, f
	goto	$+2
	decfsz	r33, f
	goto	$+2
	decfsz	r34, f
	goto	Retardo_5s_0

			;4 cycles
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 2 seconds
; Clock frequency = 16 MHz

; Actual delay = 2 seconds = 8000000 cycles
; Error = 0 %

	cblock
	r35
	r36
	r37
	endc

RETARDO_2S_16:	    ;7999990 cycles
	movlw	0x47
	movwf	r35
	movlw	0x71
	movwf	r36
	movlw	0x12
	movwf	r37
RETARDO_2S_16_0:
	decfsz	r35, f
	goto	$+2
	decfsz	r36, f
	goto	$+2
	decfsz	r37, f
	goto	RETARDO_2S_16_0

			;6 cycles
	goto	$+1
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 1 seconds
; Clock frequency = 16 MHz

; Actual delay = 1 seconds = 4000000 cycles
; Error = 0 %

	cblock
	r38
	r39
	r40
	endc

Retardo_1s
			;3999994 cycles
	movlw	0x23
	movwf	r38
	movlw	0xB9
	movwf	r39
	movlw	0x09
	movwf	r40
Retardo_1s_0
	decfsz	r38, f
	goto	$+2
	decfsz	r39, f
	goto	$+2
	decfsz	r40, f
	goto	Retardo_1s_0

			;2 cycles
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 0.5 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.5 seconds = 2000000 cycles
; Error = 0 %

	cblock
	r41
	r42
	r43
	endc

RETARDO_500MS_16:	;1999996 cycles
	movlw	0x11
	movwf	r41
	movlw	0x5D
	movwf	r42
	movlw	0x05
	movwf	r43
RETARDO_500MS_16_0:
	decfsz	r41, f
	goto	$+2
	decfsz	r42, f
	goto	$+2
	decfsz	r43, f
	goto	RETARDO_500MS_16_0

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 30 seconds
; Clock frequency = 16 MHz

; Actual delay = 30 seconds = 120000000 cycles
; Error = 0 %

	cblock
	r44
	r45
	r46
	r47
	endc

Retardo_30s
			;119999995 cycles
	movlw	0x54
	movwf	r44
	movlw	0x74
	movwf	r45
	movlw	0xCC
	movwf	r46
	movlw	0x01
	movwf	r47
Retardo_30s_0
	decfsz	r44, f
	goto	$+2
	decfsz	r45, f
	goto	$+2
	decfsz	r46, f
	goto	$+2
	decfsz	r47, f
	goto	Retardo_30s_0

			;1 cycle
	nop

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------

; Delay = 60 seconds
; Clock frequency = 16 MHz

; Actual delay = 60 seconds = 240000000 cycles
; Error = 0 %

	cblock
	r48
	r49
	r50
	r51
	endc

Retardo_60s
			;239999992 cycles
	movlw	0xA9
	movwf	r48
	movlw	0xE7
	movwf	r49
	movlw	0x97
	movwf	r50
	movlw	0x02
	movwf	r51
Retardo_60s_0
	decfsz	r48, f
	goto	$+2
	decfsz	r49, f
	goto	$+2
	decfsz	r50, f
	goto	$+2
	decfsz	r51, f
	goto	Retardo_60s_0

			;4 cycles
	goto	$+1
	goto	$+1

			;4 cycles (including call)
	return

;----------------------------------------------------------------------------------------
;
;      Librería de retardos para oscilador de 16 MHz.
;
;      Web: http://electronica-pic.blogspot.com
;
;*****************************************************************************************

