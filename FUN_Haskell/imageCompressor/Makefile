##
## EPITECH PROJECT, 2020
## FUN_imageCompressor_2019 [WSL: Ubuntu]
## File description:
## Makefile
##

all:
	stack build
	cp `stack path --local-install-root`/bin/imageCompressor .

clean:
	rm -f stack.yaml.lock
	rm -rf .stack-work

fclean: clean
	rm -f imageCompressor

re: fclean all