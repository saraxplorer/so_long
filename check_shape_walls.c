/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_shape_walls.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/03 16:42:25 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/05/27 14:01:52 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_shape(char **map_array)
{
	size_t len;
	size_t	line_num;
	
	line_num = 0;
	len = ft_strlen(map_array[line_num]);
	while (map_array[line_num])
	{
		if (ft_strlen(map_array[line_num]) != len)
			error_exit("Map is not rectangle");
		line_num++;
	}
	return(line_num);
}

void	left_n_ryt(t_game *game)
{
	size_t i;
	
	i = 0;
	while (game->grid[i])
	{
		if (game->grid[i][0]!= '1')//first[0] char of i'th row
			error_exit("broken wall at left");
		if (game->grid[i][game->width - 1] != '1')//last char of i'th row
			error_exit("broken wall at right");
		i++;
	}
}

void	top_n_bottom(t_game *game)
{
	int	i;

	i = 0;
	while (game->grid[0][i])
	{
		if (game->grid[0][i] != '1') //i'th char of first[0] row
			error_exit("broken wall at top");
		if (game->grid[game->height -1][0] != '1')//i'th char of last row
			error_exit("broken wall at bottom");
		i++;
	}
}
	
void	check_walls(t_game *game)
{
	left_n_ryt(game);
	top_n_bottom(game);
}
