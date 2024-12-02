NAME	:= cub3d
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -Iminilibx-linux
MLXFLG	:= -lXext -lX11 -Lminilibx-linux -lmlx -lm
MLXLIB	:= minilibx-linux/libmlx.a
MLXDIR	:= minilibx-linux
LIBFT_FLAG := -Llibft/lib -lft
LIBFT	:= libft/lib/libft.a
LFTDIR	:= libft
RM		:= rm -rf
SRC		:= main.c \
			scrnbuffer.c\
			user_input.c\
			main_loop.c\
			new_map.c\
			ray.c\
			read_header.c\
			read_map.c\
			parsing_matrix_utils.c\
			player_new.c\
			player_init_utils.c\
			validate_map.c\
			error_management.c\

OBJ		:= ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ} ${MLXLIB} ${LIBFT}
	${CC} -o $(NAME) ${OBJ} ${CFLAGS} ${MLXFLG} ${LIBFT_FLAG}

submodules:
	git submodule init && git submodule update

${MLXLIB}:	submodules
	make -C ${MLXDIR}

${LIBFT}:	submodules
	make -C ${LFTDIR}

clean:
	${RM} ${OBJ}
	cd ${LFTDIR} &&	make clean
	cd ${MLXDIR} &&	make clean

fclean: clean
	${RM} ${NAME}
	${RM} ${LIBFT}
	${RM} ${MLXLIB}

re: fclean all

.PHONY:	all clean fclean re bonus
