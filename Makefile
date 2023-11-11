# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 13:18:46 by jesuserr          #+#    #+#              #
#    Updated: 2023/11/11 13:18:46 by jesuserr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft/
LIBX_DIR = minilibx_macos/

NAME = ./cub3D/cub3D
SRCS = errors.c errors2.c graphics.c hooks.c main.c map_utils.c map_utils2.c \
map_utils_parse.c map_utils_check.c map_utils_check2.c moves.c ray_casting.c \
raycast_utils.c wall_utils.c txt_utils.c sprites.c sprites2.c enemy.c \
character.c
PATH_SRCS = ./cub3D/
PATH_OBJS = ./cub3D/
PATH_DEPS = ./cub3D/

NAME_BONUS = ./cub3D_bonus/cub3D_bonus
SRCS_BONUS = errors_bonus.c errors2_bonus.c graphics_bonus.c hooks_bonus.c \
main_bonus.c map_utils_bonus.c map_utils2_bonus.c map_utils_parse_bonus.c \
map_utils_check_bonus.c map_utils_check2_bonus.c moves_bonus.c \
ray_casting_bonus.c graphics_2_bonus.c raycast_utils_bonus.c \
wall_utils_bonus.c txt_utils_bonus.c sprites_bonus.c sprites2_bonus.c \
enemy_bonus.c character_bonus.c
PATH_SRCS_BONUS = ./cub3D_bonus/
PATH_OBJS_BONUS = ./cub3D_bonus/
PATH_DEPS_BONUS = ./cub3D_bonus/

OBJS = $(addprefix $(PATH_OBJS), $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(PATH_OBJS_BONUS), $(SRCS_BONUS:.c=.o))
DEPS = $(addprefix $(PATH_DEPS), $(SRCS:.c=.d))
DEPS_BONUS = $(addprefix $(PATH_DEPS_BONUS), $(SRCS_BONUS:.c=.d))

INCLUDE = -I./ -I./minilibx_macos/ -I./libft/includes/
RM = rm -f
CFLAGS = -O3 -Wall -Wextra -Werror

NORM = $(addprefix $(PATH_SRCS), $(SRCS)) $(PATH_SRCS)cub3d.h \
$(PATH_SRCS)controls.h
NORMB = $(addprefix $(PATH_SRCS_BONUS), $(SRCS_BONUS)) \
$(PATH_SRCS_BONUS)cub3d.h $(PATH_SRCS_BONUS)controls.h
GREEN = "\033[0;92m"
RED = "\033[0;91m"
BLUE = "\033[0;94m"
NC = "\033[37m"

LIBX = -lmlx -lz -framework OpenGL -framework Appkit -Lminilibx_macos/

all: makelibft makelibx $(NAME)

makelibft:
	@make --no-print-directory -C $(LIBFT_DIR)	
	@echo ${GREEN}"Libft Compiled!\n"${NC};

makelibx:
	@make --no-print-directory -C $(LIBX_DIR) 2> ERRORS
	@rm ERRORS
	@echo ${GREEN}"MiniLibx Compiled!\n"${NC};
	
%.o: %.c
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@
	
$(NAME): $(OBJS) $(LIBFT_DIR)libft.a $(LIBX_DIR)libmlx.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)libft.a $(LIBX) -o $@
	@echo ${GREEN}"cub3D Compiled!\n"${NC};
-include $(DEPS)

bonus: makelibft makelibx $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT_DIR)libft.a $(LIBX_DIR)libmlx.a
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_DIR)libft.a $(LIBX) -o $@
	@echo ${GREEN}"cub3D Bonus Compiled!\n"${NC};
-include $(DEPS_BONUS)

clean:
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(LIBX_DIR)
	$(RM) $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)
		
fclean:
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(LIBX_DIR)
	$(RM) $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)
	$(RM) $(NAME) $(NAME_BONUS)

norm:
	@echo ${BLUE}"\nChecking Norminette..."${NC}
	@if norminette $(NORM); then echo ${GREEN}"Norminette OK!\n"${NC}; \
	else echo ${RED}"Norminette KO!\n"${NC}; \
	fi

normb:
	@echo ${BLUE}"\nChecking Norminette..."${NC}
	@if norminette $(NORMB); then echo ${GREEN}"Norminette OK!\n"${NC}; \
	else echo ${RED}"Norminette KO!\n"${NC}; \
	fi

re: fclean all

.PHONY: all clean fclean re bonus makelibft norm makelibx normb
