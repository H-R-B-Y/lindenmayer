
NAME			= lindenmayer.out
# CFLAGS			:= -Wextra -Wall -Werror -g3 -O0 -fsanitize=address
CFLAGS			:= -g3 -O0 -fsanitize=address

HEADERS			:= -I ./include

LIB_DIR			:= ./lib

LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
LIBFT			:= $(LIBFT_DIR)/libft.a

LIBMLX_DIR		:= $(abspath $(LIB_DIR)/MLX42)
LIBMLX			:= $(LIBMLX_DIR)/build/libmlx42.a
LIBFLAGS		:=  -ldl `pkg-config --libs glfw3` -pthread -lm

SRC_DIR			:= ./src
SRCS			:= $(SRC_DIR)/draw_line.c \
				$(SRC_DIR)/rules.c \
				$(SRC_DIR)/prop.c \
				$(SRC_DIR)/vec2_math.c \
				$(SRC_DIR)/default_d_rules.c \
				$(SRC_DIR)/hooks.c

OBJS			:= ${SRCS:.c=.o}

MAIN 			:= $(SRC_DIR)/main.c

all: $(NAME)

$(LIBFT):
		$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)"

$(LIBMLX):
		cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make CFLAGS="$(CFLAGS)" -C $(LIBMLX_DIR)/build -j4 

$(NAME): $(MAIN) $(OBJS) $(LIBFT) $(ANIM_ENGINE) $(LIBMLX) $(DIJKSTRA) $(MAP_PARSE)
		$(CC) $(CFLAGS) $(MAIN) $(OBJS) $(LIBFT) $(LIBMLX) $(LIBFLAGS) -o $(NAME)

.c.o:
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
		$(MAKE) --directory $(LIBFT_DIR) clean
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(LIBMLX_DIR)/build
		$(MAKE) --directory $(LIBFT_DIR) fclean
		rm -rf $(NAME)

rm:
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, test
