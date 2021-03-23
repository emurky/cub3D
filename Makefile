# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emurky <emurky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 17:48:52 by emurky            #+#    #+#              #
#    Updated: 2021/03/24 00:12:57 by emurky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS				= \
						cub3d.c

OBJS				= $(SRCS:.c=.o)

INCS				= \
						-I./libft \
						-I./mlx \
						-I.

NAME				= cub3d

CC 					= gcc
RM 					= rm -f
CFLAGS				= -Wall -Wextra -Werror
MLX_FLAGS			= -framework OpenGL -framework AppKit

LIBS				= \
						-L./libft -lft \
						-L./mlx -lmlx $(MLX_FLAGS)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(MAKE) -C ./libft -j 8
					$(MAKE) -C ./mlx -j 8
					$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBS) -o $(NAME)

bonus:				all

clean:
					$(MAKE) clean -C ./libft
					$(MAKE) clean -C ./mlx
					$(RM) $(OBJS)

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

superclean:
					rm -r *.o *.a */*.o */*.a cub3d* !(cub3d.*)

.PHONY:				all clean fclean re bonus \
					libft libft_clean libft_fclean libft_re \
					superclean
#.SILENT:
