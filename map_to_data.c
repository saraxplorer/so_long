/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_to_data.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/03 16:33:11 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/06/03 18:16:22 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_map(char *map)
{
	int		fd;
	char	*line;
	char	*map_str;
	char	*temp;
	
	fd = open(map, O_RDONLY);
	if (fd == -1)
		error_exit("Problem opening file");
	line = get_next_line(fd);
	if (!line)
		error_exit("cannot read map");
	temp = ft_calloc(1, sizeof(char));
	if (!temp)
		error_exit("cannot allocate memory");
	while (line != NULL)
	{
		map_str = ft_strjoin(temp, line);
		if (map_str == NULL)
			return(free(temp), NULL);
		free(line);
		line = get_next_line(fd);
		free(temp);
		temp = map_str;
	}
	return (close(fd), map_str);
}

int	collectables_num(char **map)
{
	int line;
	int letter;
	int	collectable;
	
	collectable = 0;
	line = 0;
	while(map[line]!= NULL)
	{
		letter = 0;
		while(map[line][letter]!='\0')
		{
			if (map[line][letter] == 'C')
				collectable++;
			letter++;
		}
		line++;
	}
	return (collectable);
}

void	element_position(char **map, t_game *game)
{
	int		col;
	int		line;

	line = 0;
	while (map[line])
	{
		col = 0;
		while (map[line][col])
		{
			if (map[line][col] == 'P')
			{
				game->player_x = col;
				game->player_y = line;
			}
			if (map[line][col] == 'E')
			{
				game->exit_x = col;
				game->exit_y = line;
			}
			col++;
		}
		line++;
	}
	return ;
}


t_game	initialize_game_struct(char **grid, int height)
{
	t_game	game;

	game.grid = grid;
	game.steps = 0;
	game.geld = collectables_num(grid);
	element_position(grid, &game);
	game.width = ft_strlen(grid[0]);
	game.height = height;

	return (game);
}

t_game	map_to_data(char *argv)
{
	t_game	game;
	char	*map_str;
	char	**map_array;
	int		height;
	
	map_str = read_map(argv);
	if (!map_str)
		error_exit("Failed to read map");
	check_empty(map_str);
	check_empty_line(map_str);
	check_content(map_str);
	map_array = ft_split(map_str, '\n');
	if (map_array == NULL)
		error_exit("cannot convert map to data");
	free(map_str);
	height = check_map_shape(map_array);
	check_path(map_array, height);
	game = initialize_game_struct(map_array, height);
	check_walls(&game);
	return (game);
}
