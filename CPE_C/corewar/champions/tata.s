	.name "Tata"
	.comment "Tu dois vivre mon fils!!!"

	st r1 6
	live %100
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
	st r1 114
un_pour_tous:	fork %:tous_pour_un
	ld %0 r2
	zjmp %:un_pour_tous
tous_pour_un:	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	live %100
	ld %0 r2
	zjmp %:tous_pour_un
