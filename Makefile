NAME	:= cub3D
CC		:= cc
CFLAGS	+= -Wall -Wextra -Werror -Iminilibx-linux
MLXFLG	:= -lmlx -lXext -lX11 -Lminilibx-linux -lm
MLXLIB	:= minilibx-linux/libmlx.a
MLXDIR	:= minilibx-linux
LIBFT_FLAG := -Llibft/lib -lft
LIBFT	:= libft/lib/libft.a
LFTDIR	:= libft
RM		:= rm -rf
SRC		:= main.c \
			image_interface.c\
			buffering.c\
			user_input.c\
			game_loop.c\
			new_map.c\
			ray.c\
			read_header.c\
			read_map.c\
			parsing_matrix_utils.c\
			player_new.c\
			player_init_utils.c\
			validate_map.c\
			dda.c\
			dda_remains.c\
			minimap.c

OBJ		:= ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${MLXLIB} ${LIBFT} $(OBJ)
	${CC} $(CFLAGS) -o $(NAME) ${OBJ} ${CFLAGS} ${LDFLAGS} ${MLXFLG} ${LIBFT_FLAG}

${MLXLIB}:
	make -C ${MLXDIR}

${LIBFT}:
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

debug: fclean $(MLXLIB) $(LIBFT)
	@CFLAGS="$(CFLAGS) -g3" make -e all

.PHONY:	all clean fclean re bonus
