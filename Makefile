##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## A Makefile.
##

CC      = gcc
CFLAGS  = -g3 -Wall -Wextra
LDFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lm
SRC     = *.c
NAME    = my_world

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LDFLAGS)

clean:
	rm -f $(NAME)

re: clean all

style:
	coding-style.sh . .
	clear
	cat coding-style-reports.log
	rm -rf coding-style-reports.log

.PHONY: all clean re style
