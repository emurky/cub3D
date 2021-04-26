# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emurky <emurky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 17:48:52 by emurky            #+#    #+#              #
#    Updated: 2021/04/27 01:18:44 by emurky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSDIR				= ./sources
# OBJSDIR				= objs
# DEPSDIR				= deps

SRCS				= $(addprefix $(SRCSDIR)/, \
						cub3d.c \
						parser.c \
						parser_utils.c \
						raycaster.c \
						texturer.c \
						draw_sprites.c \
						draw_map.c \
						key_hooks.c \
						player_move.c \
						my_mlx_utils.c \
						utils.c \
						error.c \
						)

OBJS				= $(SRCS:.c=.o)

DEPS				= $(SRCS:.c=.d)

NAME				= cub3D

CC 					= gcc
RM 					= rm -f
CFLAGS				= -Wall -Wextra -Werror -fsanitize=address #-O2
CPPFLAGS			= -MMD -I. -I./includes
MLX_FLAGS			= -framework OpenGL -framework AppKit -lz

LIBS				= \
						-L./libft -lft \
						-L./mlx -lmlx $(MLX_FLAGS)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(MAKE) -C ./libft -j 4
					$(MAKE) -C ./mlx -j 4
					$(CC) $(CFLAGS) $(OBJS) $(LIBS) -g -o $(NAME)

-include			$(DEPS)

bonus:				all

clean:
					$(MAKE) clean -C ./libft
					$(MAKE) clean -C ./mlx
					$(RM) $(OBJS) $(DEPS)

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
					rm -rf *.o *.a */*.o */*.a */*.d *.d 'cub3D '* cub3D a.out cub3D.dSYM

.PHONY:				all clean fclean re bonus \
					libft libft_clean libft_fclean libft_re \
					sc
#.SILENT:
