.name "Our champ"
.comment "Comment of our champ"

start:
	and r2, r2, r2
	sti r1, %:live, %1
	sti r1, %:fork, %1
fork:
	live %99
	ld %10, r3
	fork %:live
	zjmp %:fork
live:
	live %99
	zjmp %:live
