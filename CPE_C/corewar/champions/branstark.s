.name		"Bran Stark"
.comment	"Bran the Broken, Protector of the Realm"

		st	r1,19
		ld	%0,r15
		fork	%:im_here_bro
		zjmp	%:destroy
im_here_bro:		live	%42
		fork	%:destroy
		zjmp	%:im_here_bro
	
i_ll:		live	%42
		fork	%:north
		st	r1,13
		ld	%0,r15		
protect:		live	%42
		zjmp	%-5
		
north:		live	%42
		fork	%:these
		st	r1,13
		ld	%0,r15
kill:		live	%42
		zjmp	%-5

these:		live	%42
		fork	%:white
		st	r1,13
		ld	%0,r15
fucking:		live	%42
		zjmp	%-5

white:		live	%42
		fork	%:i_ll
		st	r1,13
		ld	%0,r15
walkers:		live	%42
		zjmp	%-5		
			
construct_the_wall:      live	%42	
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		st	r8,-400
		ld	%0,r15
		zjmp	%:construct_the_wall

destroy:		live	%42
		fork	%:the
		live	%42
		fork	%:night
		live	%42
		fork	%:king
		ld	%57672448,r3
		ld	%318992390,r6
		ld	%0,r15
		zjmp	%:launch
	
the:		live	%42
		fork	%:destroy
		live	%42
		fork	%:i_ll
		ld	%251883526,r3
		ld	%386101254,r6
		ld	%0,r15
		ld	%0,r15
		zjmp	%:launch

night:		live	%42
		fork	%:construct_the_wall
		ld	%4294902082,r3
		ld	%436432902,r6
		ld	%0,r15
		ld	%0,r15
		ld	%0,r15
		zjmp	%:launch

king:		st	r1,r3	
		ld	%251883526,r6
		ld	%0,r15
		ld	%0,r15
		ld	%0,r15
		ld	%0,r15
		zjmp	%:launch

launch:	st	r3,15
	st	r6,-1
construction:	live %42
zjmp %:construction
