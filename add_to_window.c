/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_to_window.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 18:24:11 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/05/28 15:50:04 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	background_to_window(t_game *game)
{
	size_t	row;
	size_t	column;

	row = 0;
	while (row < game->height)
	{
		column = 0;
		while (column < game->width)
		{
			if (mlx_image_to_window(game->mlx, game->img->background, column * PIXELS, row * PIXELS) < 0)
				error_exit("cannot bring background to window");
			column++;	
		}
		row++;
	}
}

void	add_images(t_game *game, size_t row, size_t column)
{
	if (game->grid[row][column] == '1')
	{
		if (mlx_image_to_window(game->mlx, game->img->wall,
							column* PIXELS, row * PIXELS) < 0)
			error_exit("cannot bring wall to window");	
	}
	 if (game->grid[row][column] == 'P')
	{
		if (mlx_image_to_window(game->mlx, game->img->player,
							 column * PIXELS, row * PIXELS) < 0)
			error_exit("cannot bring player to window");
	}
	else if (game->grid[row][column] == 'C')
	{
		if (mlx_image_to_window(game->mlx, game->img->geld,
							 column * PIXELS, row * PIXELS) < 0)
			error_exit("cannot bring collectable to window");
	}
	else if (game->grid[row][column] == 'E')
	{
		if (mlx_image_to_window(game->mlx, game->img->exit,
							 column * PIXELS, row * PIXELS) < 0)
			error_exit("cannot bring exit to window");
	}
	
}

void images_to_window(t_game *game)
{
	size_t	row;
	size_t	column;
	
	row = 0;
	while (row < game->height)
	{
		column = 0;
		while (column < game->width)
		{
			add_images(game, row, column);
			column++;
		}
		row++;
	}
}

