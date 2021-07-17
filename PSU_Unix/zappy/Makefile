##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

all:
	@make -C server/ --no-print-directory
	@make -C lib/ --no-print-directory
	@make -C clients/ --no-print-directory
	cp clients/ai/zappy_ai zappy_ai

clean:
	@make clean -C server/ --no-print-directory
	@make clean -C lib/ --no-print-directory
	@make clean -C clients/ --no-print-directory

fclean:
	rm -f *.html
	rm -f zappy_ai
	@make fclean -C server/ --no-print-directory
	@make fclean -C lib/ --no-print-directory
	@make fclean -C clients/ --no-print-directory

libraries:
	@make -C lib/ --no-print-directory

doc:
	rm -f *.html
	@make doc -C server/ --no-print-directory
	@make doc -C lib/ --no-print-directory
	@make doc -C clients/ --no-print-directory
	ln -s lib/index.html LibraryDocumentation.html
	ln -s server/index.html ServerDocumentation.html
	ln -s clients/index.html ClientsDocumentation.html
	ln -s clients/ai/index.html AiDocumentation.html
	ln -s clients/graphical/index.html GraphicalDocumentation.html

re: fclean all

.PHONY: clean re fclean all
