;CONFIGURACIONES DE PUERTOS.
IRTRIS equ TRISB
IRPORT equ PORTB
IRBIT equ 4	    ;IR EN PORTB<4>
 
 ;PARAMETROS DE CONTROL REMOTO.
HEADER_LENGTH   equ     D'24'      ; header length = 2300 - 2500 us
SPACE_LENGTH    equ     D'6'       ; space length = 500 - 700 us
ONE_LENGTH      equ     D'11'      ; one length = 1000 - 1200 us
ZERO_LENGTH     equ     D'6'       ; zero length = 500 - 700 us
END_LENGTH      equ     D'12'      ; tail length = 1100 - 1300 us
      
;BITS EN IR_FLAGS.
BYTE_READY      equ     0       ; there is a signal in REC_BYTE2:REC_BYTE1
PREV            equ     1       ; value (1 = pulse, 0 = space) of last sample
RCV             equ     2       ; set if receiving a signal
 
;VARIABLES.
IR_FLAGS        res     1       ; flags for IR reception
CURR_TIME       res     1       ; time (/100us) so far in current pulse/space
PULSE_TIME      res     1       ; length (/100us) of last pulse
SPACE_TIME      res     1       ; length (/100us) of last space
REC_BYTE1       res     1       ; first byte that received bits are shifted into
REC_BYTE2       res     1       ; second byte that received bits are shifted into
COUNTER         res     1       ; used as counter in various loops
CONTADOR_2	res	1
BITS_IR		res	1

;MACROS.
; if not(literal - 1 <= file <= literal + 1) goto toAdr
bNotClose MACRO file, literal, toAdr
    movf file,W             ; move file to W
    sublw literal + 1       ; if (literal + 1 - file < 0)
    bnc toAdr                ;   goto toAdr
    sublw 2                 ; if (1 + file - literal < 0)
    bnc toAdr                ;   goto toAdr
    ENDM
    
;Inicializa los pines de entrada y salida del microcontrolador.
IRsetup:
    BSF STATUS, RP0 ;BANCO 1
    BCF STATUS, RP1
    BCF TRISD, 0    ;RD0 -> PIN DE SALIDA DIGITAL.
    BCF STATUS, RP0 ;BANCO 0
    BCF PORTD, 0    ;INICIALIZAR EL PIN RD0 EN 0.
    RETURN
    
;Saca una se�al de 38MHz durante un tiempo (microsegundos).
;void IRcarrier(int microsegundos)
IRcarrier:
    MOVWF BITS_IR
    MOVLW 0x00
    MOVWF CONTADOR_2
BUCLE:
    BSF PORTD,0
    MOVFW CONTADOR_2
    ADDLW D'1'
    MOVWF CONTADOR_2
    SUBWF BITS_IR,W
    BTFSC STATUS,Z
    GOTO FINAL		
    CALL RETARDO_20MICROS_16	
    BCF PORTD,0
    CALL RETARDO_20MICROS_16
    GOTO BUCLE
FINAL:
    BCF PORTD,0
    RETURN
    