# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/03 15:27:19 by rshaheen      #+#    #+#                  #
#    Updated: 2024/06/03 17:40:34 by rshaheen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT = ./libft/libft.a

MLXLIB = MLX42/build/libmlx42.a

LIBMLX = ./MLX42

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

FLAGSMLX = -ldl -lglfw -pthread -lm

OBJ_DIR = obj

SOURCE = main.c \
		map_to_data.c \
		check_content.c \
		check_shape_walls.c \
		struct_image.c \
		add_to_window.c \
		texture.c \
		hook_moves.c \
		checker.c \
		free_map.c \

			

OBJECTS = $(SOURCE:%.c=$(OBJ_DIR)/%.o)

all: $(MLXLIB) $(NAME)

$(MLXLIB):
	@cmake $(LIBMLX) -DEBUG=1 -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLXLIB) $(OBJ_DIR) $(OBJECTS)
	@cc $(CFLAGS) $(FLAGSMLX) $(OBJECTS) $(LIBFT) $(MLXLIB) -o $(NAME)

clean: 
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build

re: fclean all

.PHONY: all clean fclean re