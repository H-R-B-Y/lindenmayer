NAME		= libft.a
HEADER		= libft.h

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rc

SRC			= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
			ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			ft_substr.c ft_tolower.c ft_toupper.c ft_memmove.c get_next_line.c\
			get_next_line_utils.c
OBJ			= $(SRC:.c=.o)

BSRC		= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
			ft_lstmap_bonus.c ft_lstget_bonus.c ft_lstiter_param_bonus.c
BOBJ		= $(BSRC:.c=.o)

all:		$(NAME) bonus

$(NAME):	$(OBJ)
			$(AR) $(NAME) $(OBJ)

.c.o:
			$(CC) $(CFLAGS) -c $<

bonus:		$(BOBJ)
			$(AR) $(NAME) $(BOBJ)

clean:
			rm -f $(OBJ) $(BOBJ)

fclean:		clean
			rm -f libft.a libft.so

re:			fclean all

.PHONY:		re all clean fclean bonus

# For portable object files
#so:
#			$(CC) -nostartfiles -fPIC $(CFLAGS) -c $(SRC) $(BSRC)
#			gcc -nostartfiles -shared -o libft.so $(OBJ) $(BOBJ)
