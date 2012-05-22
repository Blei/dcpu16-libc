	.text
:memmove
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

	ifg a, b
	set pc, .backwards
	add b, c
:.loop
	sti [i], [j]
	ifn b, j
	set pc, .loop

	set j, pop
	set i, pop
	set pc, pop

:.backwards
	; start from the end
	add i, c
	add j, c
:.backwardsloop
	std [i], [j]
	ifn i, a
	set pc, .backwardsloop

	set j, pop
	set i, pop
	set pc, pop
