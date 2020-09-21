;::::::::::::: www.rodrigocarita.com ::::::::::::::::::::::::::
; 			Retardos.asm   Versión: 1.0

; Librería de retardos por bucles anidados.
; 
;             Se utiliza con la Macro.inc
; milisegundo .2   -> Genera un retardo de 2 milisegundos
; Segundo .6 -> Genera un retardo de 6 segundos
; Los valores deben estar entre 0 a 255.

	cblock	                	
	memo_tiemp_1        
	memo_tiemp_2        
	memo_tiemp_3        
	memo_tiemp_4
	endc

milisegundos
         movwf  memo_tiemp_1
    retbucle1
         movlw  .17
         movwf  memo_tiemp_2 
    retbucle2
         movlw  .58
         movwf  memo_tiemp_3     
    retbucle3
         nop
         nop
         decfsz memo_tiemp_3,1     
         goto   retbucle3
         decfsz memo_tiemp_2,1
         goto   retbucle2
         decfsz memo_tiemp_1,1
         goto   retbucle1
RETURN
segundos
         movwf  memo_tiemp_1
    retbucle1a
         movlw  .250
         movwf  memo_tiemp_2 
    retbucle2a
         movlw  .250
         movwf  memo_tiemp_3     
    retbucle3a
         movlw  .19
         movwf  memo_tiemp_4 
    retbucle4a
         nop
         decfsz memo_tiemp_4,1 
         goto   retbucle4a
         decfsz memo_tiemp_3,1    
         goto   retbucle3a
         decfsz memo_tiemp_2,1
         goto   retbucle2a
         decfsz memo_tiemp_1,1
         goto   retbucle1a
RETURN


