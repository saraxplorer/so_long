/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_content.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/03 16:39:58 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/05/03 16:52:33 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_empty(char *map)
{
	size_t 	i;
	
	i = 0;
	if(!map[i])
		error_exit("map is empty");
}

void	check_empty_line(char *map)
{
	size_t	i;
	
	i = 0;
	while(map[i]!= '\0')
	{
		if(map[0] == '\n' || (map[i] == '\n' && map[i + 1] == '\n'))
			error_exit("empty line in map");
		i++;
	}
}

void	check_invalid_content(int i)
{
	if(!ft_strchr("PEC01X\n", i))
		error_exit("Invalid character found");
}

void	check_content(char *map)
{
	int	player;
	int	exit;
	int	taka;
	int	i;

	player = 0;
	exit = 0;
	taka = 0;
	i = 0;
	while (map[i]!= '\0')
	{
		if (map[i] == 'P')
			player++;
		if (map[i] == 'E')
			exit++;
		if (map[i] == 'C')
			taka++;
		else
			check_invalid_content(map[i]);
		i++;
	}
	if (player != 1 || exit != 1 || taka < 1)
		error_exit("wrong numbers of content");
}