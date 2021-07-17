##
## EPITECH PROJECT, 2020
## FUN_imageCompressor_2019 [WSL: Ubuntu]
## File description:
## Makefile
##

all:
	stack build --ghc-options="-Wall -Wextra"
	cp `stack path --local-install-root`/bin/hal .

test: all
	test/test.sh

clean:
	rm -f stack.yaml.lock
	rm -rf .stack-work

fclean: clean
	rm -f hal

re: fclean all