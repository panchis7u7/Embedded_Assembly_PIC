#INCLUDE <P16F887.INC>
LIST P=16F887
#INCLUDE <MACROS.INC>
; CONFIG1
; __config 0x2FC2
 __CONFIG _CONFIG1, _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _MCLRE_OFF & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_ON & _FCMEN_ON & _LVP_OFF
; CONFIG2
; __config 0x3FFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF
 
 START_PASSED EQU 0x1
 
 CBLOCK 0x20
    IR_FLAGS
    DIGITO
    TEMP
    CONTADOR
    CONTADOR_2
    REC_BYTE1
    REC_BYTE2
ENDC

    ORG 0
    GOTO SETUP
    ORG 4
    GOTO INT_HANDLE
SETUP:
    LCD_INIT
    CALL IR_INIT
START:
    WRITE_LCD 'C'
    WRITE_LCD 'O'
    WRITE_LCD 'D'
    WRITE_LCD 'I'
    WRITE_LCD 'G'
    WRITE_LCD 'O'
    WRITE_LCD ':'
    CLRF CONTADOR
    MOVFW REC_BYTE2
    MOVWF TEMP
    CALL IMPRIMIR_VAR
    MOVFW REC_BYTE1
    MOVWF TEMP
    CALL IMPRIMIR_VAR
    ORIGIN_LCD
    ONLY_DISPLAY
    ;CALL IR_RCV
PRUEBA:
    MOVLW D'13'
    SUBWF CONTADOR_2,0
    BTFSS STATUS,Z
    GOTO PRUEBA
    BCF IR_FLAGS,START_PASSED
    CLRF CONTADOR_2
    BCF STATUS,C
    RRF REC_BYTE1
    RRF REC_BYTE2
    BCF STATUS,C
    RRF REC_BYTE1
    RRF REC_BYTE2
    BCF STATUS,C
    RRF REC_BYTE1
    RRF REC_BYTE2
    BCF STATUS,C
    RLF REC_BYTE1
    RLF REC_BYTE1
    BCF STATUS,C
    GOTO START

IMPRIMIR_VAR:
    INCF CONTADOR
    MOVLW D'9'
    MOVWF DIGITO
    SWAPF TEMP,1
    MOVFW TEMP
    ANDLW 0xF
    SUBWF DIGITO,1
    BTFSC STATUS,C
    GOTO DECIMAL
    GOTO HEXADECIMAL
DECIMAL:
    MOVWF DIGITO
    WRITE_LCD_REG DIGITO
    GOTO VERIFICACION
HEXADECIMAL:
    MOVWF DIGITO
    WRITE_LCD_REG_HEX DIGITO
VERIFICACION:
    MOVLW D'2'
    SUBWF CONTADOR,0
    BTFSS STATUS,Z
    GOTO IMPRIMIR_VAR
    CLRF CONTADOR
    RETURN
    
IR_INIT: 
    BSF STATUS,RP0
    BSF STATUS,RP1
    CLRF ANSEL
    CLRF ANSELH
    BSF STATUS,RP0
    BCF STATUS,RP1
    BSF TRISB,0		; IR is input
    CLRF TRISD
    MOVLW B'01000011'	;PRESCALLER:16.
    MOVWF OPTION_REG
    BCF STATUS,RP0      ; Select memory bank 0
    MOVLW B'10010000'
    MOVWF INTCON
    CLRF PORTD
    CLRF REC_BYTE1
    CLRF REC_BYTE2
    CLRF CONTADOR
    CLRF CONTADOR_2
    CLRF IR_FLAGS
    RETURN
    
INT_HANDLE:
    INCF CONTADOR_2,1
    CALL RETARDO_50MICROS
    BTFSC IR_FLAGS,START_PASSED
    GOTO IR_RCV
    CALL RETARDO_1200MICROS
    CALL RETARDO_1200MICROS
    BTFSS PORTB,0
    GOTO VERIFICACION_2
    BSF IR_FLAGS,START_PASSED
    GOTO VERIFICACION_2
IR_RCV:
    CALL RETARDO_600MICROS
    BTFSC PORTB,0
    GOTO UNO
CERO:
    BCF STATUS,C
    RRF REC_BYTE1
    RRF REC_BYTE2
    GOTO VERIFICACION_2
UNO:
    BSF STATUS,C
    RRF REC_BYTE1
    RRF REC_BYTE2
VERIFICACION_2:
    BCF INTCON,INTF
    RETFIE
    
;IR_RCV:
;BEGIN:
;    BTFSC PORTB,4
;    GOTO BEGIN
;    CALL RETARDO_1200MICROS
;    BTFSS PORTB,4
;    GOTO BEGIN
;    CALL RETARDO_600MICROS
;BUCLE:
;    CALL RETARDO_600MICROS
;    BTFSS PORTB,4
;    GOTO UNO
;CERO: 
;    BCF STATUS,C
;    RRF REC_BYTE1
;    RRF REC_BYTE2
;    CALL RETARDO_600MICROS
;    GOTO VERIFICACION_2
;UNO:
;    BSF STATUS,C
;    RRF REC_BYTE1
;    RRF REC_BYTE2
;    CALL RETARDO_1200MICROS
;VERIFICACION_2:
;    INCF CONTADOR,1
;    MOVLW D'11'
;    SUBWF CONTADOR,0
;    BTFSS STATUS,Z
;    GOTO BUCLE
;    RETURN

;RETARDO DE 1.2MS USANDO TIMER0.
RETARDO_1200MICROS:
    BCF INTCON,T0IF
    MOVLW D'106'
    MOVWF TMR0
COMPROBAR:
    BTFSS INTCON,T0IF
    GOTO COMPROBAR
    RETURN
    
;RETARDO DE 600 MICROS USANDO TIMER0.
RETARDO_600MICROS:
    BCF INTCON,T0IF
    MOVLW D'219'
    MOVWF TMR0
COMPROBAR_2:
    BTFSS INTCON,T0IF
    GOTO COMPROBAR_2
    RETURN
    
;RETARDO DE 50 MICROS USANDO TIMER0.
RETARDO_50MICROS:
    BCF INTCON,T0IF
    MOVLW D'253'
    MOVWF TMR0
COMPROBAR_3:
    BTFSS INTCON,T0IF
    GOTO COMPROBAR_3
    RETURN
    
    #INCLUDE <RETARDOS.inc>
    #INCLUDE <LCD20X4.inc>
    #INCLUDE <BCD.INC>
    END


