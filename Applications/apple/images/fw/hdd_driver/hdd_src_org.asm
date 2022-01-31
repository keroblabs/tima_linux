		.org $c700
		
		; disc id
		LDX   #$20
		LDY   #$00
		LDX   #$03
		STX   $3C
		
;-------------------------------------------
; detect slot
;-------------------------------------------
		JSR   $FF58
		TSX   
		LDA   $0100,X
		ASL   
		ASL   
		ASL   
		ASL   
		STA   $2B
		TAX   
		
;-------------------------------------------
; instant boot
;-------------------------------------------
		LDA   #$00
		STA   $44
		STA   $46
		STA   $47
		LDA   #$01
		STA   $42
		LDA   #$08
		STA   $45
		TXA
		STA   $43
		JSR   entry_point
		JMP   $0801
		
;-------------------------------------------
; Load MLI command to FIFO
;-------------------------------------------
load_cmd_to_fifo:
		STA   $C080,X 			; reset FIFO
		LDY   #$00
load_02:
		LDA   $42,Y
		STA   $C082,X
		INY
		CPY   #$06
		BNE   load_02
		RTS

;-------------------------------------------
; Wait for driver response
;-------------------------------------------
exec_command:
		STA   $C083,X 			; start command
wait_driver_01:
		LDA   $C084,X           ; check for complete
		BMI   wait_driver_01
		RTS

;-------------------------------------------
; load block data to fifo
;-------------------------------------------
write_fifo_block:
		LDA   $44
		STA   $3A
		LDA   $45
		STA   $3B
		LDY   #$00

write_loop_01:
		LDA   ($3A),Y
		STA   $C082,X
		INY
		BNE   write_loop_01
		INC   $3B
write_loop_02:
		LDA   ($3A),Y
		STA   $C082,X
		INY
		BNE   write_loop_02
		RTS

;-------------------------------------------
; get block data from fifo
;-------------------------------------------
read_fifo_block:
		LDA   $44
		STA   $3A
		LDA   $45
		STA   $3B
		LDY   #$00

read_loop_01:
		LDA   $C081,X
		STA   ($3A),Y
		INY
		BNE   read_loop_01
		INC   $3B
read_loop_02:
		LDA   $C081,X
		STA   ($3A),Y
		INY
		BNE   read_loop_02
		RTS

;-------------------------------------------
; MLI entry point
;-------------------------------------------
entry_point:
		LDA   $43
		AND   #$70
		TAX   

		JSR   load_cmd_to_fifo
		
		LDA   $42				; select command
		CMP   #$00
		BEQ   get_status
		
		CMP   #$01
		BEQ   read_block
		
		CMP   #$02
		BEQ   write_block
		
		CMP   #$03
		BEQ   format_unit
		
		; unknown command
_exit_io_error:		
		LDA   #$27
		SEC   
		RTS   
		
		; no error
_exit_no_error:		
		LDA   #$00
		CLC   
		RTS   
		
get_status:		
		JSR   exec_command
		LDA   $C081,X
		TAX   
		LDA   $C081,X
		TAY   
		CLC   
		BCC   _exit_no_error
		
read_block:
		JSR   exec_command
		JSR   read_fifo_block
		LDA   #$00
		CLC   
		RTS   
		
write_block:
		JSR   write_fifo_block
		JSR   exec_command
		LDA   #$00
		CLC   
		RTS   
		
format_unit:
		JSR   exec_command
		LDA   #$00
		CLC   
		RTS   
		
;****************************************
		
		.org	$C7FC
		
		.word	$00
		.byte 	$7F
		.byte	entry_point & $ff
		