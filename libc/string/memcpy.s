	.text
:memcpy
	; same as memmove, but we don't care about forward/backward
	; A: dst
	; B: src
	; C: n
	; return: dst
	ife c, 0
	set pc, pop

	set push, i
	set push, j
	set i, a
	set j, b
	add b, c
:.loop
	sti [i], [j]
	ifn b, j
	set pc, .loop

	set j, pop
	set i, pop
	set pc, pop
