##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC	=	$(wildcard */)

%_: %/
	@make --no-print-directory -C $<
	@cp $(<D)/lib_arcade_*.so .

%_c: %/
	@make clean --no-print-directory -C $<

%_f: %/
	@make fclean --no-print-directory -C $<

%_r: %/
	@make re --no-print-directory -C $<

games:	$(SRC:/=_)
	@rm -f lib_arcade_.so

clean:	$(SRC:/=_c)

fclean:	$(SRC:/=_f)
	@rm -f *.so

re:	$(SRC:/=_r)

.PHONY:	all clean fclean re
