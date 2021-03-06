           PAGE    80,132
;===================================================================
;                  PROGRAM BY IAN ROSNER
;
; PROGRAM TO MOVE A COW AROUND THE SCREEN
;===================================================================
                                       ;PROCEDURES TO
           EXTRN   CLEAR:FAR           ;CLEAR VIDEO SCREEN
           EXTRN   DELAY:FAR           ;DELAY n SECONDS
           EXTRN   PUTSHAPE:FAR        ;DISPLAY A TEXTUAL SHAPE
		   EXTRN   PAUSE:FAR
		   EXTRN   RANDOM:FAR
;===================================================================
           .MODEL  LARGE,BASIC
;===================================================================
; S T A C K   S E G M E N T   D E F I N I T I O N
;
           .STACK  256
;===================================================================
; D A T A   S E G M E N T   D E F I N I T I O N
           .DATA
COWV1	 DW		0	;TRACK WHERE OUR COW IS
COWV2	 DB		0
COWV3	 DB		0
TEMPV1	 DB		0
TEMPV2	 DB		0
LOWER	 DW     0
UPPER    DW     10

NAME_IR  DB 	1,21
		 DB		'P R O G R A M   B Y   I A N   R O S N E R '

		   
COW 	 DB 	7, 15
		 DB 	20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 28H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 29H,2FH
		 DB 	20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 28H,2FH, 6fH,2FH, 6fH,2FH, 29H,2FH, 20H,2FH
		 DB 	20H,2FH, 29H,2FH, 5cH,2FH, 2eH,2FH, 2dH,2FH, 2dH,2FH, 2dH,2FH, 2dH,2FH, 2dH,2FH, 2fH,2FH, 28H,2FH, 4fH,2FH, 20H,2FH, 4fH,2FH, 29H,2FH
		 DB 	23H,2FH, 20H,2FH, 3bH,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 2fH,2FH, 20H,2FH, 75H,2FH, 20H,2FH, 20H,2FH
		 DB 	20H,2FH, 20H,2FH, 28H,2FH, 20H,2FH, 20H,2FH, 2eH,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 7cH,2FH, 7dH,2FH, 20H,2FH, 29H,2FH, 20H,2FH, 20H,2FH
		 DB 	20H,2FH, 20H,2FH, 20H,2FH, 7cH,2FH, 2fH,2FH, 20H,2FH, 60H,2FH, 2eH,2FH, 3bH,2FH, 7cH,2FH, 2fH,2FH, 3bH,2FH, 20H,2FH, 20H,2FH, 20H,2FH
		 DB 	20H,2FH, 20H,2FH, 20H,2FH, 22H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 22H,2FH, 20H,2FH, 22H,2FH, 20H,2FH, 20H,2FH, 20H,2FH

COW2 	 DB 	7, 15
		 DB 	28H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 29H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH
		 DB 	20H,2FH, 28H,2FH, 6fH,2FH, 6fH,2FH, 29H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH
		 DB 	28H,2FH, 4fH,2FH, 20H,2FH, 4fH,2FH, 29H,2FH, 5cH,2FH, 2dH,2FH, 2dH,2FH, 2dH,2FH, 2dH,2FH, 2dH,2FH, 2eH,2FH, 2fH,2FH, 28H,2FH, 20H,2FH
		 DB 	20H,2FH, 20H,2FH, 75H,2FH, 20H,2FH, 5cH,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 3bH,2FH, 20H,2FH, 23H,2FH
		 DB 	20H,2FH, 20H,2FH, 28H,2FH, 20H,2FH, 7bH,2FH, 7cH,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 2eH,2FH, 20H,2FH, 20H,2FH, 29H,2FH, 20H,2FH, 20H,2FH
		 DB 	20H,2FH, 20H,2FH, 20H,2FH, 3bH,2FH, 5cH,2FH, 7cH,2FH, 3bH,2FH, 20H,2FH, 2cH,2FH, 20H,2FH, 5cH,2FH, 7cH,2FH, 20H,2FH, 20H,2FH, 20H,2FH
		 DB 	20H,2FH, 20H,2FH, 20H,2FH, 22H,2FH, 20H,2FH, 22H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 20H,2FH, 22H,2FH, 20H,2FH, 20H,2FH, 20H,2FH
		 
COW3 	 DB 	7, 15
		 DB 	28H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 29H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH
		 DB 	20H,3FH, 28H,3FH, 6fH,3FH, 6fH,3FH, 29H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH
		 DB 	28H,3FH, 4fH,3FH, 20H,3FH, 4fH,3FH, 29H,3FH, 5cH,3FH, 2dH,3FH, 2dH,3FH, 2dH,3FH, 2dH,3FH, 2dH,3FH, 2eH,3FH, 2fH,3FH, 28H,3FH, 20H,3FH
		 DB 	20H,3FH, 20H,3FH, 75H,3FH, 20H,3FH, 5cH,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 3bH,3FH, 20H,3FH, 23H,3FH
		 DB 	20H,3FH, 20H,3FH, 28H,3FH, 20H,3FH, 7bH,3FH, 7cH,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 2eH,3FH, 20H,3FH, 20H,3FH, 29H,3FH, 20H,3FH, 20H,3FH
		 DB 	20H,3FH, 20H,3FH, 20H,3FH, 3bH,3FH, 5cH,3FH, 7cH,3FH, 3bH,3FH, 20H,3FH, 2cH,3FH, 20H,3FH, 5cH,3FH, 7cH,3FH, 20H,3FH, 20H,3FH, 20H,3FH
		 DB 	20H,3FH, 20H,3FH, 20H,3FH, 22H,3FH, 20H,3FH, 22H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 20H,3FH, 22H,3FH, 20H,3FH, 20H,3FH, 20H,3FH
		 
COW4 	 DB 	7, 15
		 DB 	28H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 29H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH
		 DB 	20H,0FH, 28H,0FH, 6fH,0FH, 6fH,0FH, 29H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH
		 DB 	28H,0FH, 4fH,0FH, 20H,0FH, 4fH,0FH, 29H,0FH, 5cH,0FH, 2dH,0FH, 2dH,0FH, 2dH,0FH, 2dH,0FH, 2dH,0FH, 2eH,0FH, 2fH,0FH, 28H,0FH, 20H,0FH
		 DB 	20H,0FH, 20H,0FH, 75H,0FH, 20H,0FH, 5cH,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 3bH,0FH, 20H,0FH, 23H,0FH
		 DB 	20H,0FH, 20H,0FH, 28H,0FH, 20H,0FH, 7bH,0FH, 7cH,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 2eH,0FH, 20H,0FH, 20H,0FH, 29H,0FH, 20H,0FH, 20H,0FH
		 DB 	20H,0FH, 20H,0FH, 20H,0FH, 3bH,0FH, 5cH,0FH, 7cH,0FH, 3bH,0FH, 20H,0FH, 2cH,0FH, 20H,0FH, 5cH,0FH, 7cH,0FH, 20H,0FH, 20H,0FH, 20H,0FH
		 DB 	20H,0FH, 20H,0FH, 20H,0FH, 22H,0FH, 20H,0FH, 22H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 20H,0FH, 22H,0FH, 20H,0FH, 20H,0FH, 20H,0FH
		 
UFO 	 DB 	4, 23
		 DB 	20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 2fH,07H, 2fH,07H, 2dH,07H, 41H,07H, 2dH,07H, 5cH,07H, 5cH,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H
		 DB 	20H,07H, 20H,07H, 5fH,07H, 5fH,07H, 5fH,07H, 2dH,07H, 2dH,07H, 2dH,07H, 3dH,07H, 3dH,07H, 3dH,07H, 3dH,07H, 3dH,07H, 3dH,07H, 3dH,07H, 2dH,07H, 2dH,07H, 2dH,07H, 5fH,07H, 5fH,07H, 5fH,07H, 20H,07H, 20H,07H
		 DB 	28H,07H, 3dH,07H, 5fH,07H, 5fH,07H, 5cH,07H, 20H,07H, 20H,07H, 20H,07H, 2fH,07H, 2eH,07H, 2eH,07H, 20H,07H, 2eH,07H, 2eH,07H, 5cH,07H, 20H,07H, 20H,07H, 20H,07H, 2fH,07H, 5fH,07H, 5fH,07H, 3dH,07H, 29H,07H
		 DB 	20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 2dH,07H, 2dH,07H, 2dH,07H, 5cH,07H, 5fH,07H, 5fH,07H, 4fH,07H, 5fH,07H, 5fH,07H, 2fH,07H, 2dH,07H, 2dH,07H, 2dH,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H
		 
BEAM 	 DB 	17, 19
		 DB 	20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 2FH,3EH, 20H,3EH, 5CH,3EH, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H
		 DB 	20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 2fH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 5cH,3EH, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H
		 DB 	20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 2fH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 5cH,3EH, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H
		 DB 	20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 2fH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 5cH,3EH, 20H,07H, 20H,07H, 20H,07H, 20H,07H, 20H,07H
		 DB 	20H,07H, 20H,07H, 20H,07H, 20H,07H, 2fH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 5cH,3EH, 20H,07H, 20H,07H, 20H,07H, 20H,07H
		 DB 	20H,07H, 20H,07H, 20H,07H, 2fH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 5cH,3EH, 20H,07H, 20H,07H, 20H,07H
		 DB 	20H,07H, 20H,07H, 2fH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 5cH,3EH, 20H,07H, 20H,07H
		 DB 	20H,07H, 2fH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 5cH,3EH, 20H,07H
		 DB 	2aH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 2aH,3EH
		 DB 	7cH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 7cH,3EH
		 DB 	7cH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 7cH,3EH
		 DB 	7cH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 7cH,3EH
		 DB 	7cH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 7cH,3EH
		 DB 	7cH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 7cH,3EH
		 DB 	7cH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 7cH,3EH
		 DB 	7cH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 7cH,3EH
		 DB 	7cH,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 20H,3EH, 7cH,3EH




SKY		DB		12,80
		DB		12*80 DUP(' ',0FH)
		
GRASS	DB		13,80
		DB		13*80 DUP(' ',2FH)

;===================================================================
; C O D E   S E G M E N T   D E F I N I T I O N
;PUTSHAPE -- DL HORIZONTAL DH VERTICAL
;			 BH PAGE NUMBER
;SCREEN IS 80 X 25 [HORIZONTAL X VERTICAL]
           .CODE   EX_13_6
           .STARTUP                     ;GENERATE STARTUP CODE
;
		MOV     AH,15                ;GET PG <ACTIVE PAGE NO.>
		INT     10H
		
		MOV		DL,1
		MOV		DH,1
		LEA     SI,SKY
		CALL    PUTSHAPE             ;CALL PUTSHAPE(SPTR,PG,I,J)
		
		MOV		DH,13
		LEA		SI,GRASS
		CALL	PUTSHAPE
		
		LEA     SI,COW           	;SPTR = ADDRESS OF FACE
		MOV     DH,15                 ;I = 3
		MOV     DL,25                ;J = 18
		MOV     AL,1
		MOV     CX,12                ;LOOP_CNT = 12
		
			;COW ANIMATION LOOP 1
		
			.REPEAT                      ;REPEAT
			CALL    CLEAR                ;   CLEAR SCREEN
			;GIVE A 30% CHANCE THAT THE COW GOES UP
				PUSH	LOWER
				PUSH	UPPER
				CALL	RANDOM
				MOV AH,0
				.IF AX > 7
					DEC DH
					INC COWV1
				.ENDIF
			;END COW UP
			INC     DL                   ;   J = J + 1
			LEA		SI,COW
			CALL    PUTSHAPE             ;   CALL PUTSHAPE(SPTR,PG,I,J)
			MOV		AL,1
			CALL    DELAY                ;   DELAY 1 SECOND
			.UNTILCXZ                    ;   LOOP_CNT = LOOP_CNT - 1
										 ;UNTIL LOOP_CNT = 0
										 
		MOV		COWV2,DH
		MOV		COWV3,DL
		
		MOV		DL,1
		MOV		DH,1
		LEA     SI,SKY
		CALL    PUTSHAPE             ;CALL PUTSHAPE(SPTR,PG,I,J)
		
		MOV		DH,13
		LEA		SI,GRASS
		CALL	PUTSHAPE
		
		MOV		AL,15
	DELAYLOOP2:
		CALL	DELAY
		DEC		AL
		CMP		AL,0
		JL		DELAYLOOP2
		
		MOV		CX,15
		MOV		DL,5
		MOV		DH,1
			;COW ANIMATION LOOP 2
			;ENTER SCENE - UFO
			.REPEAT
			PUSH	DX
			MOV		DH,COWV2
			MOV		DL,COWV3
			CALL	CLEAR
				;MOV THAT COW BACK DOWN!
				.IF COWV1 > 0
					INC DH
					DEC COWV1
				.ENDIF
			DEC		DL
			LEA		SI,COW2
			CALL	PUTSHAPE
			MOV		COWV2,DH
			MOV		COWV3,DL
			
			POP		DX
			LEA		SI,UFO
			CALL	PUTSHAPE
			INC		DL
			MOV		AL,1
			CALL	DELAY
			.UNTILCXZ
			
		MOV		TEMPV1,DH			;STORING WHERE THINGS ARE ...
		MOV		TEMPV2,DL
			
		MOV		DL,1
		MOV		DH,1
		LEA     SI,SKY
		CALL    PUTSHAPE             ;CALL PUTSHAPE(SPTR,PG,I,J)
		
		MOV		DH,13
		LEA		SI,GRASS
		CALL	PUTSHAPE
			
			
		MOV		CX,10
			;BEAM TIME
			.REPEAT
			CALL	CLEAR
			MOV		DH,TEMPV1
			MOV		DL,TEMPV2
			LEA		SI,UFO			;PRINT UFO
			CALL	PUTSHAPE
			
			MOV		DL,21
			MOV		DH,5
			LEA		SI,BEAM			;BIG BEAM
			CALL	PUTSHAPE
			
			MOV		DH,COWV2		;DRAW COW OVER BEAM
			MOV		DL,COWV3
			LEA		SI,COW3
			CALL	PUTSHAPE
			DEC		COWV2
			CALL	DELAY
			.UNTILCXZ
			
		MOV		DL,1
		MOV		DH,1
		LEA     SI,SKY
		CALL    PUTSHAPE             ;CALL PUTSHAPE(SPTR,PG,I,J)
		
		MOV		DH,13
		LEA		SI,GRASS
		CALL	PUTSHAPE
			
		MOV		CX,45
			;EXIT STAGE RIGHT
			.REPEAT
			CALL	CLEAR
			MOV		DH,TEMPV1
			MOV		DL,TEMPV2
			INC		TEMPV2
			LEA		SI,UFO			;PRINT UFO
			CALL	PUTSHAPE
			
			MOV		DH,COWV2		;DRAW COW OVER BEAM
			MOV		DL,COWV3
			LEA		SI,COW4
			CALL	PUTSHAPE
			INC		COWV3
			CALL	DELAY
			.UNTILCXZ
			
		MOV		DH,13
		MOV		DL,1
		LEA		SI,GRASS
		CALL	PUTSHAPE
		
	MOV		DL,1
	MOV		DH,1
	LEA		SI,COW
	MOV		CX,27
		.REPEAT						;COW SCREEN TRANSITION
		MOV		DH,1
		CALL	CLEAR
		CALL	PUTSHAPE
		ADD		DH,7
		CALL	PUTSHAPE
		ADD		DH,7
		CALL	PUTSHAPE
		ADD		DH,7
		CALL	PUTSHAPE
		ADD		DL,7
		CALL	DELAY
		.UNTILCXZ

		LEA		SI,NAME_IR			;PRINT NAME
		MOV		DL,10
		MOV		DH,10
		CALL	PUTSHAPE
		
		
		;ADD     DH,4                 ;I = I + 4
		;LEA     SI,COW         ;SPTR = ADDRESS OF SAD_MOUTH
		;CALL    PUTSHAPE             ;CALL PUTSHAPE(SPTR,PG,I,J)
		;MOV     AL,5                 ;DELAY 5 SECONDS
		;CALL    DELAY
		.EXIT                        ;RETURN TO DOS
;
;===================================================================
		END