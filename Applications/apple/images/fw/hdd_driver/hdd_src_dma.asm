		.org $C000
		
		; disc id
		LDX   #$20
		LDY   #$00
		LDX   #$03
		STX   $3C
		
		; detect slot
		JSR   $FF58
		TSX   
		LDA   $0100,X
		ASL   
		ASL   
		ASL   
		ASL   
		STA   $2B
		TAX   
		
		; (instant boot)
		STA   $C08C,X
		JMP   $0801
		
entry_point:
		LDA   $43
		AND   #$70
		TAX   
		
		; execute mli
		STA   $C08D,X
		LDA   #$00
		CLC   
		RTS   
		
;****************************************
		
		.org	$C0FC
		
		.word	$00
		.byte 	$7F
		.byte	entry_point & $ff
		
