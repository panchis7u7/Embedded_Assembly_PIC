    PROCESSOR 16F887
    #INCLUDE <P16F887.INC>
    LIST P=16F887
; CONFIG1
; __config 0x2FC2
 __CONFIG _CONFIG1, _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _MCLRE_OFF & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_ON & _FCMEN_ON & _LVP_OFF
; CONFIG2
; __config 0x3FFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF
 
    #DEFINE RX_BYTE 0x01
    
    Genvars udata_shr	    ;logical group, shared area, general variables
    TEMP res 1
 
    CBLOCK 0x20
    CONTADOR
    UART
    GUARDA_W
    GUARDA_STATUS
    ENDC
    
    ORG 0
    GOTO SETUP
    ORG 4
    GOTO INTERRUPCION
SETUP:
    BSF STATUS,RP0	    ;BANCO 1.
    BCF STATUS, RP1
    BCF TRISC,2	    ;CCP1/PWM 1KHz.
    MOVLW B'00100000'	    ;HABILITA LA INTERRUPCION PARA RX (RECEPCION SERIAL) EN EUSART.
    MOVWF PIE1		    ;HABILITACION DE INTERRUPCION PARA RX.
    CLRF PIE2	    
    BSF TRISC,7		    ;PUERTO RX COMO ENTRADA.
    MOVLW D'25'		    ;RESULTADO DEL CALCULO PARA 2400 BAUDIOS.
    MOVWF SPBRG
    CLRF TRISD
    MOVLW D'249'
    MOVWF PR2
    BSF STATUS,RP1	    ;BANCO 3.
    CLRF ANSEL
    CLRF ANSELH
    BCF STATUS,RP0	    ;BANCO 0.
    BCF STATUS,RP1	    ;CONFIGURACION DEL PUERTO RX.
    CLRF PIR1
    BSF RCSTA,CREN	    ;HABILITACION.
    BCF RCSTA,SYNC	    ;OPERACION ASINCRONA.
    BSF RCSTA,SPEN	    ;HABILITACION DE PIN ENTRADA.
    MOVWF RCSTA
    MOVLW B'11000000'	    ;CONFIGURACION PARA INTERRUPCION RX.
    MOVWF INTCON	    ;INTERRUPCION EUSART, PEIE Y GIE.
    MOVLW B'00001100'
    MOVWF CCP1CON
    MOVLW D'204'
    MOVWF CCPR1L
    MOVLW B'00000101'
    MOVWF T2CON
    CLRF PORTD
    MOVF RCREG,W	    ;Flush receive buffer
    MOVF RCREG,W
    MOVF RCREG,W
    MOVLW 0x00
    MOVWF CONTADOR
    GOTO PROGRAMA
    
	;ESPERA AQUI HASTA QUE EL USUARIO HAGA UNA DESICION DEL MENU.
	;------------------------------------------------------------
ESPERA_CMD:
    BCF UART,RX_BYTE
ESPERA_CMD_NUEVO:
    BTFSC UART,RX_BYTE
    GOTO PROGRAMA
    GOTO ESPERA_CMD_NUEVO
	;MENU DE DESICIONES.
	;------------------------------------------------------------
    
PROGRAMA:
    BANKSEL TEMP
    MOVFW TEMP
    XORLW 0x55
    BTFSC STATUS,Z
    GOTO COLOR_COLOR
    
    MOVFW TEMP
    XORLW 0xAA
    BTFSC STATUS,Z
    GOTO CAMBIO_DUTY
    GOTO ESPERA_CMD

COLOR_COLOR:
    MOVLW D'1'
    ADDWF CONTADOR,1
    MOVFW CONTADOR
    ANDLW D'7'
    MOVWF PORTD
    GOTO ESPERA_CMD
    
CAMBIO_DUTY:
    MOVLW D'51'
    ADDWF CCPR1L,1
    GOTO ESPERA_CMD
    
INTERRUPCION:
    MOVWF GUARDA_W
    SWAPF STATUS,W
    BCF STATUS,RP0
    BCF STATUS,RP1
    MOVWF GUARDA_STATUS
    BTFSS PIR1,RCIF	    ;CHECAR SI LA INTERRUPCION ES DEL USART.
    GOTO EXIT 
    BTFSC UART,RX_BYTE	    ;SI RX_BIT ESTA ALTO, ENTONCES RXREG NO SE HA PROCESADO AUN.
    GOTO EXIT
    MOVF RCREG,W	    ;Read input byte into W
    MOVWF TEMP		    ;Store received byte to shared RAM
    BSF UART,RX_BYTE
    MOVFW RCREG		    ;PUEDE HABER UN SEGUNDO BYTE.
    BCF RCSTA,CREN
    BSF RCSTA,CREN
 EXIT:
    MOVFW RCREG
    MOVFW RCREG
    SWAPF GUARDA_STATUS,W
    MOVWF STATUS
    SWAPF GUARDA_W,F
    SWAPF GUARDA_W,W
    RETFIE
    END

