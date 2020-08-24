;CONFIGURACIONES DE PUERTOS.
IRTRIS equ TRISB
IRPORT equ PORTB
IRBIT equ 4	    ;IR EN PORTB<4>
SEND_BITS_IR equ D'25'
 
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
;COUNTER         res     1       ; used as counter in various loops
BYTES		res	3
		
CBLOCK
    CONTADOR
    CONTADOR_2
    r52
ENDC

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
    BSF TRISA, 4
    BCF STATUS, RP0 ;BANCO 0
    BCF PORTD, 0    ;INICIALIZAR EL PIN RD0 EN 0.
    RETURN
    
;Saca una señal de 38MHz durante un tiempo (microsegundos).
;void IRcarrier(int microsegundos) 
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
    ;CALL RETARDO_13MICROS_16
    movlw	0xE
    movwf	r52
RETARDO_13MICROS_16_0_2:
    decfsz	r52, f
    goto	RETARDO_13MICROS_16_0_2
    GOTO BUCLE
FINAL:
    BCF PORTD,0
    RETURN
    
;Manda una señal de acuerdo al protocolo NEC, 1 -> 2.25ms y 0 -> 1.25ms
;void IRsend(int dato)
IRsend:
    MOVLW SEND_BITS_IR
    MOVWF CONTADOR_2
BUCLE_SEND:
    DECFSZ CONTADOR_2,1
    GOTO ENVIO
    MOVLW D'24'
    CALL IRcarrier
    RETURN ;SI ES 0.
ENVIO:
    MOVFW BYTES
    ANDLW 0x80
    BTFSS STATUS,Z
    GOTO SEND_1	;SI ES 1.
    GOTO SEND_0	;SI ES 0.
ROTACION:
    RLF BYTES+2,1
    RLF BYTES+1,1
    RLF BYTES,1
    BCF BYTES+2,0
    GOTO BUCLE_SEND
SEND_1:
    MOVLW D'24'
    CALL IRcarrier
    CALL RETARDO_1MS_16
    CALL RETARDO_500MICROS_16
    GOTO ROTACION
SEND_0:
    MOVLW D'24'
    CALL IRcarrier
    CALL RETARDO_500MICROS_16
    GOTO ROTACION