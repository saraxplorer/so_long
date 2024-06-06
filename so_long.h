#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <memory.h>
# include <time.h>

# define PIXELS 64

typedef struct s_img
{
	mlx_image_t			*wall;
	mlx_image_t			*background;
	mlx_image_t			*geld;
	mlx_image_t			*exit;
	mlx_image_t			*player;

} t_img;

typedef struct s_game
{
	char			**grid;
	size_t			width;
	size_t			height;
	size_t			geld;
	size_t			steps;
	size_t			collected;
	size_t			player_x;
	size_t			player_y;
	size_t			exit_x;
	size_t			exit_y;
	t_img			*img;
	mlx_t			*mlx;
}t_game;

void error_exit(char* str);

void 	check_file_extension(char *name);
void	check_empty(char *map);
void	check_empty_line(char *map);
void	check_content(char *map);
int		check_map_shape(char **map_array);
void	check_walls(t_game *game);
void	check_path(char **map, int height);

void	element_position(char **map, t_game *game);

t_game	initialize_game_struct(char **grid, int height);
t_game	map_to_data(char *argv);
t_img *struct_image(t_game *game);

void	background_to_window(t_game *game);
void 	images_to_window(t_game *game);

t_img *background_tx(mlx_t *mlx, t_img *image);
t_img *wall_tx(mlx_t *mlx, t_img *image);
t_img *collectable_tx(mlx_t *mlx, t_img *image);
t_img *exit_tx(mlx_t *mlx, t_img *image);
t_img *player_tx(mlx_t *mlx, t_img *image);

void	hook_moves(mlx_key_data_t keydata, void *mlx);
void	move_player(t_game *game, char line, char dir);
void	move_select(t_game *game, char line, char dir);
t_game	*move_up(t_game *game);
t_game	*move_down(t_game *game);
t_game	*move_right(t_game *game);
t_game	*move_left(t_game *game);

void	finish_game_checker(t_game *game);
t_game	*collect_checker(int y, int x, t_game *game);

void	free_map(char **map, int height);


#endif
