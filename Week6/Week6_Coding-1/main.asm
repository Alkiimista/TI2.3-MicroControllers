;
; Week6_Coding-1.asm
;
; Created: 16/03/2017 11:03:45
; Author : Duc
;


; Replace with your application code
start:

	; Implementatie zonder loop.
	ldi R16, $55
	sts $540, R16	; Sets the content at $540 to $55
	sts $541, R16
	sts $542, R16
	sts $543, R16
	sts $544, R16
	sts $545, R16
	sts $546, R16
	sts $547, R16
	sts $548, R16
klaar:
	rjmp klaar