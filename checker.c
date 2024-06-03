#include "so_long.h"
t_game	*collect_checker(int y, int x, t_game *game)
{
	size_t geld;

	geld = 0;
	if (game->grid[y][x] == 'C')
	{
		while (geld < game->img->geld->count)
		{
			if (((game->img->geld->instances[geld].x) / PIXELS) == x
					&& ((game->img->geld->instances[geld].y) / PIXELS) == y)
			{
				game->img->geld->instances[geld].enabled = false;
				game->geld--;
				game->grid[y][x] = '0';
			}
			geld++;
		}
	}
	return (game);
}

void	finish_game_checker(t_game *game)
{
	ft_printf("Moves: %i\n", game->steps);
	if (game->geld == 0)
		ft_putendl_fd("yay", 1);
	if (game->geld == 0
			&& game->player_x == game->exit_x
			&& game->player_y == game->exit_y)
	{
		mlx_close_window(game->mlx);
		ft_printf("\n");
		ft_putendl_fd("congratulations", 1);
		ft_putendl_fd("treasures! yay", 1);
		ft_putendl_fd("Play again? choose another map", 1);
	}
	else if (game->player_x == game->exit_x
			&& game->player_y == game->exit_y)
	{
		ft_printf("\n");
		ft_putendl_fd("More treasures left", 2);
		ft_putendl_fd("get more treasure", 2);
	}
}