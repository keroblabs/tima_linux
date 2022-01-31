;****************************************
; Mouse Slot Rom
;****************************************

		.org $00

		BIT	$FF58;			set V-Flag
		BVS	init
in:		SEC	;			Mouse-ID
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
		JSR	get_slot_data
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
get_slot_data:
		JSR	$FF58;			RTS
		TSX
		LDA	$0100,x
		TAX
		ASL
		ASL
		ASL
		ASL
		TAY
		RTS

;----------------------------------------
data_port       =       $C080
command_port    =       $C081

init_mouse_cmd  =       $02
serve_mouse_cmd =       $03
read_mouse_cmd  =       $04
clear_mouse_cmd =       $05
pos_mouse_cmd   =       $06
home_mouse_cmd  =       $07
set_mouse_cmd	=	$08
reset_index_cmd	=	$09
load_irq_cmd	=	$0A

read_data_mouse:
		PHA
		JSR	reset_data_port
		LDA	data_port,y
		STA 	$0478,x	
		LDA	data_port,y
		STA 	$04F8,x	
		LDA	data_port,y
		STA 	$0578,x	
		LDA	data_port,y
		STA 	$05F8,x	
		PLA
		RTS

write_data_mouse:
		PHA
		JSR	reset_data_port
		LDA	$0478,x
		STA 	data_port,y	
		LDA	$04F8,x
		STA 	data_port,y	
		LDA	$0578,x
		STA 	data_port,y	
		LDA	$05F8,x
		STA 	data_port,y	
		PLA
		RTS

reset_data_port:
		PHA
		LDA	#reset_index_cmd
		STA     command_port,y
		PLA
		RTS

read_status:
		PHA
		LDA 	data_port,y	
		STA	$0778,x
		PLA
		RTS

write_mode:
		JSR	reset_data_port
		STA	$07F8,x
		STA 	data_port,y	
		RTS

irq_status_to_c:
		PHA
		JSR	reset_data_port
		LDA	#load_irq_cmd
		STA     command_port,y
		LDA	data_port,y
		ASL
		PLA
		RTS

;----------------------------------------
servemouse:	
		PHA
		PHX
		PHY
		JSR	get_slot_data
		CLC
		JSR	irq_status_to_c
		BCC	serve2

		LDA	#serve_mouse_cmd
		STA	command_port,y
		JSR     reset_data_port
		JSR     read_status
		SEC
serve2:		
        	PLY
		PLX
		PLA
		RTS

;----------------------------------------
readmouse:	
		LDA	#read_mouse_cmd
		STA	command_port,y
read_data_2:
		JSR	read_data_mouse
		JSR     read_status
		RTS

;----------------------------------------
setmouse:	
		CMP	#$10
		BCS	error
		JSR     write_mode
		LDA	#set_mouse_cmd
		STA     command_port,y
		RTS

;----------------------------------------
clampmouse:	
		CMP	#$02
		BCS	error
		JSR	write_data_mouse
		STA	command_port,y
		RTS
;----------------------------------------
initmouse:	
		PHA
		LDA 	#init_mouse_cmd
		STA	command_port,y
		JSR 	read_data_2
		PLA
		RTS
;----------------------------------------
clearmouse:	
		PHA
		LDA	#clear_mouse_cmd
		STA	command_port,y
		JSR	read_data_mouse
		PLA
		RTS
;----------------------------------------
posmouse:	
		PHA
		JSR 	write_data_mouse
		LDA	#pos_mouse_cmd
send_command:
		STA	command_port,y
		PLA
		RTS
;----------------------------------------
homemouse:	
		PHA
		LDA	#home_mouse_cmd
		JMP     send_command
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

