# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/22 00:33:10 by flevesqu          #+#    #+#              #
#    Updated: 2016/11/14 22:58:36 by flevesqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

LIB = libft

FILES =	main.c\
		game.c\
		game_loop.c\
		gui_events.c\
		init.c\
		raycaster.c\
		surfaces.c\
		pixels.c\
		map.c\
		menu.c\
		sprites.c\
		medias.c\
		events_keyup.c\
		events_keydown.c\
		print_sprites.c\
		moves_actions.c\
		mouse_actions.c\
		text.c\
		gif.c\
		init_sprites.c\
		threads.c

FRAMEWORKS_NAME =	SDL2\
					SDL2_ttf\
					SDL2_image\
					SDL2_mixer

CC = clang

WFLAGS = -Wall -Werror -Wextra -O3 -march=native -ffast-math

LFLAGS = -L $(LIB)/ -lft -lm

LIB_INCLUDES = ./$(LIB)/includes/

SRC_INCLUDES = ./includes/

SRC_DIR = ./src/
OBJ_DIR = ./obj/

FRAMEWORKS_DIR = ~/Library/Frameworks/

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

FRAMEWORKS_INCLUDES = $(addsuffix .framework/Headers/, $(FRAMEWORKS_NAME))

FRAMEWORKS_SRC = $(addprefix -framework , $(FRAMEWORKS_NAME))
FRAMEWORKS_HEAD = $(addprefix -I $(FRAMEWORKS_DIR), $(FRAMEWORKS_INCLUDES))

HEADER = $(SRC_INCLUDES)$(NAME).h

FRAMEWORKS = -F $(FRAMEWORKS_DIR) $(FRAMEWORKS_SRC)
FRAMEWORKS_HEADER  = -F $(FRAMEWORKS_DIR) $(FRAMEWORKS_HEAD)

FRAMEWORKS_LOCATION = $(addprefix $(FRAMEWORKS_DIR), $(addsuffix .framework, $(FRAMEWORKS_NAME)))

all : $(FRAMEWORKS_LOCATION) $(OBJ_DIR) $(NAME)

$(FRAMEWORKS_LOCATION) :
	@if ! ls $@ 1>/dev/null 2>/dev/null;\
	then echo "Install frameworks..." && cp -rf $(addprefix ./Framework/, $(addsuffix .framework, $(FRAMEWORKS_NAME))) $(FRAMEWORKS_DIR) && echo "Frameworks installed" !;\
	fi

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(LIB) :
	make -C $(LIB)

obj/%.o: src/%.c $(HEADER)
	$(CC) -c $(WFLAGS) -I $(LIB_INCLUDES) -I $(SRC_INCLUDES) $(FRAMEWORKS_HEADER) $< -o $@

$(NAME) : $(OBJ) $(HEADER)
	make -C $(LIB)
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(FRAMEWORKS) $(FRAMEWORKS_HEADER) $(LFLAGS)

clean :
	rm -rf $(OBJ)
	@if test -d $(OBJ_DIR);then rmdir $(OBJ_DIR) && echo "directory "$(OBJ_DIR)" deleted.";fi

lclean :
	make -C $(LIB)/ clean

fclean : clean
	rm -f $(NAME)

lfclean :
	make -C $(LIB)/ fclean

install_frameworks :
	cp -rf $(addprefix ./Framework/, $(addsuffix .framework, $(FRAMEWORKS_NAME))) $(FRAMEWORKS_DIR)

uninstall_frameworks :
	rm -rf $(FRAMEWORKS_LOCATION)

re : fclean all

lre :
	make -C $(LIB)/ re

.PHONY: all clean fclean re lclean lfclean lre frameworks
