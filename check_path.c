/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 18:35:03 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/06/06 13:12:50 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_path_all(t_game *temp, int y, int x)
{
	if (temp->grid[y][x] == '1')
		return ;
	if (temp->grid[y][x] == 'E')
		temp->exit_x = 1;
	if (temp->grid[y][x] == 'C')
		temp->geld--;
	temp->grid[y][x] = '1';
	check_path_all(temp, y + 1, x);
	check_path_all(temp, y - 1, x);
	check_path_all(temp, y, x + 1);
	check_path_all(temp, y, x - 1);
}

t_game	temp_game(char **map, int height)
{
	t_game	temp;
	int		i;

	temp.geld = collectables_num(map);
	element_position(map, &temp);
	temp.height = height;
	temp.grid = (char **)ft_calloc(height, sizeof(char *));
	if (temp.grid == NULL)
	{
		free_map(map, height);
		free_map(temp.grid, temp.height);
		error_exit("Memory allocation fail");
	}
	i = 0;
	while (i < height)
	{
		temp.grid[i] = ft_strdup(map[i]);
		i++;
	}
	return (temp);
}

void	check_path(char **map, int height)
{
	t_game	temp;

	temp = temp_game(map, height);
	check_path_all(&temp, temp.player_y, temp.player_x);
	if (temp.exit_x != 1 || temp.geld != 0)
	{
		free_map(map, height);
		free_map(temp.grid, temp.height);
		error_exit("path not valid");
	}
	free_map(temp.grid, temp.height);
}
