# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emurky <emurky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 17:48:52 by emurky            #+#    #+#              #
#    Updated: 2021/04/28 07:55:59 by emurky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSDIR				= ./sources

SRCS				= $(addprefix $(SRCSDIR)/, \
						cub3d.c \
						my_mlx_utils.c \
						parser.c \
						parse_identifiers.c \
						set_parsed.c \
						parse_map.c \
						check_map.c \
						parser_utils.c \
						player_move.c \
						key_hooks.c \
						raycaster.c \
						raycasting_itself.c \
						draw_map.c \
						texturer.c \
						draw_sprites.c \
						sprites_utils.c \
						utils.c \
						screenshot.c \
						error.c \
						unused.c \
						)

OBJS				= $(SRCS:.c=.o)

DEPS				= $(SRCS:.c=.d)

NAME				= cub3D

CC 					= gcc
RM 					= rm -f
CFLAGS				= -Wall -Wextra -Werror -O2 #-g -fsanitize=address
CPPFLAGS			= -MMD -I. -I./includes
MLX_FLAGS			= -framework OpenGL -framework AppKit -lz

LIBS				= \
						-L./libft -lft \
						-L./mlx -lmlx $(MLX_FLAGS)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(MAKE) -C ./libft -j4
					$(MAKE) -C ./mlx -j4
					$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

-include			$(DEPS)

bonus:				all

clean:
					$(MAKE) clean -C ./libft
					$(MAKE) clean -C ./mlx
					$(RM) $(OBJS) $(DEPS) screenshot.bmp

fclean:				clean
					$(RM) ./libft/libft.a
					$(RM) ./mlx/libmlx.a
					$(RM) $(NAME)

re:					fclean all


# *************** libft rules *************** #
libft:
					$(MAKE) -C ./libft

libft_clean:
					$(MAKE) clean -C ./libft

libft_fclean:
					$(MAKE) fclean -C ./libft

libft_re:
					$(MAKE) re -C ./libft
# ******************************************** #

sc:
					rm -rf *.o *.a */*.o */*.a */*.d *.d 'cub3D '* cub3D

.PHONY:				all clean fclean re bonus \
					libft libft_clean libft_fclean libft_re \
					sc

#.SILENT:
# gcc -Wall -Wextra -Werror -framework OpenGL -framework AppKit -lz 
# -L./libft -lft -L./mlx -lmlx -g sources/*.c -o cub3D
