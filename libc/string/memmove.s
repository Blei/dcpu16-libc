	.text
	.globl memmove
:memmove
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

	IFG A, B
	SET PC, .backwards
	ADD B, C
:.loop
	STI [I], [J]
	IFN B, J
	SET PC, .loop

	SET J, POP
	SET I, POP
	SET PC, POP

:.backwards
	; start from the end
	ADD I, C
	ADD J, C
:.backwardsloop
	STD [I], [J]
	IFN I, A
	SET PC, .backwardsloop

	SET J, POP
	SET I, POP
	SET PC, POP
