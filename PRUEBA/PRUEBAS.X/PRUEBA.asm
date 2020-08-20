#INCLUDE <P16F887.INC>
    LIST P=16F887
; CONFIG1
; __config 0xFFE1
 __CONFIG _CONFIG1, _FOSC_XT & _WDTE_OFF & _PWRTE_ON & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_ON & _FCMEN_ON & _LVP_ON
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF
 
 CBLOCK
 
 ENDC 
 ORG 0
    BSF STATUS, RP0
    MOVLW D'124'
    MOVWF PR2
    BCF TRISC, 2
    BCF STATUS, RP0
    
    MOVLW D'37'
    MOVWF CCPR1L
    
    MOVLW B'00001100'
    MOVWF CCP1CON
    MOVLW B'00000101'
    MOVWF T2CON
    
PROGRAMA:
    NOP
    GOTO PROGRAMA
 END