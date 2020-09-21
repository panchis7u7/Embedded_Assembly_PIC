CBLOCK
BCD_UNIDAD
BCD_DECENA
BCD_CENTENA
ENDC

BINARIO_BCD:
    MOVWF  BCD_UNIDAD    ;Carga el número binario a convertir
    CLRF   BCD_CENTENA    ;Borra registro
    CLRF   BCD_DECENA     ;Borra registro
BCD_RESTA10:
    MOVLW  .10             ;A las unidades de les va restando
    SUBWF  BCD_UNIDAD,0  ;10 en cada pasada 
    BTFSS  STATUS,C        ;C=0? si- entonces bcd_unidad>=0
    GOTO   BIN_BCD_Fin     ;No- entonces se acabo  
BCD_IncrementarDecenas:     
    MOVWF  BCD_UNIDAD    ;Recupera lo que queda por restar
    INCF   BCD_DECENA,1   ;Incrementa las decenas 
    MOVLW  .10
    SUBWF  BCD_DECENA,0   ;Comprueba si a llegado a 10
    BTFSS  STATUS,C        ;C=1? si- entonces bcd_decena>=0 
    GOTO   BCD_RESTA10     ;No- entonces resta 10 a las unidades
BCD_IncrementarCentenas:
    CLRF   BCD_DECENA     ;Pone a cero las decenas
    INCF   BCD_CENTENA,1  ;Incrementa las centenas
    GOTO   BCD_RESTA10     ;Resta 10 al número a convertir
BIN_BCD_Fin:
    SWAPF  BCD_DECENA,0   ;Intercambia nibles
    ADDWF  BCD_UNIDAD,0  ;Nible bajo=unidades / Nible alto=decenas
    RETURN




