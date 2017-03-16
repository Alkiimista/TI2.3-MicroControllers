;
; Week6_Coding-3.asm
;
; Created: 16-Mar-17 12:10:20
; Author : Nick
;


start:
	ldi xh, $60
	ldi xl, 00
	ldi yh, $80
	ldi yl, 00
	ldi R16, 10	;Counter for the loop, should loop 10 times.

loop:

	mov yh, xh

	ld R8, x+
	ld R9, y+
	inc R8
	inc R9
	
	cp xl, R16
	brne loop	; Branch if it's not 0

end:			; infinite loop
	rjmp end