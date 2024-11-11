
NAME			= hb_menu_lib.a
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0 -fsanitize=address

CC				= gcc

HEADERS			:= -I ./include

LIB_DIR			:= ./lib

SRCS			:= menu_item_type.c \
				menu_item_utils.c \
				menu_nav_hooks.c \
				menu_nav_utils.c \
				menu_redraw.c \
				menu_type.c 

OBJS			:= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf ./*.o

fclean: clean
	rm -rf ./$(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
