;****************************************
; Serial Slot Rom
;****************************************

			.org  $0

			BIT   $FF58
			BVS   p_C211
			SEC   
			.byte $90
			.byte $18
			CLV   
			BVC   p_C211
			ORA   ($31,X)
			STX   $9794
			TXS   

p_C211:
			STA   $27
			STX   $35
			TXA   
			PHA   
			TYA   
			PHA   
			PHP   
			SEI   
			STA   $CFFF
			JSR   $FF58
			TSX   
			LDA   $0100,X
			STA   $07F8
			TAX   
			ASL   
			ASL   
			ASL   
			ASL   
			STA   $26
			TAY   
			PLP   
			BVC   p_C25C
			ASL   $0538,X
			LSR   $0538,X
			LDA   $C08A,Y
			AND   #$1F
			BNE   p_C245
			LDA   #$EF
			JSR   $C805

p_C245:
			CPX   $37
			BNE   p_C254
			LDA   #$07
			CMP   $36
			BEQ   p_C254
			STA   $36
p_C251:
			CLC   
			BCC   p_C25C
p_C254:
			CPX   $39
			BNE   p_C251
			LDA   #$05
			STA   $38

p_C25C:
			LDA   $0738,X
			AND   #$02
			PHP   
			BCC   p_C267
			JMP   $C8BF

p_C267:
			LDA   $04B8,X
			PHA   
			ASL   
			BPL   p_C27C
			LDX   $35
			LDA   $27
			ORA   #$20
			STA   $0200,X
			STA   $27
			LDX   $07F8

p_C27C:
			PLA   
			AND   #$BF
			STA   $04B8,X
			PLP   
			BEQ   p_C28B
			JSR   $CB63
			JMP   $C8B5

p_C28B:
			JMP   $C8FC
			JSR   $C800
			LDX   #$00
			RTS   
			JMP   $C89B
			JMP   $C9AA
			LSR   
			JSR   $C99B
			BCS   p_C2A8
			JSR   $CAF5
			BEQ   p_C2AB
			CLC   
			BCC   p_C2AB

p_C2A8:
			JSR   $CAD2

p_C2AB:
			LDA   $05B8,X
			TAX   
			RTS   
			LDX   #$03

p_C2B2:
			LDA   $36,X
			PHA   
			DEX   
			BPL   p_C2B2
			LDX   $07F8
			LDA   $0638,X
			STA   $36
			LDA   $04B8,X
			AND   #$38
			LSR   
			LSR   
			LSR   
			ORA   #$C0

p_C2CA:
			STA   $37
			TXA   
			PHA   
			LDA   $27
			PHA   
			ORA   #$80
			JSR   $FDED
			PLA   
			STA   $27
			PLA   
			STA   $07F8
			TAX   
			ASL   
			ASL   
			ASL   
			ASL   
			STA   $26
			STA   $CFFF
			LDA   $36
			STA   $0638,X
			LDX   #$00

p_C2EE:
			PLA   
			STA   $36,X
			INX   
			CPX   #$04
			BCC   p_C2EE
			LDX   $07F8
			RTS   

			CMP   ($D0,X)
			BNE   p_C2CA
			CMP   $08
			
