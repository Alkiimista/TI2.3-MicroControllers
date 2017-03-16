;
; Week6_Coding-2.asm
;
; Created: 16/03/2017 11:45:22
; Author : Duc
;


; Replace with your application code
start:
	ldi xh, $60
	ldi xl, 00
	ldi yh, $70
	ldi yl, 00
	ldi R16, 10	;Counter for the loop, should loop 10 times.

loop:
	ld R8, x+
	inc R8
	st y+, R8
	cp xl, R16
	brne loop	; Branch if it's not 0

end:			; infinite loop
	rjmp end