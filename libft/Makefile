SRCS_DIR	=	srcs

SRCS		=	$(SRCS_DIR)/ft_atoi.c\
				$(SRCS_DIR)/ft_bzero.c\
				$(SRCS_DIR)/ft_isalnum.c\
				$(SRCS_DIR)/ft_isascii.c\
				$(SRCS_DIR)/ft_isspace.c\
				$(SRCS_DIR)/ft_isprint.c\
				$(SRCS_DIR)/ft_memcpy.c\
				$(SRCS_DIR)/ft_strlen.c\
				$(SRCS_DIR)/ft_tolower.c\
				$(SRCS_DIR)/ft_isalpha.c\
				$(SRCS_DIR)/ft_isdigit.c\
				$(SRCS_DIR)/ft_isnumber.c\
				$(SRCS_DIR)/ft_isinteger.c\
				$(SRCS_DIR)/ft_memcmp.c\
				$(SRCS_DIR)/ft_memset.c\
				$(SRCS_DIR)/ft_strncmp.c\
				$(SRCS_DIR)/ft_toupper.c\
				$(SRCS_DIR)/ft_memmove.c\
				$(SRCS_DIR)/ft_memdup.c\
				$(SRCS_DIR)/ft_strlcpy.c\
				$(SRCS_DIR)/ft_strchr.c\
				$(SRCS_DIR)/ft_strrchr.c\
				$(SRCS_DIR)/ft_memchr.c\
				$(SRCS_DIR)/ft_strnstr.c\
				$(SRCS_DIR)/ft_calloc.c\
				$(SRCS_DIR)/ft_strlcat.c\
				$(SRCS_DIR)/ft_strdup.c\
				$(SRCS_DIR)/ft_substr.c\
				$(SRCS_DIR)/ft_strjoin.c\
				$(SRCS_DIR)/ft_strtrim.c\
				$(SRCS_DIR)/ft_split.c\
				$(SRCS_DIR)/ft_itoa.c\
				$(SRCS_DIR)/ft_strmapi.c\
				$(SRCS_DIR)/ft_striteri.c\
				$(SRCS_DIR)/ft_putchar_fd.c\
				$(SRCS_DIR)/ft_putptr_fd.c\
				$(SRCS_DIR)/ft_putstr_fd.c\
				$(SRCS_DIR)/ft_putendl_fd.c\
				$(SRCS_DIR)/ft_putnbr_fd.c\
				$(SRCS_DIR)/ft_putulnbr_base_fd.c\
				$(SRCS_DIR)/ft_putlnbr_base_fd.c\
				$(SRCS_DIR)/ft_unumlen_base.c\
				$(SRCS_DIR)/ft_numlen_base.c\
				$(SRCS_DIR)/ft_ltoa_base.c\
				$(SRCS_DIR)/ft_ultoa_base.c\
				$(SRCS_DIR)/ft_lstnew_bonus.c\
				$(SRCS_DIR)/ft_lstadd_front_bonus.c\
				$(SRCS_DIR)/ft_lstsize_bonus.c\
				$(SRCS_DIR)/ft_lstlast_bonus.c\
				$(SRCS_DIR)/ft_lstdup.c\
				$(SRCS_DIR)/ft_lstadd_back_bonus.c\
				$(SRCS_DIR)/ft_lstdelone_bonus.c\
				$(SRCS_DIR)/ft_lstclear_bonus.c\
				$(SRCS_DIR)/ft_lstiter_bonus.c\
				$(SRCS_DIR)/ft_lstmap_bonus.c \
				$(SRCS_DIR)/ft_lstfind.c \
				$(SRCS_DIR)/ft_printf.c \
				$(SRCS_DIR)/get_next_line.c \
				$(SRCS_DIR)/get_next_line_utils.c \
				$(SRCS_DIR)/issorted_int.c\
				$(SRCS_DIR)/bubblesort_int.c\
				$(SRCS_DIR)/ft_free_ptr_array.c\
				$(SRCS_DIR)/strarr_len.c\
				$(SRCS_DIR)/strarr_to_intarr.c

OBJS_DIR	=	objs
OBJS		=	$(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
LIB_DIR		=	lib
NAME		=	$(LIB_DIR)/libft.a
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Iinclude 

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all:		${NAME}
${NAME}:	${SRCS} ${OBJS}
	ar rc ${NAME} ${OBJS}
clean:
	rm -f ${OBJS}
fclean:		clean 
	rm -f ${NAME}
re:			fclean all
