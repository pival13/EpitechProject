##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

NAME	=	my_nm
NAME2	=	my_objdump

SRCNM	=	my_nm.c
SRCOBJ	=	my_objdump.c
SRCLIB	=	$(wildcard lib/*.c) tools.c

OBJNM32	=	$(SRCNM:.c=_32.o)
OBJNM64	=	$(SRCNM:.c=_64.o)
OBJOBJ32	=	$(SRCOBJ:.c=_32.o)
OBJOBJ64	=	$(SRCOBJ:.c=_64.o)
OBJLIB		=	$(SRCLIB:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra -O2 -pipe -g

%_32.o: %.c
	$(CC) $(CFLAGS) -DARCH=32	-c -o $@ $<

%_64.o: %.c
	$(CC) $(CFLAGS) -DARCH=64	-c -o $@ $<

all:	pre_compil compil post_compil

pre_compil:
	@echo "Compilation..."

nm:	$(NAME)

$(NAME):	$(OBJNM32) $(OBJNM64) $(OBJLIB)
	$(CC) -o $(NAME) $(OBJLIB) $(OBJNM32) $(OBJNM64) main.c -DFUNC=1 $(CFLAGS)

objdump: $(NAME2)

$(NAME2):	$(OBJOBJ32) $(OBJOBJ64) $(OBJLIB)
	$(CC) -o $(NAME2) $(OBJLIB) $(OBJOBJ32) $(OBJOBJ64) main.c -DFUNC=2 $(CFLAGS)

compil:	nm objdump

post_compil:
	@echo "Compilation completed"

clean:
	@rm -f *.o lib/*.o

fclean:	clean
	@rm -f $(NAME) $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re pre_compil compil post_compil
