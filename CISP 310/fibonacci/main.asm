;=====================================================================
;			FIBONACCI PROGRAM
;	DESCRIPTION:
;	CALCULATES FIBONACCI SEQUENCE USING UP TO 72
;	DIGITS, ALERTS UPON EXCEEDING 72 DIGITS
;=====================================================================

	DOSSEG
	.MODEL  LARGE,BASIC
							;PROCEDURES TO
	EXTRN	NEWLINE:FAR		;DISPLAY NEWLINE CHARACTER
	EXTRN	PUTDEC$:FAR		;DISPLAY 16-BIT DECIMAL INTEGER
	EXTRN	PUTSTRNG:FAR	;DISPLAY CHARACTER STRING
	EXTRN	PAUSE:FAR		;DISPLAY CHARACTER STRING
	EXTRN	GETDEC$:FAR
	
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
HEADER		DB	'--72 DIGIT FIBONACCI--';22
HEADR2		DB	'ENTER NUMBER OF ITERATIONS TO PERFORM: ';39
OVERFL		DB	'OVERFLOW DETECTED AFTER ';24
OVERF2		DB	' ITERATIONS';11
DIGITS		DB	'DIGITS USED: ';13
;DEBUG		DB	'EXECUTED PAST THIS LINE'	;23 CHARS
PAUMSG		DB	'PRESS ANY KEY TO CONTINUE ... '
NAME_IR		DB	'FIBONACCI PROGRAM - IAN ROSNER'
;===============================================================
;
; D A T A   S E G M E N T   D E F I N I T I O N
;
FIB1		DB	72 DUP (0)
FIB2		DB	72 DUP (0)

CFLAG		DW	0
INPUT		DW	?	
;===============================================================
;
; C O D E   S E G M E N T   D E F I N I T I O N
;
	.CODE
	;ASSUME DS:NOTHING,ES:DGROUP
STARTUP:
	MOV		AX,DGROUP		;SET ES TO POINT TO DATA SEG
	MOV		ES,AX
	MOV		DS,AX
	
	LEA		DI,HEADER
		MOV		CX,22
		CALL	PUTSTRNG
		CALL	NEWLINE
	LEA		DI,HEADR2
		MOV		CX,39
		CALL	PUTSTRNG
	
	;LOOP COUNTER
	CALL	GETDEC$
	CALL	NEWLINE
	MOV		INPUT,AX
	
MAIN:
	MOV		DI,71
	MOV		FIB1[DI],1	;INITIAL VALUES ARE 1, 1
	MOV		FIB2[DI],1
	
	MOV		CX,INPUT
	
	;REGISTERS - 
	;AL CONTAINS CELL VALUES
	;BX - ODDS AND ENDS
	;CX CONTAINS LOOP COUNTER
	;DI CONTAINS CELL NUMBER [SUBSCRIPT]
	
OUTERLOOP:	;ITERATES CX AMOUNT OF TIMES (USER INPUT)
	MOV		DI,71
		INNERLOOP:	;ITERATES FROM 71 TO 0 (ARRAY LOOP [1 ITERATION])
			MOV		AL,FIB1[DI]		;GET VALUE FROM FIRST ARRAY
			ADD		AL,FIB2[DI]		;ADD VALUE FROM SECOND ARRAY
			
			.IF CFLAG == 1 ;ADD OUR CARRY
				INC		AL
				MOV		CFLAG,0
			.ENDIF
			
			CMP		AL,9		;IS VALUE <= 9?
			JLE		UNDER
				;OVER --- SUBTRACT 10, SET CARRY
				SUB		AL,10	;AL IS NOW READY TO BE SET TO FIB2
				;IF WE ARE AT LAST DIGIT AND EXCEEDING 9, GO TO
				CMP		DI,0		;OVERFLOW ROUTINE
				JE		OFLOW
				;ADD 1 TO NEXT VALUE - THIS IS THE CARRY
				MOV		CFLAG,1
			UNDER:
				MOV		BL,FIB2[DI] ;SAVE VALUE TO SWAP INTO FIB1
				MOV		FIB2[DI],AL	;SAVE OUR COMBINED VALUE INTO
				MOV		FIB1[DI],BL	;RESULT ARRAY
			;LOOP CHECK -- WHILE DI >= 0
			DEC		DI
			CMP		DI,0
			JGE		INNERLOOP
			
	LOOP	OUTERLOOP
	
REPORT:
	;FOR I = 0, I < 72, I++
	;PRINT FIB2[I]
	MOV		DI,0
	MOV		AH,0
	;TRIM NUMBER SEQUENCE
		TRIM:
		.IF FIB2[DI] == 0
			INC DI
			JMP TRIM
		.ENDIF
	;DIGITS USED = 72 - TRIM (DI)
	MOV		DX,72
	MOV		BX,DI
	SUB		DX,BX	;DX = DIGITS USED

	MOV		BH,0
	R_LOOP:
		MOV		AL,FIB2[DI]
		CALL	PUTDEC$
		INC		DI
		
	CMP		DI,72
	JL		R_LOOP
	;REPORT DIGITS USED
	CALL	NEWLINE
	LEA		DI,DIGITS
		MOV		CX,13
		CALL	PUTSTRNG
		
	MOV		AX,DX
	CALL	PUTDEC$
	
	JMP		DONE	
	
OFLOW:
	;CX CONTAINS WHAT ITERATION TRIGGERED OVERFLOW
	;FIND AMOUNT BY SUBTRACTING [INITIAL ENTRY - CX]
	MOV		AX,INPUT
	SUB		AX,CX
	INC		AX		;FIX OFF-BY-ONE ERROR
	LEA		DI,OVERFL
		MOV		CX,24
		CALL	PUTSTRNG
	;PRINT ITERATION COUNT	
	CALL	PUTDEC$
	LEA		DI,OVERF2
		MOV		CX,11
		CALL	PUTSTRNG

	CALL	NEWLINE
	JMP		REPORT
DONE:
	CALL	NEWLINE
	CALL	NEWLINE
	LEA		DI,NAME_IR
	MOV		CX,30
	CALL	PUTSTRNG
	CALL	NEWLINE
	LEA		DI,PAUMSG
	MOV		CX,30
	CALL PAUSE

	.EXIT
END STARTUP