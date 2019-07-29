# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: notraore <notraore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/17 16:13:57 by notraore          #+#    #+#              #
#    Updated: 2019/03/13 15:43:12 by notraore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	ft_ssl
LIBFT 		= 	libft/libft.a

SRCS		= 	main.c \
				digest.c \
				utils.c \
				md5.c \
				sha256.c \
				sha512.c

OBJS		= 	$(patsubst srcs/%.c,objs/%.o,$(SRCS))

CC			= 	gcc
CFLAGS		= 	

CG = \033[92m
CY = \033[93m
CE = \033[0m

all:		$(NAME)

$(NAME):	$(OBJS)
			@ make -C ./libft all
			@ $(CC) $(LIBFT) $(CFLAGS) -o $@ $^
			@ echo "\n\033[92m---> hash program created ✓\033[0m";

objs/%.o:	srcs/%.c
			@ mkdir -p objs
		 	@ $(CC) -c $< -o $@
		 	@ echo "\033[K$(CY)[RT] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean:		
			@ make -C libft/ clean
			@ /bin/rm -rf objs/
			@ echo "\033[1;33m---> All .o files cleared\033[0m \033[92m✓\033[0m";

fclean:		clean
			@ /bin/rm -f $(NAME)
			@ make -C libft/ fclean
			@ echo "\n\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\033[0m";
re : fclean all

.PHONY: all, clean, fclean, re
