;==============================
;	parity finder
;
;	returns # of 1 bits
;		in a value
;	    input - AX
;	   output - CX
;==============================
	.MODEL	SMALL,BASIC
;==============================
;DATA SEG
.FARDATA PARDATA
PARCT	DW	0
LOOPCT	DW	?
;==============================
	.CODE	PAR
	ASSUME	DS:PARDATA
PARITY	PROC	FAR PUBLIC USES AX DS
	PUSHF
	PUSH	AX	
	MOV		AX,SEG PARDATA		;SET ES TO POINT TO DATA SEG
	MOV		DS,AX
	POP		AX
	
	MOV	LOOPCT,16	;INITIALIZE COUNTER - AX == 16 BIT REG
PAR_LOOP:
	SHR		AX,1	;SHIFT RIGHTMOST INTO CARRY
	JNC		SKIP
	INC		PARCT	;IF CARRY SET, INC PARITY CT
SKIP:
	DEC		LOOPCT
	CMP		LOOPCT,0
	JNE		PAR_LOOP
FINISH:
	MOV		CX,PARCT	;PARCT RETURNED IN CX
	
	POPF
	RET
PARITY	ENDP
END