# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emurky <emurky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 17:48:52 by emurky            #+#    #+#              #
#    Updated: 2021/04/04 02:01:32 by emurky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSDIR				= ./sources
# OBJSDIR				= objs
# DEPSDIR				= deps

SRCS				= $(addprefix $(SRCSDIR)/, \
						cub3d.c \
						)

OBJS				= $(SRCS:.c=.o)

DEPS				= $(SRCS:.c=.d)

NAME				= cub3d

CC 					= gcc
RM 					= rm -f
CFLAGS				= -Wall -Wextra -Werror
CPPFLAGS			= -MMD -I. -I./includes
MLX_FLAGS			= -framework OpenGL -framework AppKit

LIBS				= \
						-L./libft -lft \
						-L./mlx -lmlx $(MLX_FLAGS)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(MAKE) -C ./libft -j 8
					$(MAKE) -C ./mlx -j 8
					$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

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
					rm -rf *.o *.a */*.o */*.a */*.d *.d 'cub3d '* cub3d a.out

.PHONY:				all clean fclean re bonus \
					libft libft_clean libft_fclean libft_re \
					superclean
#.SILENT:
