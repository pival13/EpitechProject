all:
	go tool compile 206neutrinos.go
	go tool link -o 206neutrinos 206neutrinos.o

clean:
	rm -f 206neutrinos.o

fclean:	clean
	rm -f 206neutrinos

re:	fclean all