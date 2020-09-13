 LIST P=16F628A
 PROCESSOR P16F628A
 #INCLUDE<P16F628A.INC>
; CONFIG
; __config 0xFF42
 __CONFIG _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _MCLRE_OFF & _BOREN_ON & _LVP_OFF & _CPD_OFF & _CP_OFF
 
CAMBIO_COLOR EQU 0x55
CAMBIO_BRILLO EQU 0xAA
MODO_AUTO EQU 0xFF
 
 CBLOCK 0x20
    R_CONTA
    R_CONTB
 ENDC
 
 ORG 0
SETUP:
    BSF STATUS,RP0
    BCF STATUS,RP1	;BANCO 1.
    BCF TRISA,0
    MOVLW B'01110010'	;BOTONES, ;SALIDA TX -> B2, ENTRADA RX -> B1.
    MOVWF TRISB
    MOVLW B'00100100'
    MOVWF TXSTA
    MOVLW D'25'		;2400 BAUDIOS.
    MOVWF SPBRG
    BCF STATUS,RP0	;BANCO 0.
    MOVLW 0x07
    MOVWF CMCON		;APAGA LOS COMPARADORES.
    MOVLW B'10001000'
    MOVWF RCSTA
PROGRAMA:
    BTFSC PORTB,4
    GOTO CAMBIO_RGB
    BTFSC PORTB,5
    GOTO CAMBIO_PWM
    BTFSC PORTB,4
    GOTO CAMBIO_AUTO
    GOTO PROGRAMA 

CAMBIO_RGB:
    BTFSC PORTB,4
    GOTO CAMBIO_RGB
    BSF PORTA,0
    MOVLW CAMBIO_COLOR
    MOVWF TXREG
    CALL RETARDO_20MS
    GOTO PROGRAMA
    
CAMBIO_PWM:
    BTFSC PORTB,5
    GOTO CAMBIO_PWM
    MOVLW CAMBIO_BRILLO
    MOVWF TXREG
    CALL RETARDO_20MS
    GOTO PROGRAMA
    
CAMBIO_AUTO:
    BTFSC PORTB,4
    GOTO CAMBIO_AUTO
    MOVLW MODO_AUTO
    MOVWF TXREG
    CALL RETARDO_20MS
    GOTO PROGRAMA

RETARDO_20MS:				; La llamada "call" aporta 2 ciclos m�quina.
    MOVLW	D'20'			; Aporta 1 ciclo m�quina. Este es el valor de "M".
    MOVWF	R_CONTB			; Aporta 1 ciclo m�quina.
R1MS_BUCLEEXTERNO:
    MOVLW	D'249'			; Aporta Mx1 ciclos m�quina. Este es el valor de "K".	
    MOVWF	R_CONTA			; Aporta Mx1 ciclos m�quina.
R1MS_BUCLEINTERNO:
    NOP				; Aporta KxMx1 ciclos m�quina.
    DECFSZ	R_CONTA,F		; (K-1)xMx1 cm (cuando no salta) + Mx2 cm (al saltar).
    GOTO	R1MS_BUCLEINTERNO	; Aporta (K-1)xMx2 ciclos m�quina.
    DECFSZ	R_CONTB,F		; (M-1)x1 cm (cuando no salta) + 2 cm (al saltar).
    GOTO	R1MS_BUCLEEXTERNO	; Aporta (M-1)x2 ciclos m�quina.
    RETURN
    END
 


