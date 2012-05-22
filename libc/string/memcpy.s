	.text
	.globl memcpy
:memcpy
	; same as memmove, but we don't care about forward/backward
	; A: dst
	; B: src
	; C: n
	; return: dst
	IFE C, 0
	SET PC, POP

	SET PUSH, I
	SET PUSH, J
	SET I, A
	SET J, B
	ADD B, C
:.loop
	STI [I], [J]
	IFN B, J
	SET PC, .loop

	SET J, POP
	SET I, POP
	SET PC, POP
