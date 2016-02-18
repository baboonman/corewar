.name		"TEST FILE NAME"
.comment	"COMMENT TEST FOR TEST FILE ASM FOR COREWAR"

label:
	and		10000, %:label, r9
	and		10000, %:toto, r9
	and		10000, %32, r9
toto:
	and		10000, %:label, r9
	and		10000, %:toto, r9
