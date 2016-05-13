;=====================================================================
;			RAND 1 PROGRAM
;	DESCRIPTION:
;	PRINT 10 RANDOM NUMBERS
;	USING 5555H AS SEED
;=====================================================================

	DOSSEG
	.MODEL  LARGE,BASIC

							;PROCEDURES TO
	EXTRN	CLEAR:FAR		;CLEAR SCREEN
	EXTRN	GETDEC:FAR		;GET 16-BIT DECIMAL INTEGER
	EXTRN	NEWLINE:FAR		;DISPLAY NEWLINE CHARACTER
	EXTRN	PUTDEC$:FAR		;DISPLAY 16-BIT DECIMAL INTEGER
	EXTRN	PUTSTRNG:FAR	;DISPLAY CHARACTER STRING
	EXTRN	PAUSE:FAR		;DISPLAY CHARACTER STRING
	EXTRN	RANDOM:FAR
	;EXTRN	RESEED:FAR
	
;===================================================================
;
; S T A C K   S E G M E N T   D E F I N I T I O N
;
	.STACK  256

;===================================================================
;
; C O N S T A N T   S E G M E N T   D E F I N I T I O N
;
.CODE
.DATA
HEADR		DB	'10 RANDOM NUMBERS BASED ON 5555H SEED: '
PAUMSG		DB	'PRESS ANY KEY TO CONTINUE ... '
UPPER		DW	9999
LOWER		DW	0
;===============================================================
;
; D A T A   S E G M E N T   D E F I N I T I O N
;
SEED		DW	5555H
COUNT		DW	10
;===============================================================
;
; C O D E   S E G M E N T   D E F I N I T I O N
;
	.CODE
	;ASSUME DS:NOTHING,ES:DGROUP
STARTUP:
	MOV		AX,DGROUP		;SET ES TO POINT TO DATA SEG
	MOV		ES,AX
	
	MOV		AX,DGROUP
	MOV		DS,AX
	;MOV		AX,SEED
			
	LEA		DI,HEADR
	MOV		CX,39
	CALL	PUTSTRNG
	CALL	NEWLINE
	
RANDLOOP:
			PUSH	LOWER					; PUSH LOWER FIRST
			PUSH	UPPER					; THEN UPPER	
			CALL	RANDOM					; GET RANDOM
			
			MOV		BH, 0
			CALL	PUTDEC$
			
			CALL	NEWLINE
			
			DEC		COUNT
			CMP		COUNT,0					; IF COUNT != 0,LOOP AGAIN
			JNE		RANDLOOP				; LOOP AGAIN	
DONE:
	LEA		DI,PAUMSG
	MOV		CX,30
	CALL PAUSE
	.EXIT
END STARTUP