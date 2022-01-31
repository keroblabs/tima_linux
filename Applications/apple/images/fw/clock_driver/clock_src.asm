;****************************************
; Clock Slot Rom
;****************************************
;
;input buffer ($200):
;
;mo,da,dt,hr,mn
;
;where
;
;mo is the month (01 = January...12 = December)
;da is the day of the week (00 = Sunday...06 = Saturday)
;dt is the date (00 through 31)
;hr is the hour (00 through 23)
;mn is the minute (00 through 59)
;
;return example:
;
;07,04,14,22,46
;Thursday, July 14, 10:46 p.m.
;
;ROM:
;
;$Cn00 = $08
;$Cn02 = $28
;$Cn04 = $58
;$Cn06 = $70
;
;$Cn08 = READ entry point
;$Cn0B = WRITE entry point
;
;The accumulator is loaded with an #$A3 before the JSR to the WRITE entry point
;
;
;0xC0n0: save buffer
;0xC0n1: load buffer
;0xC0n2: write bytes (zero terminated)
;0xC0n3: read bytes (zero terminated)

;****************************************

		.org $00
		
		PHP   
		LDX   #$28
		LDX   #$58
		LDX   #$70
		PLP   
		CLC   
		BCC   p_C40E
		CLC   
		BCC   p_C448
		
p_C40E:
		PHA   
		JSR   $FF58
		TSX   
		LDA   $0100,X
		ASL   
		ASL   
		ASL   
		ASL   
		STA   $2B
		TAX   
		PLA   
		STA   $C081,X
		LDA   $40
		PHA   
		LDA   $41
		PHA   
		LDA   #$00
		STA   $40
		LDA   #$02
		STA   $41
		LDY   #$00
		
p_C431:
		LDA   $C083,X
		CMP   #$00
		BEQ   p_C43D
		STA   ($40),Y
		INY   
		BNE   p_C431
		
p_C43D:
		LDA   #$00
		STA   ($40),Y
		PLA   
		STA   $41
		PLA   
		STA   $40
		RTS   
		
p_C448:
		PHA   
		JSR   $FF58
		TSX   
		LDA   $0100,X
		ASL   
		ASL   
		ASL   
		ASL   
		STA   $2B
		TAX   
		PLA   
		STA   $C080,X
		RTS   

;****************************************
		.org $ff
		.byte $0