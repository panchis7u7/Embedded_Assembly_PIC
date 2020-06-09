#INCLUDE <P16F887.INC>
LIST P=16F887
; CONFIG1
; __config 0xFFE1
 __CONFIG _CONFIG1, _FOSC_XT & _WDTE_OFF & _PWRTE_ON & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_ON & _FCMEN_ON & _LVP_ON
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF
CBLOCK
    contador
ENDC
ORG 0
CONFIGURACION
    BSF STATUS,RP0	;BANCO 1
    BCF STATUS,RP1
    CLRF TRISD		;SE DECLARAN TODOS LOS PINES DEL PUERTO D COMO SALIDA
    BSF TRISA,0		;SE DECLARA EL PIN RA0 COMO ENTRADA
    BSF STATUS,RP0	;BANCO 3
    BSF STATUS,RP1
    BSF ANSEL,0		;AN0 TIENE ENTRADA ANALOGICA
    CLRF ANSELH		;TODOS LO PINES DIFERENTES A AN0 SON DIGITALES
    BSF STATUS,RP0	;BANCO 1
    BCF STATUS,RP1
    CLRF ADCON1		;JUSTIFICACION A LA IZQUIERDA
    BCF STATUS,RP0	;BANCO 0
    BCF STATUS,RP1
    MOVLW B'00000001'	;FOSC/2, AN0, ADC ENABLE 0
    MOVWF ADCON0
DELAY
    MOVLW D'19'		
    MOVWF contador
DELAY_BUCLE		;TIEMPE DE ADQUISICION
    DECFSZ contador,1
    GOTO DELAY_BUCLE	
    BSF ADCON0,GO	;EL ADC EMPIEZA CON LA CONVERSION
ADC_INICIO
    BTFSC ADCON0,GO	;CHECA SI EL ADC TERMINO CON LA CONVERSION
    GOTO ADC_INICIO
    MOVF ADRESH,W	;REGISTRO EN DONDE SE GUARDA EL RESULTADO DE LA CONVERSION
    MOVWF PORTD	    
    GOTO DELAY
END
    

