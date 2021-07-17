.name "Black Death"
.comment "The day of death is better than the day of birth"

patientzero:
	zjmp		%-511

	ld			%851920, r4
	ld			%167936, r3
	st			r3, -25
	st			r4, -26
	ld			%984040, r2
	ld			%0, r16
	sti			r1, %:gingersaretheworld, %1
	fork		%:gingersaretheworld
	zjmp		%:gingerscontroltheworld

destroyacountry:
	live		%666
	ld			%1234567, r6
	ld			%0, r8
	st			r1, 31
	st			r1, 61
	st			r1, 91
	st			r1, 121
	st			r1, 151
	st			r1, 181

destroycontinent:
	live		%3055151
	st			r2, -410
	st			r2, -407
	st			r2, -404
	st			r2, -401
	st			r2, -398
	st			r2, -395

	live		%9868977
	st			r2, -397
	st			r2, -394
	st			r2, -391
	st			r2, -388
	st			r2, -385
	st			r2, -382

	live		%3055151
	st			r2, -384
	st			r2, -381
	st			r2, -378
	st			r2, -375
	st			r2, -372
	st			r2, -369

	live		%9868977
	st			r2, -371
	st			r2, -368
	st			r2, -365
	st			r2, -362
	st			r2, -359
	st			r2, -356

	live		%9868977
	st			r2, -358
	st			r2, -355
	st			r2, -352
	st			r2, -349
	st			r2, -346
	st			r2, -343

	live		%9868977
	st			r2, -345
	st			r2, -342
	st			r2, -339
	st			r2, -336
	st			r2, -333
	st			r2, -330

	zjmp		%:destroycontinent

destroy_world:
	st			r1, 38
	st			r1, 38
	st			r1, 38
	st			r1, 38
	st			r1, 38
	st			r1, 38

kill_god:
	ld			%1, r16

putallgingerspresident:
	live		%76544674
	live		%76544674
	live		%76544674
	live		%76544674
	live		%76544674
	live		%76544674
	zjmp		%:putallgingerspresident
	fork		%:putallgingerspresident
	ld			%0, r16
	zjmp		%:putallgingerspresident

gingerscontroltheworld:
	sti			r1, %:edsheerancreatethenationalanthem, %1
	sti			r1, %:edsheerancreatethenationalanthem, %9
	sti			r1, %:edsheerancreatethenationalanthem, %17
	sti			r1, %:edsheerancreatethenationalanthem, %25
	sti			r1, %:edsheerancreatethenationalanthem, %33
	sti			r1, %:edsheerancreatethenationalanthem, %41
	sti			r1, %:edsheerancreatethenationalanthem, %49
	sti			r1, %:destroyacountry, %1
	st			r1, 6
	live		%875765
	fork		%:destroyacountry

edsheerancreatethenationalanthem:
	live		%76578685
	fork		%:edsheerancreatethenationalanthem
	live		%76578685
	fork		%:destroycontinent
	live		%76578685
	fork		%:destroyacountry
	live		%65435454
	fork		%:destroyacountry
	live		%65435454
	fork		%:destroy_world
	live		%76578685
	fork		%:kill_god
	live		%76578685
	fork		%:edsheerancreatethenationalanthem
	zjmp		%:edsheerancreatethenationalanthem

gingersaretheworld:
	live		%666
zjmp %511
