;====================================================================
;		DELAY PROGRAM
;=====================================================================
	.286
	.MODEL  SMALL,BASIC, FARSTACK

;===============================================================
;
; C O D E   S E G M E N T   D E F I N I T I O N
;
	.CODE
	
DELAY     PROC    FAR PUBLIC USES AX BX CX DX
	
	MOV		BX, 2
	MOV     AH,0
	INT     1AH			;GET INITIAL TIME
	ADD		BX, DX

	DELAYLOOP:
		NOP
		MOV     AH,0
		INT     1AH			;GET UPDATED TIME
		CMP		DX, BX		;CHECK IF DELAY IS COMPLETE
		JL		DELAYLOOP	;IF NOT, REPEAT

		RET
DELAY   ENDP
END