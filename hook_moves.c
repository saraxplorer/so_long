#include "so_long.h"

t_game	*move_up(t_game *game)
{
	if (game->grid[game->player_y - 1][game->player_x] != '1')
	{
		game->img->player->instances->y -= PIXELS;
		game->player_y--;
		game->steps++;
		collect_checker(game->player_y, game->player_x, game);
	}
	else
		ft_putendl_fd("\n	Ouch! 😢", 1);
	finish_game_checker(game);
	return (game);
}

t_game	*move_down(t_game *game)
{
	if (game->grid[game->player_y + 1][game->player_x] != '1')
	{
		game->img->player->instances->y += PIXELS;
		game->player_y++;
		game->steps++;
		collect_checker(game->player_y, game->player_x, game);
	}
	else
		ft_putendl_fd("\n	Ouch", 1);
	finish_game_checker(game);
	return (game);
}

t_game	*move_left(t_game *game)
{
	if (game->grid[game->player_y][game->player_x - 1] != '1')
	{
		game->img->player->instances->x -= PIXELS;
		game->player_x--;
		game->steps++;
		collect_checker(game->player_y, game->player_x, game);
	}
	else
		ft_putendl_fd("\n	Ouch", 1);
	finish_game_checker(game);
	return (game);
}

t_game	*move_right(t_game *game)
{
	if (game->grid[game->player_y][game->player_x + 1] != '1')
	{
		game->img->player->instances->x += PIXELS;
		game->player_x++;
		game->steps++;
		collect_checker(game->player_y, game->player_x, game);
	}
	else
		ft_putendl_fd("\n	Ouch", 1);
	finish_game_checker(game);
	return (game);
}

void	hook_moves(mlx_key_data_t keydata, void *mlx)
{
	t_game	*game;

	game = (t_game *)mlx;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
	}
	if ((keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS))
		move_up(mlx);
	if ((keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS))
		move_down(mlx);
	if ((keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS))
		move_left(mlx);
	if ((keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS))
		move_right(mlx);
}