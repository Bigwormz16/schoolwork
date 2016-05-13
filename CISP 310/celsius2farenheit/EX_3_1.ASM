           PAGE    80,132
;===================================================================
;
;                  PROGRAM LISTING 3.1
;
; PROGRAM  TO  CONVERT  A  TEMPERATURE  FROM
; CELSIUS TO FAHRENHEIT USING THE FORMULA
;
; C = 5*(F-32)/9  ROUNDED TO NEAREST INTEGER
; ----> F = ((C*9)/5) + 32
;===================================================================
           DOSSEG
           .MODEL  SMALL,BASIC,FARSTACK
;===================================================================
                                       ;PROCEDURES TO
           EXTRN   GETDEC:FAR          ;GET 16-BIT DECIMAL INTEGER
           EXTRN   NEWLINE:FAR         ;DISPLAY NEWLINE CHARACTER
           EXTRN   PUTDEC:FAR          ;DISPLAY 16-BIT DECIMAL INTEGER
           EXTRN   PUTSTRNG:FAR        ;DISPLAY CHARACTER STRING
		   EXTRN   PAUSE:FAR
;===================================================================
;
; S T A C K   S E G M E N T   D E F I N I T I O N
;
           .STACK  256
;===================================================================
;
; C O N S T A N T   S E G M E N T   D E F I N I T I O N
;
           .CONST
PROMPT     DB      'ENTER TEMPERATURE IN DEGREES CELSIUS     '
ANNOTATION DB      '      TEMPERATURE IN DEGREES FARENHEIT   '
PRNTNAME   DB      'IAN ROSNER    PROGRAM 3        '
PAUSEMSG   DB      ' PRESS ANY KEY TO CONTINUE ... '
;===================================================================
;
; C O D E   S E G M E N T   D E F I N I T I O N
;
           .CODE
EX_3_1:
           MOV     AX,SEG DGROUP       ;SET ES-REGISTER TO ADDRESS
           MOV     ES,AX               ;    DGROUP
;
           LEA     DI,PROMPT           ;PROMPT FOR F_TEMP
           MOV     CX,40
           CALL    PUTSTRNG
           CALL    GETDEC              ;GET C_TEMP
           MOV     BX,9					;STEP 1: MULTIPLY BY 9
           IMUL    BX                   ;
           MOV     BX,5					;STEP 2: DIVIDE BY 5
           IDIV    BX
           XCHG    AX,DX               ;REMAIN = (C*9) rem 5
           MOV     BL,5                ;ROUND  = REMAIN / 5
           IDIV    BL
		   ADD     AX,32			   ;STEP 3: ADD 32
           CBW
           ADD     AX,DX               ;F_TEMP = F_TEMP + ROUND
;
           LEA     DI,ANNOTATION       ;DISPLAY F_TEMP
;          MOV     CX,42
           CALL    PUTSTRNG
           MOV     BH,0
           CALL    PUTDEC
           CALL    NEWLINE
		   CALL	   NEWLINE
		   LEA     DI,PRNTNAME
		   MOV     CX,30
		   CALL    PUTSTRNG
		   CALL    NEWLINE
		   LEA     DI,PAUSEMSG
		   CALL    PAUSE
           .EXIT                       ;RETURN TO DOS
;
           END     EX_3_1
;===================================================================