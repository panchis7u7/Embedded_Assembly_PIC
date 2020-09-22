puertoa EQU PORTA
puertob EQU PORTB
puertoc EQU PORTC
puertod EQU PORTD
puertoe EQU PORTE

;-------------------------------- MACRO PINES ----------------------------------
ON MACRO PIN,PORT
	BSF PORT,PIN
	ENDM
OFF MACRO PIN,PORT
	BCF PORT,PIN
	ENDM
SETF MACRO REG0
	MOVLW D'255'
	MOVWF REG0
	ENDM

;--------------------------------- MACRO REG -----------------------------------
MOV_VAL MACRO VALUE,REG
	MOVLW VALUE
	MOVWF REG
	ENDM

COPY_REG MACRO REG_SRC,REG_DEST
	MOVF REG_SRC,0
	MOVWF REG_DEST
	ENDM

;--------------------------------- MACRO REG -----------------------------------
SEL_BANK MACRO NO_BANK
	IF NO_BANK==0
	BCF STATUS, RP0
	BCF STATUS, RP1
	ENDIF

	IF NO_BANK==1
	BSF STATUS, RP0
	BCF STATUS, RP1
	ENDIF

	IF NO_BANK==2
	BCF STATUS, RP0
	BSF STATUS, RP1
	ENDIF

	IF NO_BANK==3
	BSF STATUS, RP0
	BSF STATUS, RP1
	ENDIF
	ENDM

;----------------------------- REG COMPARE EQUAL -------------------------------
REG_EQUAL_JMP MACRO REG1,REG2,LABEL
	MOVF	REG2,0
	SUBWF	REG1,0
	BTFSC	STATUS,Z
	GOTO	LABEL
	ENDM
;---------------------------- REG COMPARE !EQUAL -------------------------------
REG_NE_JMP MACRO REG1,REG2,LABEL
	MOVF	REG2,0
	SUBWF	REG1,0
	BTFSC	STATUS,Z
	GOTO	LABEL
	ENDM

;-------------------------- REG COMPARE EQUAL VALUE ----------------------------
REG_VAL_EQ_JMP MACRO REG1,VAL,DIR
	MOVLW	VAL
	SUBWF	REG1,0
        BTFSC	STATUS,Z
        GOTO	DIR
	ENDM
	
;------------------------- REG COMPARE EQUAL !VALUE ----------------------------
REG_VAL_NEQ_JMP MACRO REG1,VAL,DIR
	MOVLW VAL
	SUBWF REG1,0
	BTFSS STATUS,Z
	GOTO DIR
	ENDM

; Compara registro con un valor y si  se cumple la condicion Reg>valor se va a la subrutina
mayorque macro registro1,valor ,subrutina
		MOVLW valor
		SUBWF registro1,0
		BTFSC STATUS,C
		GOTO subrutina
endm
; Compara registro con un valor y si  se cumple la condicion Reg<valor se va a la subrutina
menorque macro registro1,valor ,subrutina
		MOVLW valor
		SUBWF registro1,0
		BTFSS STATUS,C
		GOTO subrutina
endm
; Compara registro con un valor y si se cumple la condicion Reg>Reg2se va a la subrutina
mayorquereg macro registro1,registro2 ,subrutina
		MOVF registro2,0
		SUBWF registro1,0
		BTFSC STATUS,C
		GOTO subrutina
endm
; Compara registro con un valor y si se cumple la condicion Reg<Reg2 se va a la subrutina
menorquereg macro registro1,registro2,subrutina
		MOVF registro2,0
		SUBWF registro1,0
		BTFSS STATUS,C
		GOTO subrutina
endm

; /////////////////////////////////// Para display 7 segmentos //////////////////////////////
enviaradisplay macro numnum
	MOVLW numnum
	CALL TABLAANODO
	MOVWF PORTD
endm
	
enviarcdisplay macro numnum
	MOVLW numnum
	CALL TABLACATODO
	MOVWF PORTD
endm

registroadisplay macro numnum
	MOVF numnum,0
	CALL TABLAANODO
	MOVWF PORTD
endm

registrocdisplay macro numnum
	MOVF numnum,0
	CALL TABLACATODO
	MOVWF PORTD
endm
;...............................................///////////////////////////////////........................./////////////////////////
on_lib_retardos_ms macro
	CALL CONFTMR0TEMP
endm

retardo_ms macro valor
	MOVLW valor
	CALL RETARDOLIBRE_mS
endm

;Conversor de Binario a BCD. La respuesta se guarda en registros bcd_unidad, bcd_decena, bcd_centena
BCD_CONVERT MACRO REG
	MOVF REG,0
	CALL BINARIO_BCD
    ENDM

;Codigo de macro para Retardos
milisegundo	 macro X
			 movlw X
			 call  milisegundos
			 endm
segundo    	 macro X
			 movlw X
			 call  segundos
			 endm
;//////////////////////////////////////////////////////////////////////////////
; Macro para LCD Información sobre comandos en www.rodrigocarita.com
; Para controlar la pantalla LCD 2x16

LCD_INIT MACRO			;Con esto desarrollamos la secuencia de inicio               
        CALL  Inicio_lcd
	ENDM
WRITE_LCD MACRO CHAR		;Con este comando enviaremos un caracter a la pantalla
        MOVLW CHAR
        CALL  ESCRIBIRCARACTER  ;Subrutina en la librería que me permite enviar el caracter
	ENDM
WRITE_LCD_REG MACRO REG4	;Con este comando enviaremos el valor de un registro a la pantalla
	MOVLW .48
	ADDWF REG4,0
        CALL  ESCRIBIRCARACTER   ;Subrutina en la librería que me permite enviar el valor
        ENDM
WRITE_LCD_REG_HEX MACRO REG4	;Con este comando enviaremos el valor de un registro a la pantalla
	MOVLW .55
	ADDWF REG4,0
        CALL  ESCRIBIRCARACTER   ;Subrutina en la librería que me permite enviar el valor
        ENDM
escribirregistro macro regREG3d     ;Subrutina para escribir en el LCD registro de 3 dígitos
		   MOVF regREG3d,0
		   CALL PARAESCR1B1RREGISTRO
endm
escribirmensaje macro
			CLRF indice
			SEcuENCIASUBcar1
			MOVF indice,0
			CALL aasdd
			MOVWF NumCadena
			csi NumCadena,.255,FUERALIM1T3
			MOVF NumCadena,0
			call  ESCRIBIRCARACTER
			INCF indice,1
			GOTO SEcuENCIASUBcar1
    ENDM	   
	   
;Aquí las macros para manipulación del cursor //////////////////////////////////////////
CURSOR_ON MACRO
	MOVLW on_display_cursor_blink ;Enciende el cursor y su parpadeo
        CALL  ESCRIBIRCOMANDO
    ENDM
CURSOR_OFF MACRO
	MOVLW solo_display        ;Apaga el cursor y muestra solamente el display
        CALL  ESCRIBIRCOMANDO
    ENDM
CURSOR_LEFT MACRO
	MOVLW mover_cursor_izquierda ;Mueve el cursor a la derecha
        call  ESCRIBIRCOMANDO
    ENDM
cursor_derecha macro
		movlw mover_cursor_derecha ;Mueve el cursor a la izquierda
        call  ESCRIBIRCOMANDO
		endm
	   
fila_enter     macro    ;Saltará de línea a la segunda fila
           movlw salto_enter
           call  ESCRIBIRCOMANDO
endm
ORIGIN_LCD macro
		movlw home_inicio
		call ESCRIBIRCOMANDO
endm
;//////////////////////////////////////////////////////
;//////////////////////////////////////// creado para la escritura en LCD mediante textos predeterminados.///////////
mensaje macro  x
        if x==.1
        call SubirCarActer1
        endif
        if x==.2
        call SubirCarActer2
        endif
		if x==.3
        call SubirCarActer3
        endif
		if x==.4
        call SubirCarActer4
        endif
		if x==.5
        call SubirCarActer5
        endif
		if x==.6
        call SubirCarActer6
        endif
		if x>.6
		ERROR "No hay mensaje predeterminado para el valor"
		MESSG "Revisa el comando mensjae .x"
		endif
        endm

;Se pueden agregar más, respetando la estructura de condicionales

;/////////////////////////////////////////////////////////////////////////////////////



;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
;\\\\\\\\\\\\\\\\\\\\\Manipulación del cursor solamente para pantallas de 20x4 ////////////////////////////
;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

ir_a_fila macro filaseleccionada

	if filaseleccionada==1
		movlw home_inicio
		call ESCRIBIRCOMANDO
	endif
	if filaseleccionada==2
		movlw home_inicio
		call ESCRIBIRCOMANDO
		movlw salto_enter
        call ESCRIBIRCOMANDO
	endif
	if filaseleccionada==3
		movlw 0x94
		call ESCRIBIRCOMANDO
	endif
	if filaseleccionada==4
		movlw 0xD4
		call ESCRIBIRCOMANDO
	endif
	if filaseleccionada>4
		ERROR "Has sobrepasado la cantidad de filas a usar"
		MESSG "Revisa el comando ir_a_fila que el valor sea"
		MESSG "de 1 a 4 solamente."
	endif
endm


; ///////////////////////Comando adicional ////////////////////////////////////////////////////////////////////////
;/////////////////////////////Para ir a un punto especifico del LCD //////////////////////////////////////////////
;/////////////////////////////////Solo para LCD20x4 //////////////////////////////////////////////////////////////
lcdfc macro lcdvalorf,lcdvalorc

	;/// Para seleccionar la fila
	if lcdvalorf==1
	MOVLW lcdvalorc
	MOVWF ubicacionlcdfcr
	DECF ubicacionlcdfcr,1
	MOVlW 0X80
	ADDWF ubicacionlcdfcr,0
	call ESCRIBIRCOMANDO
	endif
	if lcdvalorf==2
	MOVLW lcdvalorc
	MOVWF ubicacionlcdfcr
	DECF ubicacionlcdfcr,1
	MOVlW 0XC0
	ADDWF ubicacionlcdfcr,0
	call ESCRIBIRCOMANDO
	endif
	if lcdvalorf==3
	MOVLW lcdvalorc
	MOVWF ubicacionlcdfcr
	DECF ubicacionlcdfcr,1
	MOVlW 0X94
	ADDWF ubicacionlcdfcr,0
	call ESCRIBIRCOMANDO
	endif
	if lcdvalorf==4
	MOVLW lcdvalorc
	MOVWF ubicacionlcdfcr
	DECF ubicacionlcdfcr,1
	MOVlW 0XD4
	ADDWF ubicacionlcdfcr,0
	call ESCRIBIRCOMANDO
	endif
	;Para seleccionar la columna

endm

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\		

;Desde aquí los comandos para manipulación del display //////////////////////////////////////////
CLEAR_LCD  MACRO                ;Borra todo lo de la pantalla
        MOVLW limpiar_lcd
        CALL  ESCRIBIRCOMANDO
    ENDM
borrarfila macro valor
	lcdfc valor,.1
	CALL subp4arab0rf1l	
	lcdfc valor,.1
endm		   
 desplazaderecha  macro  		;Mueve todo lo escrito en la pantalla 1 a la derecha
               	  movlw  mover_pantalla_derecha
               	  call   ESCRIBIRCOMANDO             
                  endm
 desplazaizquierda  macro     	;Mueve todo lo escrito en la pantalla 1 a la izquierda         
				movlw  mover_pantalla_izquierda
				call   ESCRIBIRCOMANDO             
				endm
 apagarpantalla macro
				movlw apagar_el_display
				call ESCRIBIRCOMANDO
 endm
ONLY_DISPLAY MACRO
	MOVLW solo_display
	CALL ESCRIBIRCOMANDO
    ENDM
 
 ;/////////////////////////////////////////////////////////////////////////////////
 ;/////////////////////////////////////////////////////////////////////////////////
 ;Para enviar 1 pulso de duración programable
 ;Requiere de la Librería RETARDOS.ASM
 
 PULSOSUB macro pinp,registrop,duracion
		BSF registrop,pinp
		milisegundo duracion
		BCF registrop,pinp
 endm
 ;///////////////////// Operaciones matemáticas //////////////////////////////////
 ;//////////////////////////////////////////////////////
sumarreg macro registro1,registro2
   movf registro1,0
   movwf Reg15tr01
   movf registro2,0
   movwf Reg15tr02
   call Separaciondigit05
   call ParaSumarReg1str0s
endm

restarreg macro registrox1,registrox2; Hay que asegurarse que el registro 1 sea mayor al registro2.
   movf registrox1,0
   movwf Reg15tr01
   movf registrox2,0
   movwf Reg15tr02
   call ParaRestarReg1str0s2
endm
 
multiplicarreg macro registrom1,registrom2
   movf registrom1,0
   movwf Reg15tr01
   movf registrom2,0
   movwf Reg15tr02
   call Separaciondigit05
   call ParaMultiplicarReg1str0s
endm 

crearreg macro registroc1,registroc2,registroc3
   movf registroc1,0
   movwf Reg15tr01
   movf registroc2,0
   movwf Reg15tr02
   movf registroc3,0
   movwf Reg15tr03
   call ParaCrearReg1str0
endm

;////////////////////////////////////////////////////////////////////////////////////////////////////////////
;//////////////////////////////////// Para módulo HC-SR04 ///////////////////////////////////////////////////
;////////////////////////////////////////////////////////////////////////////////////////////////////////////  

iniciar_hcsr04  macro
	banco 1
	MOVLW b'00000111' ; Timer 0 como temporizador y escala 256
	MOVWF OPTION_REG  ; Cargamos la configuración en el TMR0
	banco 0
	BCF TRIGGER
	MOVLW .88 ;Cargamos el valor de ajuste de medida 51.2/58 = 0.88
         MOVWF Ajust3d1st ;En la variable de ajuste "Ajust3d1st"
endm

medir_ultrasonico macro Rresulm3edid4
	CALL Med1rdiist4nc1ia  ;Llama a la subrutina de medición
	MOVF valaux04,0        ;Extrae el valor de la respuesta en W 
	MOVWF Rresulm3edid4    ;Guarda la respuesta en el indicador de registro 
endm

;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 ;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ Para teclado 4x4         \\\\\\\\\\\\\\\\\\\\\\\\\\\\
 ;\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 
iniciar_teclado macro
	CALL IN1ci0t3cla4do
endm

leertecla macro
	BSF Sit3cl4pus,0
	CALL Tttest3aTecld0o
endm

irsitecla macro subrutdepulso
	BCF Sit3cl4pus,0
	CALL Tttest3aTecld0o
	MOVF tekl4pul5,0
	BTFSS Hhayrt3cla,0
	GOTO subrutdepulso
endm

llamarsitecla macro subrutdepulso
	BCF Sit3cl4pus,0
	CALL Tttest3aTecld0o
	MOVF tekl4pul5,0
	BTFSS Hhayrt3cla,0
	CALL subrutdepulso
endm

; ///////////////////////////////-------------------------//////////////////////////////////////////////////


