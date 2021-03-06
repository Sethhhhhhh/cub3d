NAME		=	cub3d

HEADER		=	./includes/

LIBFT		=	libft/libft.a

MLX		=	mlx/libmlx.a

MLX_MAC		=	-lmlx -framework OpenGL -framework AppKit

MLX_LINUX	=	-lm -lbsd -lX11 -lXext

CC		=	gcc

FLAGS		=	-Werror -Wall -Wextra -I $(HEADER)

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

OBJS		=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(MLX) $(HEADER) map.cub
			$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX) $(MLX_LINUX)

$(LIBFT)	:
			make -C ./libft

$(MLX)		:
			make -C ./mlx

clean		:
			rm -rf $(OBJS)
			make clean -C ./libft
			make clean -C ./mlx

fclean		:	clean
			rm $(NAME)
			make fclean -C ./libft

re		:	fclean all

