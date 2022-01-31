;****************************************

		.org $C000

COMMAND_GET_SIZE			=   $01
COMMAND_SET_BLOCK_NUM		=   $02
COMMAND_READ_BLOCK			=   $03
COMMAND_WRITE_BLOCK			=   $04
COMMAND_CLEAR_BLOCK			=   $05
COMMAND_READ_BLOCK_00		=   $06
COMMAND_RESET_FIFO			=   $07

IO_LATCH_WRITE				=   $C080
IO_WRITE_TRIGGER			=   $C081
IO_LATCH_READ				=   $C082
IO_READ_DONE				=   $C083
IO_LATCH_CMD_DONE			=   $C084
IO_LATCH_WRITE_DONE			=   $C085
IO_LATCH_READ_PENDING		=   $C086
IO_COMMAND					=   $C087
		
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

		LDA   $CFFF				; clear IOSTB

		LDA   #$00
		STA   $44
		LDA   #$08
		STA   $45

		TXA
		ORA   #COMMAND_READ_BLOCK_00
		JSR   send_command

		JSR   read_fifo_block

		LDA   #COMMAND_RESET_FIFO		; reset FIFO
		JSR   send_command

		JMP   $0801

;-------------------------------------------
; MLI entry point
;-------------------------------------------
entry_point:
		LDA   $CFFF				; clear IOSTB

		LDA   $43
		AND   #$70
		TAX   
		
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
		TXA
		ORA   #COMMAND_GET_SIZE
		JSR   send_command

		JSR   get_byte_fifo
		TAX   
		JSR   get_byte_fifo
		TAY   
		CLC   
		BCC   _exit_no_error
		
read_block:
		JSR   send_block_num

		TXA
		ORA   #COMMAND_READ_BLOCK
		JSR   send_command

		JSR   read_fifo_block
		CLC   
		BCC   _exit_no_error
		
write_block:
		JSR   send_block_num
		JSR   write_fifo_block

		TXA
		ORA   #COMMAND_WRITE_BLOCK
		JSR   send_command

		CLC   
		BCC   _exit_no_error
		
format_unit:
		TXA
		ORA   #COMMAND_CLEAR_BLOCK
		JSR   send_command

		CLC   
		BCC   _exit_no_error
		
;****************************************
		
		.org	$C0FC
		
		.word	$00
		.byte 	$7F
		.byte	entry_point & $ff
		
;****************************************

		.org	$C800

;-------------------------------------------
; send command to device
;-------------------------------------------
send_command:
		STA   IO_COMMAND,X

send_command_loop:
		LDA   IO_LATCH_CMD_DONE,X
		BMI   send_command_loop
		RTS

;-------------------------------------------
; send byte to FIFO
;-------------------------------------------
send_byte_fifo:
		STA   IO_LATCH_WRITE,X
		STA   IO_WRITE_TRIGGER,X

send_byte_loop:
		LDA   IO_LATCH_WRITE_DONE,X
		BMI   send_byte_loop
		RTS

;-------------------------------------------
; get byte from FIFO
;-------------------------------------------
get_byte_fifo:
		LDA   IO_LATCH_READ_PENDING,X
		BPL   get_byte_fifo

		LDA   IO_LATCH_READ,X
		STA   IO_READ_DONE,X
		RTS

;-------------------------------------------
; load block data to fifo
;-------------------------------------------
write_fifo_block:
		LDA   #COMMAND_RESET_FIFO		; reset FIFO
		JSR   send_command

		LDA   $44						; get block address
		STA   $3A
		LDA   $45
		STA   $3B

		LDY   #$00

write_loop_01:							; loop first 256
		LDA   ($3A),Y
		JSR   send_byte_fifo
		INY
		BNE   write_loop_01
		INC   $3B

write_loop_02:							; loop next 256
		LDA   ($3A),Y
		JSR   send_byte_fifo
		INY
		BNE   write_loop_02
		RTS

;-------------------------------------------
; get block data from fifo
;-------------------------------------------
read_fifo_block:
		LDA   $44						; get block address
		STA   $3A
		LDA   $45
		STA   $3B

		LDY   #$00

read_loop_01:
		JSR   get_byte_fifo
		STA   ($3A),Y
		INY
		BNE   read_loop_01
		INC   $3B

read_loop_02:
		JSR   get_byte_fifo
		STA   ($3A),Y
		INY
		BNE   read_loop_02
		RTS

;-------------------------------------------
; send block num to device
;-------------------------------------------
send_block_num:
		LDA   #COMMAND_RESET_FIFO
		JSR   send_command

		LDA   $46
		JSR   send_byte_fifo
		LDA   $47
		JSR   send_byte_fifo

		LDA   #COMMAND_SET_BLOCK_NUM
		JSR   send_command
		RTS

