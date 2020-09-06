#INCLUDE <P16F887.INC>
    LIST P=16F887
; CONFIG1
; __config 0xEFC2
 __CONFIG _CONFIG1, _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _MCLRE_OFF & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_ON & _FCMEN_ON & _LVP_OFF
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF
 
 ;udata
 ;BYTES RES 3
 SEND_BITS_IR EQU D'9'
 
 CBLOCK 0x20
    BYTE
    CONTADOR
    CONTADOR_2
    r52
 ENDC
 
 ORG 0
SETUP:
BSF STATUS, RP0 ;BANCO 1
    BCF STATUS, RP1
    BCF TRISD, 0    ;RD0 -> PIN DE SALIDA DIGITAL.
    BSF TRISA, 4
    MOVLW B'11010100'
    MOVWF OPTION_REG
    BCF STATUS, RP0 ;BANCO 0
    BCF PORTD, 0    ;INICIALIZAR EL PIN RD0 EN 0.
 REC:
    BTFSC PORTA,4
    GOTO ACT_RLF
    GOTO REC
ACT_RLF:
    BTFSC PORTA,4
    GOTO ACT_RLF
    MOVLW D'255'
    CALL IRcarrier
    MOVLW D'110'
    CALL IRcarrier
    CALL RETARDO_4500MICROS_16
    MOVLW 0xFF
    CALL IRsend
    MOVLW 0xA2
    CALL IRsend
    MOVLW 0x5D
    CALL IRsend
    MOVLW 0xFF
    CALL IRsend
    MOVLW D'24'
    CALL IRcarrier
    GOTO REC

 RETARDO_1686MICROS_16:
    BCF INTCON,T0IF
    MOVLW D'45'
    MOVWF TMR0
 RETARDO_1686MICROS_16_0:
    BTFSS INTCON,T0IF
    GOTO RETARDO_1686MICROS_16_0
    RETURN
    
 RETARDO_562MICROS_16:
    BCF INTCON,T0IF
    MOVLW D'186'
    MOVWF TMR0
 RETARDO_562MICROS_16_0:
    BTFSS INTCON,T0IF
    GOTO RETARDO_562MICROS_16_0
    RETURN
    
 RETARDO_4500MICROS_16:
    BSF STATUS,RP0
    MOVLW B'11010110'
    MOVWF OPTION_REG
    BCF STATUS,RP0
    BCF STATUS,RP0
    BCF INTCON,T0IF
    MOVLW D'115'
    MOVWF TMR0
 RETARDO_4500MICROS_16_0:
    BTFSS INTCON,T0IF
    GOTO RETARDO_4500MICROS_16_0
    RETURN
    
IRcarrier:
    MOVWF CONTADOR
BUCLE:
    BSF PORTD,0
    DECFSZ CONTADOR,1
    GOTO RETARDO_13
    GOTO FINAL		
RETARDO_13:	
    movlw	0xE
    movwf	r52
RETARDO_13MICROS_16_0_1:
    decfsz	r52, f
    goto	RETARDO_13MICROS_16_0_1
    BCF PORTD,0
    movlw	0xE
    movwf	r52
RETARDO_13MICROS_16_0_2:
    decfsz	r52, f
    goto	RETARDO_13MICROS_16_0_2
    GOTO BUCLE
 FINAL:
    BCF PORTD,0
    RETURN
    
 IRsend:
    MOVWF BYTE
    MOVLW SEND_BITS_IR
    MOVWF CONTADOR_2
    BSF STATUS,RP0
    MOVLW B'11010100'
    MOVWF OPTION_REG
    BCF STATUS,RP0
BUCLE_SEND:
    DECFSZ CONTADOR_2,1
    GOTO ENVIO
    RETURN ;SI ES 0.
ENVIO:
    MOVFW BYTE
    ANDLW 0x1
    BTFSS STATUS,Z
    GOTO SEND_1	;SI ES 1.
    GOTO SEND_0	;SI ES 0.
ROTACION:
    RRF BYTE,1
    BCF BYTE,7
    GOTO BUCLE_SEND
SEND_1:
    MOVLW D'24'
    CALL IRcarrier
    CALL RETARDO_1686MICROS_16
    GOTO ROTACION
SEND_0:
    MOVLW D'24'
    CALL IRcarrier
    CALL RETARDO_562MICROS_16
    GOTO ROTACION
    END