;****************************************
; Printer Slot Rom
;****************************************

		.org $00

; $24 = horizontal cursor position

		CLC
		.byt	$b0;		= BCS (Printer-ID)
		SEC
		PHA
		TXA
		PHA
		TYA
		PHA
		PHP
		SEI
		JSR	$FF58;		--> RTS
		TSX
		PLA
		PLA
		PLA
		PLA
		TAY	;		Y = A
		DEX	;		decrement one more
		TXS
		PLA	;		get highbyte of return address
		PLP
		TAX
		BCC	p_2052

		LDA	$05B8,x;	special printer command activated?
		BPL	p_2038
		TYA
		AND	#$7F
		EOR	#$30
		CMP	#$0A
		BCC	p_2063
		CMP	#$78
		BCS	p_2055
		EOR	#$3D;		return?
		BEQ	p_2051
		TYA
		AND	#$9F
		STA	$0638,x
		BCC	p_20b6;		jump always
;----------------------------------------
p_2038:		LDA	$06B8,x
p_203b:		BMI	p_2051

		LDA	$24;		cursorx
		CMP	$0738,x
		BCS	p_2051
		CMP	#$11
		BCS	p_2051
		ORA	#$F0
		AND	$0738,x
		ADC	$24;		cursorx
		STA	$24;		cursorx
p_2051:		LSR	;		clear N flag (for further jump)
p_2052:		SEC
		BCS	p_20c2;		jump always
;----------------------------------------
p_2055:		CLC
		ROR
		AND	$06B8,x
		BCC	p_205e
		EOR	#$81
p_205e:		STA	$06B8,x
		BNE	p_20b6;		==> clear special command flag and exit
;----------------------------------------
p_2063:		LDY	#$0A
p_2065:		ADC	$0538,x
		DEY
		BNE	p_2065
		STA	$04B8,x
p_206e:		STA	$0538,x
		SEC
		BCS	p_20b7;		jump always ==> set special printer command flag and exit
;----------------------------------------
p_2074:		CMP	$24;		cursorx
		BCC	p_20b2
		PLA
		TAY
		PLA
		TAX
		PLA
		JMP	$FDF0;		Cout1
;----------------------------------------
p_2080:		BCC	p_2080
p_2082:		BCS	p_2082
;----------------------------------------
p_2084:		STA	$C080,y
		BCC	p_20c0

		EOR	#$07
		TAY
		EOR	#$0A
		ASL
		BNE	p_2097
		CLV
		STA	$24;		cursorx
		STA	$0738,x
p_2097:		LDA	$06B8,x
		LSR	;		clear N-Flag
		BVS	p_209f
		BCS	p_20c2
p_209f:		ASL
		ASL
		LDA	#$27
		BCS	p_2074
		LDA	$0738,x
		SBC	$04B8,x
		CMP	#$F8
		BCC	p_20b2
		ADC	#$27;		+ 40
		.byt	$ac;		LDY abs (dummy instruction)
p_20b2:		LDA	#0
		STA	$24;		cursorx
p_20b6:		CLC
p_20b7:		ROR	$05B8,x;	clear/set special printer command flag
		PLA
		TAY
		PLA
		TAX
		PLA
		RTS
;----------------------------------------
p_20c0:		BCC	p_20e9
p_20c2:		BCS	p_20c4
p_20c4:		BPL	p_20d7
		LDA	#$89;		reset parameters
		STA	$0638,x
		STA	$06B8,x
		LDA	#$28
		STA	$04B8,x
		LDA	#$02
		STA	$36;		CWSL (char out vector low)
p_20d7:		TYA
		EOR	$0638,x
		ASL
		BEQ	p_206e
		LSR	$05B8,x;	clear special printer command flag
		TYA
		PHA
		TXA
		ASL
		ASL
		ASL
		ASL
		TAY
p_20e9:		LDA	$0738,x
		CMP	$24;		cursorx
		PLA
		BCS	p_20f6
		PHA
		AND	#$80
		ORA	#$20
p_20f6:		BIT	$FF58;		#60
		BEQ	p_20fe
		INC	$0738,x
p_20fe:		BVS	p_2084;		==> print


