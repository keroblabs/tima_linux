;****************************************
; Mouse Slot Rom
;****************************************

		.org $00

		BIT	$FF58;			set V-Flag
		BVS	init
in:		SEC	;				Mouse-ID
		BCC	init;			Mouse-ID
		CLV	
		BVC	init

		.byt	$01;			$cx0b		Mouse-ID
		.byt	$20;			$cx0c		Mouse-ID

		.byt	undef & $ff
		.byt	undef & $ff
		.byt	undef & $ff
		.byt	undef & $ff
		.byt	$00

jumplist:	
		.byt	setmouse   & $ff;		$cx12
		.byt	servemouse & $ff;		$cx13
		.byt	readmouse  & $ff;		$cx14
		.byt	clearmouse & $ff;		$cx15
		.byt	posmouse   & $ff;		$cx16
		.byt	clampmouse & $ff;		$cx17
		.byt	homemouse  & $ff;		$cx18
		.byt	initmouse  & $ff;		$cx19
		.byt	undef      & $ff
		.byt	undef      & $ff
		.byt	undef      & $ff
		.byt	undef      & $ff
		.byt	undef      & $ff
		.byt	undef      & $ff

init:		
		PHY
		PHX
		PHA
		PHP
		SEI
		JSR	$FF58;			RTS
		TSX
		LDA	$0100,x
		TAX
		ASL
		ASL
		ASL
		ASL
		TAY
		PLP
		BVC	cinorcout;		call second time?
		LDA	$38;			KSWL (IN-vector low)
		BNE	cout
		TXA
		EOR	$39
		BNE	cout
		LDA	#$05
		STA	$38;			KSWL (IN-vector low)
		BNE	cin

cinorcout:	
		BCS	cin;			in/out?
cout:		
		PLA
		PHA
		STA	$C080,y;		send character
		PLA
		PLX
		PLY
		RTS

cin:		
		STA	$C081,y;		command in
		PLA
		LDA	$0638,x;		read index to $200
		TAX
		PLA
		LDA	$0200,x
		PLY
		RTS
;----------------------------------------
setmouse:	
		CMP	#$10
		BCS	error
		STA	$C082,y;		set mode
		RTS
;----------------------------------------
servemouse:
        PHA
        PHX
        PHY
        LDA $C063
        TAX
        ASL
        ASL
        ASL
        ASL
        TAY
        CLC
        LDA #$03
        STA $C083,y;        send command
        LDA $0778,x;        read status byte
        AND #$0E;           mask interrupt bits
        BNE serve2
        SEC
serve2:
        PLY
        PLX
        PLA
        RTS
;----------------------------------------
clampmouse:
        CMP	#$02
		BCS	error
		STA	$C083,y
		RTS
;----------------------------------------
readmouse:
        LDA	#$04
		STA	$C083,y;		send command
		LDA	$0778,x;		read status byte
		RTS
;----------------------------------------
initmouse:	
		PHA
		LDA	#$02
sendcommand:	
		STA	$C083,y
		PLA
		RTS
;----------------------------------------
clearmouse:	
		PHA
		LDA	#$05
		BNE	sendcommand;		jump always
;----------------------------------------
posmouse:	
		PHA
		LDA	#$06
		BNE	sendcommand;		jump always
;----------------------------------------
homemouse:	
		PHA
		LDA	#$07
		BNE	sendcommand;		jump always
;----------------------------------------
undef:		
		LDX	#$03
error:		
		SEC
		RTS
;----------------------------------------
		.org 	$fb
		.byt	$d6;			Mouse ID
		
		.org 	$ff
		.byt	$01;			Mouse ID

