NAME		=	cub3d

LIBFT		=	libft/libft.a

MLX		=	libmlx.a

CFLAGS		=	-Wall -Wextra -Werror -g

CC		=	gcc

HEADER		=	includes/cub3d.h

SRCS		=	srcs/s_cub3d.c \
			srcs/parsing/s_parse.c \
			srcs/parsing/s_parse_map.c \
			srcs/engine/s_img.c \
			srcs/engine/s_draw.c \
			srcs/engine/s_raycast.c \
			srcs/engine/s_player.c \
			srcs/engine/s_input.c \
			srcs/engine/s_texture.c \
			srcs/engine/s_sprite.c \
			srcs/engine/s_error.c \
			srcs/engine/s_free.c \
			srcs/engine/s_bmp.c \

OBJ		=	${SRCS:.c=.o}

.c.o		:
			${CC} -c -I ${HEADER} $< -o ${<:.c=.o}

all		:	${NAME}

${NAME}		:	${OBJ} ${HEADER} map.cub
			make bonus -C libft
			make -C mlx
			cp mlx/${MLX} .
			$(CC) ${LIBFT} ${MLX} ${OBJ} -o ${NAME}

clean		:
			rm -f ${OBJ}
			make clean -C libft
			make clean -C mlx

fclean		:	clean
			rm -rf ${NAME}
			make fclean -C libft
			rm ${MLX}

re			:	fclean all

