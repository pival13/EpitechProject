	#
	#test.s
	#
	
	.name "spartiate"
	.comment "JHellox"

begin:
	sti r1,%:live,%1
	lfork %:live
	lld %1,r1
	lld %400,r2
	lld %11,r3
	lld %100,r5
	lld %0,r6
	lld %:repeat,r4
	sti r4,%:live,r5

repeat:
	#sti r1,r2,%:live
	#add r3,r2,r2
	lld %0, r8
	zjmp %:repeat

live:
	live %0
	ld %0,r8
	zjmp %:live
